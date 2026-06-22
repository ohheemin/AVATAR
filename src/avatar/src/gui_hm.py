#!/usr/bin/env python3

import customtkinter as ctk
import time
import os
import cv2
from PIL import Image
import subprocess
import threading
import signal
from collections import deque

# --- ROS2 Python 라이브러리 임포트 ---
import rclpy
from rclpy.node import Node
from sensor_msgs.msg import JointState, CompressedImage
from std_msgs.msg import Float64, Int32

import pyrealsense2 as rs
import numpy as np

# ── 프로세스 관리 ────────────────────────────────────────────────
_launch_process_lock   = threading.Lock()
_launch_process_by_key = {}
WORKSPACE_SETUP        = os.path.expanduser("~/track_ws/install/setup.bash")


def _launch_ros2_run(setup_script, package_name, executable_name,
                     extra_args=None, label="ROS2 Run", dedup_key=None):
    run_cmd_parts = ["ros2", "run", package_name, executable_name]
    if extra_args:
        run_cmd_parts.extend(extra_args)
    src = (f"source {setup_script}" if os.path.exists(setup_script)
           else "echo 'No workspace setup found'")
    cmd = (f"source /opt/ros/humble/setup.bash && {src} && "
           f"{' '.join(run_cmd_parts)}")
    try:
        with _launch_process_lock:
            if dedup_key:
                ex = _launch_process_by_key.get(dedup_key)
                if ex is not None and ex.poll() is None:
                    return True
            proc = subprocess.Popen(["bash", "-c", cmd], preexec_fn=os.setsid)
            if dedup_key:
                _launch_process_by_key[dedup_key] = proc
        return True
    except Exception as e:
        print(f"[ERROR] Failed to run {label}: {e}")
        return False


def _cleanup_processes_by_key(dedup_key):
    with _launch_process_lock:
        proc = _launch_process_by_key.get(dedup_key)
        if proc is not None and proc.poll() is None:
            try:
                os.killpg(os.getpgid(proc.pid), signal.SIGINT)
                proc.wait(timeout=3)
            except Exception:
                try:
                    os.killpg(os.getpgid(proc.pid), signal.SIGKILL)
                except Exception:
                    pass
            _launch_process_by_key[dedup_key] = None


ctk.set_appearance_mode("Dark")
ctk.set_default_color_theme("blue")

# ── 색상 팔레트 ──────────────────────────────────────────────────
C = {
    "bg_root":      "#07090D",
    "bg_panel":     "#0C1018",
    "bg_card":      "#090E16",
    "accent_cyan":  "#00D4FF",
    "accent_amber": "#FFA500",
    "accent_green": "#00E676",
    "accent_red":   "#FF1744",
    "accent_blue":  "#1565C0",
    "accent_blue2": "#1976D2",
    "border_dim":   "#182030",
    "text_primary": "#D0E8F0",
    "text_dim":     "#3A5060",
    "text_mono":    "#90C8D8",
    "stop_bg":      "#140004",
    "stop_border":  "#FF1744",
}


class DataBuffer:
    def __init__(self, max_rows=100, num_elements=1):
        self.buffer = deque(maxlen=max_rows)
        self.num_elements = num_elements

    def add_data(self, new_list):
        if len(new_list) == self.num_elements:
            self.buffer.append(new_list)

    def get_matrix(self):
        return np.array(self.buffer)


class TeleopMonitorNode(Node):
    def __init__(self, gui_app):
        super().__init__('teleop_gui_monitor')
        self.gui_app = gui_app
        self.current_sub = self.create_subscription(
            Int32,           '/payload',          self.current_callback, 10)
        self.joint_sub   = self.create_subscription(
            JointState,      '/joint_states',     self.joint_callback,   10)
        self.clock_sub   = self.create_subscription(
            Float64,         '/calculated_clock', self.clock_callback,   10)
        self.frame_sub   = self.create_subscription(
            CompressedImage, '/vision_frame',     self.frame_callback,   10)

    def current_callback(self, msg):
        self.gui_app.root.after(0, self.gui_app.update_payload_current, msg.data)

    def joint_callback(self, msg):
        try:
            joints_str    = ", ".join([f"{v:.2f}" for v in msg.position[:3]])
            gripper_val   = msg.position[-1] if len(msg.position) > 0 else 0.0
            gripper_state = "OPEN" if gripper_val > 0.5 else "CLOSED"
            self.gui_app.root.after(
                0, self.gui_app.update_robot_states,
                f"J: [{joints_str}]\nGRIPPER: {gripper_state}")
        except Exception:
            pass

    def clock_callback(self, msg):
        self.gui_app.root.after(0, self.gui_app.update_latency_buffer, msg.data)

    def frame_callback(self, msg):
        try:
            buf   = np.frombuffer(msg.data, dtype=np.uint8)
            frame = cv2.imdecode(buf, cv2.IMREAD_COLOR)
            if frame is not None:
                self.gui_app.root.after(0, self.gui_app.update_vision_frame, frame)
        except Exception:
            pass


# ════════════════════════════════════════════════════════════════
class VisualTestGUI:
    def __init__(self, root):
        self.root = root
        self.root.title("AVATAR TELEOP SYSTEM  //  ROS2 HUMBLE")

        # ── 전체화면으로 시작 ──────────────────────────────────
        self.root.attributes("-fullscreen", True)
        self.root.configure(bg=C["bg_root"])
        self.root.bind("<Escape>", lambda e: self.root.attributes(
            "-fullscreen", not self.root.attributes("-fullscreen")))
        self.root.bind("<F11>", lambda e: self.root.attributes(
            "-fullscreen", not self.root.attributes("-fullscreen")))

        # ── 화면 해상도 기반 스케일 계수 계산 ─────────────────
        self.root.update_idletasks()
        sw = self.root.winfo_screenwidth()
        sh = self.root.winfo_screenheight()
        # 기준 1920×1080 → scale=1.0
        self._scale = min(sw / 1920, sh / 1080)
        self._sw, self._sh = sw, sh

        # 상태 변수
        self.max_latency_trials  = 5
        self.latency_trial       = 0
        self.pnp_time_left       = 120
        self.pnp_timer_running   = False
        self.rs_pipeline         = None
        self.video_running       = False
        self.realsense_online    = False
        self.clock_online        = False
        self.payload_online      = False
        self.latest_latency_ms   = 0.0
        self.latency_buffer      = deque(maxlen=100)
        self.current_avg_latency = 0.0

        self.create_widgets()

        try:
            rclpy.init(args=None)
            self.ros_node   = TeleopMonitorNode(self)
            self.ros_thread = threading.Thread(
                target=rclpy.spin, args=(self.ros_node,), daemon=True)
            self.ros_thread.start()
        except Exception as e:
            self.log_message(f"ROS2 INIT FAILED: {e}")

        self.save_latency = DataBuffer(max_rows=100, num_elements=1)
        self._start_clock_display()
        self.open_camera()

    # ────────────────────────────────────────────────────────────
    # 스케일 헬퍼
    # ────────────────────────────────────────────────────────────
    def _s(self, v):
        """픽셀/사이즈 값을 화면 스케일에 맞게 변환"""
        return max(1, int(v * self._scale))

    def _f(self, base):
        """폰트 사이즈를 화면 스케일에 맞게 변환"""
        return max(8, int(base * self._scale))

    def _font(self, size, weight="normal"):
        return ctk.CTkFont("Courier New", self._f(size), weight=weight)

    # ────────────────────────────────────────────────────────────
    # 패널 헬퍼
    # ────────────────────────────────────────────────────────────
    def _panel(self, parent, title, accent):
        outer = ctk.CTkFrame(parent, fg_color=C["bg_panel"], corner_radius=10,
                             border_width=1, border_color=C["border_dim"])
        # 상단 컬러 바 (3px)
        bar = ctk.CTkFrame(outer, height=3, fg_color=accent, corner_radius=0)
        bar.pack(fill="x")
        bar.pack_propagate(False)
        # 헤더
        hdr = ctk.CTkFrame(outer, fg_color="transparent")
        hdr.pack(fill="x", padx=self._s(14), pady=(self._s(8), self._s(2)))
        dot = ctk.CTkFrame(hdr, width=self._s(7), height=self._s(7),
                           fg_color=accent, corner_radius=2)
        dot.pack(side="left", padx=(0, self._s(8)))
        dot.pack_propagate(False)
        ctk.CTkLabel(hdr, text=title,
                     font=self._font(13, "bold"),
                     text_color=C["text_dim"]).pack(side="left")
        inner = ctk.CTkFrame(outer, fg_color="transparent")
        inner.pack(fill="both", expand=True,
                   padx=self._s(12), pady=(self._s(4), self._s(12)))
        return outer, inner

    def _status_row(self, parent, init_text, init_color):
        row = ctk.CTkFrame(parent, fg_color="transparent")
        row.pack(fill="x", pady=(self._s(4), self._s(8)))
        dot = ctk.CTkFrame(row, width=self._s(10), height=self._s(10),
                           fg_color=C["accent_red"], corner_radius=self._s(5))
        dot.pack(side="left", padx=(self._s(2), self._s(10)))
        dot.pack_propagate(False)
        lbl = ctk.CTkLabel(row, text=init_text,
                           font=self._font(16, "bold"),
                           text_color=init_color)
        lbl.pack(side="left")
        return dot, lbl

    def _btn(self, parent, text, cmd, color=None, height=None):
        return ctk.CTkButton(
            parent, text=text, command=cmd,
            height=height or self._s(44),
            corner_radius=7,
            fg_color=color or C["accent_blue"],
            hover_color=C["accent_blue2"],
            font=self._font(14, "bold"),
            text_color="#FFFFFF")

    # ────────────────────────────────────────────────────────────
    # 위젯 생성
    # ────────────────────────────────────────────────────────────
    def create_widgets(self):
        PAD     = self._s(12)
        LEFT_W  = self._s(300)
        RIGHT_W = self._s(330)
        BTM_H   = self._s(160)

        # ── 타이틀바 ────────────────────────────────────────────
        TB_H = self._s(48)
        titlebar = ctk.CTkFrame(self.root, fg_color=C["bg_panel"],
                                height=TB_H, corner_radius=0)
        titlebar.pack(fill="x")
        titlebar.pack_propagate(False)

        ctk.CTkLabel(titlebar, text="◈  AVATAR TELEOP SYSTEM",
                     font=self._font(17, "bold"),
                     text_color=C["accent_cyan"]).pack(side="left", padx=PAD*2)

        self.lbl_sysclock = ctk.CTkLabel(titlebar, text="--:--:--",
                                         font=self._font(15),
                                         text_color=C["text_dim"])
        self.lbl_sysclock.pack(side="right", padx=PAD*2)

        ctk.CTkLabel(titlebar, text="ROS2 HUMBLE",
                     font=self._font(13),
                     text_color=C["text_dim"]).pack(side="right", padx=PAD//2)

        ctk.CTkFrame(self.root, height=1, fg_color=C["border_dim"],
                     corner_radius=0).pack(fill="x")

        # ── 메인 (3열 grid) ──────────────────────────────────────
        main = ctk.CTkFrame(self.root, fg_color=C["bg_root"], corner_radius=0)
        main.pack(fill="both", expand=True)

        # 핵심: 좌우는 minsize로 고정, 가운데만 weight=1로 확장
        main.columnconfigure(0, minsize=LEFT_W,  weight=0)
        main.columnconfigure(1, weight=1)
        main.columnconfigure(2, minsize=RIGHT_W, weight=0)
        main.rowconfigure(0, weight=1)

        # ════ 왼쪽 컬럼 ════════════════════════════════════════
        left = ctk.CTkFrame(main, fg_color=C["bg_root"], corner_radius=0,
                            width=LEFT_W)
        left.grid(row=0, column=0, sticky="nsew",
                  padx=(PAD, PAD//2), pady=PAD)
        left.pack_propagate(False)
        left.columnconfigure(0, weight=1)
        left.rowconfigure(0, weight=1)
        left.rowconfigure(1, weight=1)
        left.rowconfigure(2, weight=1)

        # RealSense 패널
        rs_out, rs_in = self._panel(left, "REALSENSE D435i", C["accent_cyan"])
        rs_out.grid(row=0, column=0, sticky="nsew", pady=(0, PAD//2))

        self.dot_rs, self.lbl_rs_status = self._status_row(
            rs_in, "D435i  OFFLINE", C["accent_red"])
        self.btn_realsense = self._btn(
            rs_in, "▶  START REALSENSE", self.toggle_realsense)
        self.btn_realsense.pack(fill="x", pady=(0, PAD//2))
        ctk.CTkLabel(rs_in,
                     text="SN: 233522074207  |  233522076563",
                     font=self._font(10),
                     text_color=C["text_dim"]).pack()

        # Robot Planning 패널
        rp_out, rp_in = self._panel(left, "ROBOT PLANNING", C["accent_amber"])
        rp_out.grid(row=1, column=0, sticky="nsew", pady=PAD//2)

        self.dot_rp, self.lbl_robot_status = self._status_row(
            rp_in, "PLANNING  OFFLINE", C["accent_red"])
        self.lbl_countdown = ctk.CTkLabel(
            rp_in, text="",
            font=self._font(52, "bold"),
            text_color=C["accent_amber"])
        self.lbl_countdown.pack()
        self.btn_planning = self._btn(
            rp_in, "▶  START PLANNING", self.start_planning_with_tts)
        self.btn_planning.pack(fill="x", pady=(PAD//2, 0))

        # Clock Node 패널
        ck_out, ck_in = self._panel(left, "CLOCK NODE", C["accent_green"])
        ck_out.grid(row=2, column=0, sticky="nsew", pady=(PAD//2, 0))

        self.dot_ck, self.lbl_clock_status = self._status_row(
            ck_in, "CLOCK  OFFLINE", C["accent_red"])
        self.btn_clock = self._btn(ck_in, "▶  START CLOCK", self.toggle_clock)
        self.btn_clock.pack(fill="x", pady=(0, PAD//2))

        # ════ 가운데 컬럼 ══════════════════════════════════════
        center = ctk.CTkFrame(main, fg_color=C["bg_root"], corner_radius=0)
        center.grid(row=0, column=1, sticky="nsew",
                    padx=PAD//2, pady=PAD)
        center.rowconfigure(0, weight=10)
        center.rowconfigure(1, weight=3)
        center.columnconfigure(0, weight=1)

        # 카메라 행
        cam_row = ctk.CTkFrame(center, fg_color=C["bg_root"])
        cam_row.grid(row=0, column=0, sticky="nsew", pady=(0, PAD//2))
        cam_row.columnconfigure(0, weight=1)
        cam_row.columnconfigure(1, weight=1)
        cam_row.rowconfigure(0, weight=1)

        # Monitor 카메라
        cl_out, cl_in = self._panel(cam_row, "MONITOR CAM", C["accent_cyan"])
        cl_out.grid(row=0, column=0, sticky="nsew", padx=(0, PAD//2))
        ctk.CTkLabel(cl_in,
                     text="S/N 233522074207  //  640×480  RGB  30fps",
                     font=self._font(10),
                     text_color=C["text_dim"]).pack(anchor="w", pady=(0, PAD//2))
        self.lbl_video = ctk.CTkLabel(
            cl_in, text="INITIALIZING STREAM...",
            fg_color=C["bg_card"], corner_radius=6,
            font=self._font(14), text_color=C["text_dim"])
        self.lbl_video.pack(expand=True, fill="both")

        # Skeleton 카메라
        cr_out, cr_in = self._panel(cam_row, "SKELETON CAM", C["accent_amber"])
        cr_out.grid(row=0, column=1, sticky="nsew", padx=(PAD//2, 0))
        ctk.CTkLabel(cr_in,
                     text="S/N 233522076563  //  TOPIC: /vision_frame",
                     font=self._font(10),
                     text_color=C["text_dim"]).pack(anchor="w", pady=(0, PAD//2))
        self.lbl_vision_frame = ctk.CTkLabel(
            cr_in, text="REALSENSE 버튼을 눌러 시작",
            fg_color=C["bg_card"], corner_radius=6,
            font=self._font(14), text_color=C["text_dim"])
        self.lbl_vision_frame.pack(expand=True, fill="both")

        # PnP 패널
        pnp_out, pnp_in = self._panel(
            center, "PICK & PLACE TEST", C["accent_cyan"])
        pnp_out.grid(row=1, column=0, sticky="nsew", pady=(PAD//2, 0))
        pnp_in.columnconfigure(0, weight=1)
        pnp_in.columnconfigure(1, weight=0)
        pnp_in.rowconfigure(0, weight=1)

        timer_box = ctk.CTkFrame(pnp_in, fg_color=C["bg_card"], corner_radius=8)
        timer_box.grid(row=0, column=0, sticky="nsew", padx=(0, PAD))
        self.lbl_timer = ctk.CTkLabel(
            timer_box, text="02:00",
            font=self._font(52, "bold"),
            text_color=C["accent_cyan"])
        self.lbl_timer.pack(expand=True)

        pnp_btns = ctk.CTkFrame(pnp_in, fg_color="transparent")
        pnp_btns.grid(row=0, column=1, sticky="ns")
        self.btn_pnp_start = self._btn(
            pnp_btns, "▶  START",
            lambda: self.start_trial("pnp"), height=self._s(48))
        self.btn_pnp_start.pack(pady=(0, PAD//2), fill="x")
        self.btn_pnp_reset = self._btn(
            pnp_btns, "↺  RESET", self.reset_pnp,
            color="#162030", height=self._s(48))
        self.btn_pnp_reset.pack(fill="x")

        # ════ 오른쪽 컬럼 ══════════════════════════════════════
        right = ctk.CTkFrame(main, fg_color=C["bg_root"], corner_radius=0,
                             width=RIGHT_W)
        right.grid(row=0, column=2, sticky="nsew",
                   padx=(PAD//2, PAD), pady=PAD)
        right.pack_propagate(False)
        right.columnconfigure(0, weight=1)
        right.rowconfigure(0, weight=2)
        right.rowconfigure(1, weight=3)
        right.rowconfigure(2, weight=3)

        # Payload 패널
        pl_out, pl_in = self._panel(right, "PAYLOAD TEST  80g", C["accent_amber"])
        pl_out.grid(row=0, column=0, sticky="nsew", pady=(0, PAD//2))

        self.lbl_motor_current = ctk.CTkLabel(
            pl_in, text="LOAD :  --  %",
            font=self._font(24, "bold"),
            text_color=C["accent_amber"])
        self.lbl_motor_current.pack(pady=(PAD//2, PAD//2))
        self.prog_payload = ctk.CTkProgressBar(
            pl_in, height=self._s(10), corner_radius=4,
            fg_color=C["bg_card"], progress_color=C["accent_amber"])
        self.prog_payload.set(0)
        self.prog_payload.pack(fill="x", pady=(0, PAD//2))
        self.btn_payload_start = self._btn(
            pl_in, "▶  EXECUTE TEST", lambda: self.start_trial("payload"))
        self.btn_payload_start.pack(fill="x")

        # Latency 패널
        lat_out, lat_in = self._panel(
            right, "LATENCY CHECK  (ms)", C["accent_cyan"])
        lat_out.grid(row=1, column=0, sticky="nsew", pady=PAD//2)

        avg_box = ctk.CTkFrame(lat_in, fg_color=C["bg_card"], corner_radius=8)
        avg_box.pack(fill="x", pady=(0, PAD//2))
        ctk.CTkLabel(avg_box, text="REAL-TIME AVG",
                     font=self._font(11),
                     text_color=C["text_dim"]).pack(pady=(PAD//2, 0))
        self.lbl_realtime_latency = ctk.CTkLabel(
            avg_box, text="-- ms",
            font=self._font(30, "bold"),
            text_color=C["accent_cyan"])
        self.lbl_realtime_latency.pack(pady=(0, PAD//2))

        self.btn_lat_start = self._btn(
            lat_in, "◉  MEASURE", lambda: self.start_trial("latency"))
        self.btn_lat_start.pack(fill="x", pady=(0, PAD//2))

        ind_f = ctk.CTkFrame(lat_in, fg_color="transparent")
        ind_f.pack(fill="x")
        for i in range(5):
            ind_f.columnconfigure(i, weight=1)

        self.lat_inds = []
        for i in range(5):
            cell = ctk.CTkFrame(ind_f, fg_color=C["bg_card"], corner_radius=6)
            cell.grid(row=0, column=i, padx=self._s(2), sticky="ew")
            ctk.CTkLabel(cell, text=f"T{i+1}",
                         font=self._font(10),
                         text_color=C["text_dim"]).pack(pady=(PAD//2, 0))
            lbl = ctk.CTkLabel(cell, text="--",
                               font=self._font(16, "bold"),
                               text_color=C["text_mono"])
            lbl.pack(pady=(0, PAD//2))
            self.lat_inds.append(lbl)

        # Robot State 패널
        rs2_out, rs2_in = self._panel(right, "ROBOT STATE", C["accent_green"])
        rs2_out.grid(row=2, column=0, sticky="nsew", pady=(PAD//2, 0))

        joint_box = ctk.CTkFrame(rs2_in, fg_color=C["bg_card"], corner_radius=8)
        joint_box.pack(fill="x", expand=True)
        ctk.CTkLabel(joint_box, text="JOINTS  /  GRIPPER",
                     font=self._font(11),
                     text_color=C["text_dim"]).pack(
                         pady=(PAD//2, 0), anchor="w", padx=PAD)
        self.lbl_robot_states = ctk.CTkLabel(
            joint_box,
            text="J: [ --.--,  --.--,  --.-- ]\nGRIPPER: --",
            font=self._font(15, "bold"),
            text_color=C["text_mono"], justify="left")
        self.lbl_robot_states.pack(
            pady=(PAD//4, PAD//2), padx=PAD, anchor="w")

        # ════ 하단 바 ═══════════════════════════════════════════
        ctk.CTkFrame(self.root, height=1, fg_color=C["border_dim"],
                     corner_radius=0).pack(fill="x")

        btm = ctk.CTkFrame(self.root, fg_color=C["bg_panel"],
                           height=BTM_H, corner_radius=0)
        btm.pack(fill="x")
        btm.pack_propagate(False)

        btm_inner = ctk.CTkFrame(btm, fg_color="transparent")
        btm_inner.pack(fill="both", expand=True,
                       padx=PAD, pady=PAD//2)
        btm_inner.columnconfigure(0, weight=1)
        btm_inner.columnconfigure(1, weight=0)
        btm_inner.rowconfigure(0, weight=1)

        # 로그
        log_wrap = ctk.CTkFrame(btm_inner, fg_color=C["bg_root"],
                                corner_radius=8, border_width=1,
                                border_color=C["border_dim"])
        log_wrap.grid(row=0, column=0, sticky="nsew", padx=(0, PAD))
        ctk.CTkLabel(log_wrap, text="▸ SYSTEM LOG",
                     font=self._font(11),
                     text_color=C["text_dim"]).pack(anchor="w", padx=PAD, pady=(PAD//2, 0))
        self.log_area = ctk.CTkTextbox(
            log_wrap, fg_color="transparent",
            text_color=C["accent_green"],
            font=self._font(13),
            scrollbar_button_color=C["border_dim"])
        self.log_area.pack(fill="both", expand=True, padx=PAD//2, pady=PAD//2)

        # E-STOP
        STOP_SZ = int(BTM_H * 0.82)
        stop_wrap = ctk.CTkFrame(btm_inner, fg_color="transparent",
                                 width=STOP_SZ)
        stop_wrap.grid(row=0, column=1, sticky="ns")
        stop_wrap.pack_propagate(False)
        self.btn_stop = ctk.CTkButton(
            stop_wrap, text="⬡\nE-STOP",
            width=STOP_SZ, height=STOP_SZ,
            corner_radius=10,
            fg_color=C["stop_bg"], hover_color="#200008",
            border_width=2, border_color=C["stop_border"],
            font=self._font(17, "bold"),
            text_color=C["accent_red"],
            command=self.mock_stop_all)
        self.btn_stop.pack(expand=True)

    # ────────────────────────────────────────────────────────────
    # 실시간 시계
    # ────────────────────────────────────────────────────────────
    def _start_clock_display(self):
        def _tick():
            self.lbl_sysclock.configure(
                text=f"SYS  {time.strftime('%H:%M:%S')}")
            self.root.after(1000, _tick)
        _tick()

    # ────────────────────────────────────────────────────────────
    # 유틸리티
    # ────────────────────────────────────────────────────────────
    def log_message(self, msg):
        self.log_area.configure(state="normal")
        self.log_area.insert("end", f"[{time.strftime('%H:%M:%S')}]  {msg}\n")
        self.log_area.see("end")
        self.log_area.configure(state="disabled")

    def update_payload_current(self, val):
        self.lbl_motor_current.configure(text=f"LOAD :  {val:3d}  %")
        self.prog_payload.set(max(0.0, min(1.0, val / 100.0)))
        col = (C["accent_red"]   if val > 80 else
               C["accent_amber"] if val > 50 else C["accent_green"])
        self.lbl_motor_current.configure(text_color=col)
        self.prog_payload.configure(progress_color=col)

    def update_robot_states(self, s):
        self.lbl_robot_states.configure(text=s)

    # ────────────────────────────────────────────────────────────
    # 카메라
    # ────────────────────────────────────────────────────────────
    def open_camera(self):
        if not self.video_running:
            try:
                self.rs_pipeline = rs.pipeline()
                cfg = rs.config()
                cfg.enable_device("233522074207")
                cfg.enable_stream(rs.stream.color, 640, 480, rs.format.bgr8, 30)
                self.rs_pipeline.start(cfg)
                self.video_running = True
                self.update_video_frame()
                self.log_message("Monitor cam started (S/N: 233522074207).")
            except Exception as e:
                self.lbl_video.configure(
                    text=f"CAMERA ERROR\n{e}", text_color=C["accent_red"])
                self.log_message(f"Monitor cam init failed: {e}")

    def update_video_frame(self):
        if not (self.video_running and self.rs_pipeline):
            return
        try:
            frames = self.rs_pipeline.wait_for_frames()
            cf = frames.get_color_frame()
            if cf:
                w = self.lbl_video.winfo_width()  or 640
                h = self.lbl_video.winfo_height() or 360
                frame = np.asanyarray(cf.get_data())
                frame = cv2.resize(frame, (w, h))
                rgb   = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
                img   = Image.fromarray(rgb)
                imgtk = ctk.CTkImage(light_image=img, dark_image=img,
                                     size=(w, h))
                self.lbl_video.configure(image=imgtk, text="")
        except Exception:
            pass
        self.root.after(30, self.update_video_frame)

    def update_vision_frame(self, bgr_frame):
        try:
            w = self.lbl_vision_frame.winfo_width()  or 640
            h = self.lbl_vision_frame.winfo_height() or 360
            frame = cv2.resize(bgr_frame, (w, h))
            rgb   = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
            img   = Image.fromarray(rgb)
            imgtk = ctk.CTkImage(light_image=img, dark_image=img,
                                 size=(w, h))
            self.lbl_vision_frame.configure(image=imgtk, text="")
        except Exception:
            pass

    # ────────────────────────────────────────────────────────────
    # 온라인/오프라인 상태 헬퍼
    # ────────────────────────────────────────────────────────────
    def _set_online(self, dot, lbl, btn, text_status, text_btn):
        dot.configure(fg_color=C["accent_green"])
        lbl.configure(text=text_status, text_color=C["accent_green"])
        btn.configure(text=text_btn,
                      fg_color=C["stop_bg"], hover_color="#200010",
                      border_color=C["stop_border"], border_width=1)

    def _set_offline(self, dot, lbl, btn, text_status, text_btn):
        dot.configure(fg_color=C["accent_red"])
        lbl.configure(text=text_status, text_color=C["accent_red"])
        btn.configure(text=text_btn,
                      fg_color=C["accent_blue"], hover_color=C["accent_blue2"],
                      border_width=0)

    # ────────────────────────────────────────────────────────────
    # 노드 제어
    # ────────────────────────────────────────────────────────────
    def toggle_realsense(self):
        if not self.realsense_online:
            ok = _launch_ros2_run(WORKSPACE_SETUP, "avatar", "vision_nav.py",
                                  [], "RealSense", "realsense_key")
            if ok:
                self.realsense_online = True
                self._set_online(self.dot_rs, self.lbl_rs_status,
                                 self.btn_realsense,
                                 "D435i  ONLINE", "■  STOP REALSENSE")
                self.lbl_vision_frame.configure(
                    text="CONNECTING...", text_color=C["accent_amber"])
                self.log_message("vision_nav.py started — waiting for /vision_frame ...")
        else:
            _cleanup_processes_by_key("realsense_key")
            self.realsense_online = False
            self._set_offline(self.dot_rs, self.lbl_rs_status,
                              self.btn_realsense,
                              "D435i  OFFLINE", "▶  START REALSENSE")
            self.lbl_vision_frame.configure(
                image=None, text="REALSENSE 버튼을 눌러 시작",
                text_color=C["text_dim"])
            self.log_message("vision_nav.py stopped.")

    def toggle_clock(self):
        if not self.clock_online:
            ok = _launch_ros2_run(WORKSPACE_SETUP, "avatar", "clock.py",
                                  [], "Clock", "clock_key")
            if ok:
                self.clock_online = True
                self._set_online(self.dot_ck, self.lbl_clock_status,
                                 self.btn_clock,
                                 "CLOCK  ONLINE", "■  STOP CLOCK")
                self.log_message("Clock node started.")
        else:
            _cleanup_processes_by_key("clock_key")
            self.clock_online = False
            self._set_offline(self.dot_ck, self.lbl_clock_status,
                              self.btn_clock,
                              "CLOCK  OFFLINE", "▶  START CLOCK")
            self.log_message("Clock node stopped.")

    # ────────────────────────────────────────────────────────────
    # Planning (TTS + countdown)
    # ────────────────────────────────────────────────────────────
    def _tts_and_launch_planning(self):
        try:
            from gtts import gTTS
            import playsound
            fn = "/tmp/planning_announce.mp3"
            gTTS(text="자리에 앉아서 차렷자세를 취해주세요. 3초 후에 시작합니다.",
                 lang='ko').save(fn)
            playsound.playsound(fn)
            os.path.exists(fn) and os.remove(fn)
        except Exception as e:
            print(f"[TTS] {e}")

        import time as _t
        for n in range(3, 0, -1):
            self.root.after(0, self.lbl_countdown.configure, {"text": str(n)})
            self.root.after(0, self.lbl_robot_status.configure,
                            {"text": f"STARTING IN  {n}s ...",
                             "text_color": C["accent_amber"]})
            _t.sleep(1)
        self.root.after(0, self.lbl_countdown.configure, {"text": ""})

        ok = _launch_ros2_run(WORKSPACE_SETUP, "avatar", "dxl_subscriber.py",
                              None, "RobotPlanning", "planning_key")
        if ok:
            self.root.after(0, self.dot_rp.configure,
                            {"fg_color": C["accent_green"]})
            self.root.after(0, self.lbl_robot_status.configure,
                            {"text": "PLANNING  ONLINE",
                             "text_color": C["accent_green"]})
            self.root.after(0, self.btn_planning.configure,
                            {"state": "disabled", "text": "PLANNING ACTIVE"})
            self.root.after(0, self.log_message, "Planning node started.")
            _t.sleep(4)
            try:
                from gtts import gTTS
                import playsound
                fn2 = "/tmp/teleop_start.mp3"
                gTTS(text="이제 텔레오퍼레이션을 시작해주세요.", lang='ko').save(fn2)
                playsound.playsound(fn2)
                os.path.exists(fn2) and os.remove(fn2)
            except Exception as e:
                print(f"[TTS] {e}")
        else:
            self.root.after(0, self.dot_rp.configure,
                            {"fg_color": C["accent_red"]})
            self.root.after(0, self.lbl_robot_status.configure,
                            {"text": "PLANNING  OFFLINE",
                             "text_color": C["accent_red"]})
            self.root.after(0, self.btn_planning.configure,
                            {"state": "normal", "text": "▶  START PLANNING"})
            self.root.after(0, self.log_message,
                            "Failed to start planning node.")

    def start_planning_with_tts(self):
        self.btn_planning.configure(state="disabled", text="PREPARING...")
        self.dot_rp.configure(fg_color=C["accent_amber"])
        self.lbl_robot_status.configure(
            text="PREPARING...", text_color=C["accent_amber"])
        self.log_message("TTS 안내 중 — 3초 후 Planning 노드 시작 예정.")
        threading.Thread(
            target=self._tts_and_launch_planning, daemon=True).start()

    # ────────────────────────────────────────────────────────────
    # 시험 (Payload / PnP / Latency)
    # ────────────────────────────────────────────────────────────
    def start_trial(self, t_type):
        if t_type == "payload":
            if not self.payload_online:
                self.log_message("Starting Payload Test (80g)...")
                ok = _launch_ros2_run(WORKSPACE_SETUP, "avatar",
                                      "payload_test.py", [],
                                      "PayloadTest", "payload_key")
                if ok:
                    self.payload_online = True
                    self.btn_payload_start.configure(
                        text="■  STOP TEST",
                        fg_color=C["stop_bg"], hover_color="#200010",
                        border_color=C["stop_border"], border_width=1)
                    self.log_message("payload_test.py node started.")
                else:
                    self.log_message("Failed to start payload test node.")
            else:
                _cleanup_processes_by_key("payload_key")
                self.payload_online = False
                self.btn_payload_start.configure(
                    text="▶  EXECUTE TEST",
                    fg_color=C["accent_blue"], hover_color=C["accent_blue2"],
                    border_width=0)
                self.lbl_motor_current.configure(
                    text="LOAD :  --  %", text_color=C["accent_amber"])
                self.prog_payload.set(0)
                self.log_message("Payload test stopped.")

        elif t_type == "pnp":
            self.log_message("Pick & Place Timer Started.")
            self.btn_pnp_start.configure(state="disabled")
            self.pnp_time_left     = 120
            self.pnp_timer_running = True
            self.update_timer()

        elif t_type == "latency":
            if self.latency_trial < self.max_latency_trials:
                self.btn_lat_start.configure(state="disabled")
                self.root.after(500, self.record_latency)

    def update_timer(self):
        if self.pnp_timer_running and self.pnp_time_left > 0:
            m, s = divmod(self.pnp_time_left, 60)
            self.lbl_timer.configure(text=f"{m:02d}:{s:02d}")
            col = (C["accent_red"]   if self.pnp_time_left <= 10 else
                   C["accent_amber"] if self.pnp_time_left <= 30 else
                   C["accent_cyan"])
            self.lbl_timer.configure(text_color=col)
            self.pnp_time_left -= 1
            self.root.after(1000, self.update_timer)
        elif self.pnp_time_left <= 0:
            self.lbl_timer.configure(text="00:00", text_color=C["accent_red"])
            self.pnp_timer_running = False
            self.btn_pnp_start.configure(state="normal")
            self.log_message("Pick & Place Timer Finished.")

    def reset_pnp(self):
        self.pnp_timer_running = False
        self.pnp_time_left     = 120
        self.lbl_timer.configure(text="02:00", text_color=C["accent_cyan"])
        self.btn_pnp_start.configure(state="normal")
        self.log_message("PnP Timer Reset.")

    def update_latency_buffer(self, val):
        self.latency_buffer.append(val)
        self.current_avg_latency = sum(self.latency_buffer) / len(self.latency_buffer)
        self.lbl_realtime_latency.configure(
            text=f"{int(self.current_avg_latency)} ms")

    def record_latency(self):
        if not self.latency_buffer:
            self.log_message("WARNING: No latency data received yet.")
            return
        val = int(self.current_avg_latency)
        col = (C["accent_green"] if val < 50 else
               C["accent_amber"] if val < 150 else C["accent_red"])
        self.lat_inds[self.latency_trial].configure(
            text=f"{val}", text_color=col)
        self.latency_trial += 1
        if self.latency_trial < self.max_latency_trials:
            self.btn_lat_start.configure(state="normal")
        else:
            self.btn_lat_start.configure(
                text="DONE", state="disabled", fg_color="#162030")
        self.log_message(f"Latency T{self.latency_trial}: {val} ms")

    # ────────────────────────────────────────────────────────────
    # E-STOP
    # ────────────────────────────────────────────────────────────
    def mock_stop_all(self):
        for key in ("realsense_key", "planning_key",
                    "clock_key", "payload_key"):
            _cleanup_processes_by_key(key)

        self.video_running = False
        if self.rs_pipeline:
            self.rs_pipeline.stop()
            self.rs_pipeline = None

        self.realsense_online  = False
        self.clock_online      = False
        self.payload_online    = False
        self.pnp_timer_running = False

        for dot in (self.dot_rs, self.dot_rp, self.dot_ck):
            dot.configure(fg_color=C["accent_red"])

        self.lbl_rs_status.configure(
            text="D435i  OFFLINE",     text_color=C["accent_red"])
        self.lbl_clock_status.configure(
            text="CLOCK  OFFLINE",     text_color=C["accent_red"])
        self.lbl_robot_status.configure(
            text="PLANNING  OFFLINE",  text_color=C["accent_red"])
        self.lbl_countdown.configure(text="")

        for btn, txt in [(self.btn_realsense, "▶  START REALSENSE"),
                         (self.btn_clock,     "▶  START CLOCK"),
                         (self.btn_planning,  "▶  START PLANNING")]:
            btn.configure(text=txt, fg_color=C["accent_blue"],
                          hover_color=C["accent_blue2"],
                          state="normal", border_width=0)

        self.btn_payload_start.configure(
            text="▶  EXECUTE TEST", fg_color=C["accent_blue"],
            hover_color=C["accent_blue2"], border_width=0)

        self.lbl_vision_frame.configure(
            image=None, text="REALSENSE 버튼을 눌러 시작",
            text_color=C["text_dim"])
        self.lbl_motor_current.configure(
            text="LOAD :  --  %", text_color=C["accent_amber"])
        self.prog_payload.set(0)
        self.log_message("⚠  EMERGENCY STOP — ALL PROCESSES TERMINATED")


# ════════════════════════════════════════════════════════════════
def main():
    root = ctk.CTk()
    app  = VisualTestGUI(root)

    def on_closing():
        app.video_running = False
        if app.rs_pipeline:
            app.rs_pipeline.stop()
        for key in ("realsense_key", "planning_key",
                    "clock_key", "payload_key"):
            _cleanup_processes_by_key(key)
        os._exit(0)

    root.protocol("WM_DELETE_WINDOW", on_closing)
    root.mainloop()


if __name__ == "__main__":
    main()