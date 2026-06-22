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

# RealSense 파이썬 래퍼 및 numpy 임포트
import pyrealsense2 as rs
import numpy as np

# --- ROS2 프로세스 추적용 전역 변수 및 함수 ---
_launch_process_lock = threading.Lock()
_launch_process_by_key = {}

WORKSPACE_SETUP = os.path.expanduser("~/track_ws/install/setup.bash")

def _launch_ros2_launch(setup_script, package_name, launch_file, extra_args=None, label="ROS2", dedup_key=None):
    launch_cmd_parts = ["ros2", "launch", package_name, launch_file]
    if extra_args:
        launch_cmd_parts.extend(extra_args)
    source_chain = f"source {setup_script}" if os.path.exists(setup_script) else "echo 'No workspace setup found'"
    bash_command = f"source /opt/ros/humble/setup.bash && {source_chain} && {' '.join(launch_cmd_parts)}"
    try:
        with _launch_process_lock:
            if dedup_key:
                existing = _launch_process_by_key.get(dedup_key)
                if existing is not None and existing.poll() is None:
                    return True
            proc = subprocess.Popen(["bash", "-c", bash_command], preexec_fn=os.setsid)
            if dedup_key:
                _launch_process_by_key[dedup_key] = proc
        return True
    except Exception as e:
        print(f"[ERROR] Failed to launch {label}: {e}")
        return False

def _launch_ros2_run(setup_script, package_name, executable_name, extra_args=None, label="ROS2 Run", dedup_key=None):
    run_cmd_parts = ["ros2", "run", package_name, executable_name]
    if extra_args:
        run_cmd_parts.extend(extra_args)
    source_chain = f"source {setup_script}" if os.path.exists(setup_script) else "echo 'No workspace setup found'"
    bash_command = f"source /opt/ros/humble/setup.bash && {source_chain} && {' '.join(run_cmd_parts)}"
    print(f"[DEBUG] {label} run command: {bash_command}")
    try:
        with _launch_process_lock:
            if dedup_key:
                existing = _launch_process_by_key.get(dedup_key)
                if existing is not None and existing.poll() is None:
                    return True
            proc = subprocess.Popen(["bash", "-c", bash_command], preexec_fn=os.setsid)
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

# ═══ 폰트 사이즈 상수 ════════════════════════════════════════════
FS_PANEL_TITLE  = 25   # 패널 타이틀 (RealSense Controller 등)
FS_STATUS       = 30   # Online/Offline 상태 라벨 / 카메라 안내 텍스트
FS_BTN          = 17   # 버튼 텍스트
FS_BTN_EMSTOP   = 18   # 비상정지 버튼
FS_VALUE        = 18   # Robot State / Latency 수치
FS_VALUE_MONO   = 22   # 모노스페이스 수치 (Consolas)
FS_TIMER        = 36   # PnP 타이머
FS_COUNTDOWN    = 60   # 카운트다운 숫자
FS_LOG          = 16   # 로그 텍스트
FS_CAM_LABEL    = 13   # 카메라 라벨 (S/N 표시)
FS_LAT_IND      = 20   # Latency 개별 인디케이터
FS_REALTIME_LAT = 18   # Real-time Avg 라벨
# ═════════════════════════════════════════════════════════════════


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
        self.current_sub = self.create_subscription(Int32,           '/payload',          self.current_callback, 10)
        self.joint_sub   = self.create_subscription(JointState,      '/joint_states',     self.joint_callback,   10)
        self.clock_sub   = self.create_subscription(Float64,         '/calculated_clock', self.clock_callback,   10)
        self.frame_sub   = self.create_subscription(CompressedImage, '/vision_frame',     self.frame_callback,   10)

    def current_callback(self, msg):
        self.gui_app.root.after(0, self.gui_app.update_payload_current, msg.data)

    def joint_callback(self, msg):
        try:
            joints_str    = ", ".join([f"{val:.2f}" for val in msg.position[:3]])
            gripper_val   = msg.position[-1] if len(msg.position) > 0 else 0.0
            gripper_state = "OPEN" if gripper_val > 0.5 else "CLOSED"
            display_text  = f"Joints(deg): [{joints_str}]\nGripper: {gripper_state}"
            self.gui_app.root.after(0, self.gui_app.update_robot_states, display_text)
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


class VisualTestGUI:
    def __init__(self, root):
        self.root = root
        self.root.title("Real-time Robot Teleoperation Panel")
        self.root.geometry("1600x950")

        self.max_latency_trials  = 5
        self.latency_trial       = 0
        self.pnp_time_left       = 120
        self.pnp_timer_running   = False

        self.rs_pipeline   = None
        self.video_running = False

        self.realsense_online = False
        self.clock_online     = False
        self.payload_online   = False

        self.latest_latency_ms   = 0.0
        self.latency_buffer      = deque(maxlen=100)
        self.current_avg_latency = 0.0

        self.create_widgets()

        try:
            rclpy.init(args=None)
            self.ros_node   = TeleopMonitorNode(self)
            self.ros_thread = threading.Thread(target=rclpy.spin, args=(self.ros_node,), daemon=True)
            self.ros_thread.start()
        except Exception as e:
            self.log_message(f"Failed to init ROS2 Node: {e}")

        self.save_latency = DataBuffer(max_rows=100, num_elements=1)
        self.open_camera()

    # ─────────────────────────────────────────────────────────────
    # 위젯 생성
    # ─────────────────────────────────────────────────────────────
    def create_widgets(self):
        ROOT_BG  = "#121212"
        PANEL_BG = "#1E1E1E"

        content_wrapper = ctk.CTkFrame(self.root, fg_color=ROOT_BG, corner_radius=0)
        content_wrapper.pack(fill="both", expand=True, padx=20, pady=5)

        content_wrapper.rowconfigure(0, weight=1)
        content_wrapper.columnconfigure(0, weight=1)
        content_wrapper.columnconfigure(1, weight=3)
        content_wrapper.columnconfigure(2, weight=1)

        # ==========================================
        # [왼쪽 컬럼]
        # ==========================================
        left_col = ctk.CTkFrame(content_wrapper, fg_color=ROOT_BG, corner_radius=0)
        left_col.grid(row=0, column=0, sticky="nsew", padx=(0, 15))

        # RealSense Controller
        rs_frame = ctk.CTkFrame(left_col, corner_radius=25, fg_color=PANEL_BG, border_width=2, border_color="#333333")
        rs_frame.pack(fill="both", expand=True, pady=(0, 10))
        rs_inner = ctk.CTkFrame(rs_frame, fg_color="transparent")
        rs_inner.pack(expand=True)
        ctk.CTkLabel(rs_inner, text="RealSense Controller",
                     font=ctk.CTkFont(size=FS_PANEL_TITLE, weight="bold")).pack(pady=(10, 5))
        self.lbl_rs_status = ctk.CTkLabel(rs_inner, text="[ D435i Offline ]", text_color="#FF5252",
                                           font=ctk.CTkFont(size=FS_STATUS, weight="bold"))
        self.lbl_rs_status.pack(pady=5)
        self.btn_realsense = ctk.CTkButton(rs_inner, text="Start RealSense", height=48, corner_radius=12,
                                           fg_color="#0277BD", border_width=2, border_color="#0277BD",
                                           font=ctk.CTkFont(size=FS_BTN, weight="bold"),
                                           command=self.toggle_realsense)
        self.btn_realsense.pack(fill="x", padx=25, pady=(5, 10))

        # Robot Planning
        robot_frame = ctk.CTkFrame(left_col, corner_radius=25, fg_color=PANEL_BG, border_width=2, border_color="#333333")
        robot_frame.pack(fill="both", expand=True, pady=(5, 5))
        robot_inner = ctk.CTkFrame(robot_frame, fg_color="transparent")
        robot_inner.pack(expand=True)
        ctk.CTkLabel(robot_inner, text="Robot Planning",
                     font=ctk.CTkFont(size=FS_PANEL_TITLE, weight="bold")).pack(pady=(10, 5))
        self.lbl_robot_status = ctk.CTkLabel(robot_inner, text="[ Planning Offline ]", text_color="#FF5252",
                                              font=ctk.CTkFont(size=FS_STATUS, weight="bold"))
        self.lbl_robot_status.pack(pady=5)
        self.lbl_countdown = ctk.CTkLabel(robot_inner, text="",
                                          font=ctk.CTkFont(size=FS_COUNTDOWN, weight="bold"),
                                          text_color="#FF5252")
        self.lbl_countdown.pack(pady=2)
        self.btn_planning = ctk.CTkButton(robot_inner, text="Start Planning", height=48, corner_radius=12,
                                          fg_color="#0277BD", border_width=2, border_color="#0277BD",
                                          font=ctk.CTkFont(size=FS_BTN, weight="bold"),
                                          command=self.start_planning_with_tts)
        self.btn_planning.pack(fill="x", padx=25, pady=(5, 10))

        # Clock Node
        clock_frame = ctk.CTkFrame(left_col, corner_radius=25, fg_color=PANEL_BG, border_width=2, border_color="#333333")
        clock_frame.pack(fill="both", expand=True, pady=(10, 0))
        clock_inner = ctk.CTkFrame(clock_frame, fg_color="transparent")
        clock_inner.pack(expand=True)
        ctk.CTkLabel(clock_inner, text="Clock Node",
                     font=ctk.CTkFont(size=FS_PANEL_TITLE, weight="bold")).pack(pady=(10, 5))
        self.lbl_clock_status = ctk.CTkLabel(clock_inner, text="[ Clock Offline ]", text_color="#FF5252",
                                              font=ctk.CTkFont(size=FS_STATUS, weight="bold"))
        self.lbl_clock_status.pack(pady=5)
        self.btn_clock = ctk.CTkButton(clock_inner, text="Start Clock", height=48, corner_radius=12,
                                       fg_color="#0277BD", border_width=2, border_color="#0277BD",
                                       font=ctk.CTkFont(size=FS_BTN, weight="bold"),
                                       command=self.toggle_clock)
        self.btn_clock.pack(fill="x", padx=25, pady=(5, 10))

        # ==========================================
        # [가운데 컬럼]: 카메라 두 개 + Pick & Place
        # ==========================================
        center_col = ctk.CTkFrame(content_wrapper, fg_color=ROOT_BG)
        center_col.grid(row=0, column=1, sticky="nsew", padx=10)

        cam_row = ctk.CTkFrame(center_col, fg_color=ROOT_BG)
        cam_row.pack(fill="both", expand=True, pady=(0, 10))
        cam_row.columnconfigure(0, weight=1)
        cam_row.columnconfigure(1, weight=1)
        cam_row.rowconfigure(0, weight=1)

        # 왼쪽 카메라: 모니터링 (233522074207)
        cam_left_frame = ctk.CTkFrame(cam_row, corner_radius=25, fg_color=PANEL_BG,
                                      border_width=2, border_color="#333333")
        cam_left_frame.grid(row=0, column=0, sticky="nsew", padx=(0, 5))
        ctk.CTkLabel(cam_left_frame, text="Monitor Cam  (S/N: 233522074207)",
                     font=ctk.CTkFont(size=FS_CAM_LABEL), text_color="#888888").pack(pady=(8, 0))
        # [수정] font=FS_STATUS(30) 추가 → 에러/안내 텍스트도 동일 크기로 표시
        self.lbl_video = ctk.CTkLabel(cam_left_frame, text="Initializing...",
                                      fg_color="black", corner_radius=15, bg_color=PANEL_BG,
                                      font=ctk.CTkFont(size=FS_STATUS))
        self.lbl_video.pack(expand=True, fill="both", padx=10, pady=(2, 10))

        # 오른쪽 카메라: 스켈레톤 (233522076563, /vision_frame)
        cam_right_frame = ctk.CTkFrame(cam_row, corner_radius=25, fg_color=PANEL_BG,
                                       border_width=2, border_color="#333333")
        cam_right_frame.grid(row=0, column=1, sticky="nsew", padx=(5, 0))
        ctk.CTkLabel(cam_right_frame, text="Skeleton Cam  (S/N: 233522076563)",
                     font=ctk.CTkFont(size=FS_CAM_LABEL), text_color="#888888").pack(pady=(8, 0))
        self.lbl_vision_frame = ctk.CTkLabel(cam_right_frame, text="RealSense 버튼을 눌러 시작",
                                             fg_color="black", corner_radius=15, bg_color=PANEL_BG,
                                             font=ctk.CTkFont(size=FS_STATUS))
        self.lbl_vision_frame.pack(expand=True, fill="both", padx=10, pady=(2, 10))

        # Pick & Place
        pnp_frame = ctk.CTkFrame(center_col, corner_radius=25, fg_color=PANEL_BG,
                                 border_width=2, border_color="#333333")
        pnp_frame.pack(fill="x", pady=(10, 0), ipady=10)
        ctk.CTkLabel(pnp_frame, text="Pick & Place Test",
                     font=ctk.CTkFont(size=FS_PANEL_TITLE, weight="bold")).pack(pady=5)
        self.lbl_timer = ctk.CTkLabel(pnp_frame, text="02:00", text_color="#00E5FF",
                                      font=ctk.CTkFont(family="Consolas", size=FS_TIMER, weight="bold"))
        self.lbl_timer.pack(pady=5)
        pnp_btn_f = ctk.CTkFrame(pnp_frame, fg_color="transparent")
        pnp_btn_f.pack(pady=5)
        self.btn_pnp_start = ctk.CTkButton(pnp_btn_f, text="Start Timer", width=150, height=48,
                                           corner_radius=12, fg_color="#0277BD",
                                           font=ctk.CTkFont(size=FS_BTN, weight="bold"),
                                           command=lambda: self.start_trial("pnp"))
        self.btn_pnp_start.pack(side="left", padx=10)
        self.btn_pnp_reset = ctk.CTkButton(pnp_btn_f, text="Reset", width=110, height=48,
                                           corner_radius=12, fg_color="#455A64",
                                           font=ctk.CTkFont(size=FS_BTN, weight="bold"),
                                           command=self.reset_pnp)
        self.btn_pnp_reset.pack(side="left", padx=10)

        # ==========================================
        # [오른쪽 컬럼]: Payload / Latency / Robot State
        # ==========================================
        right_col = ctk.CTkFrame(content_wrapper, fg_color=ROOT_BG)
        right_col.grid(row=0, column=2, sticky="nsew", padx=(15, 0))

        # Payload
        payload_frame = ctk.CTkFrame(right_col, corner_radius=25, fg_color=PANEL_BG,
                                     border_width=2, border_color="#333333")
        payload_frame.pack(fill="both", expand=True, pady=(0, 10))
        p_inner = ctk.CTkFrame(payload_frame, fg_color="transparent")
        p_inner.pack(expand=True)
        ctk.CTkLabel(p_inner, text="Payload Test (80g)",
                     font=ctk.CTkFont(size=FS_PANEL_TITLE, weight="bold"),
                     text_color="#FFFFFF").pack(pady=(15, 10))
        self.btn_payload_start = ctk.CTkButton(p_inner, text="Execute Payload Test", height=48,
                                               corner_radius=12, fg_color="#0277BD",
                                               font=ctk.CTkFont(size=FS_BTN, weight="bold"),
                                               command=lambda: self.start_trial("payload"))
        self.btn_payload_start.pack(fill="x", padx=20, pady=(0, 15))

        # Latency
        lat_frame = ctk.CTkFrame(right_col, corner_radius=25, fg_color=PANEL_BG,
                                 border_width=2, border_color="#333333")
        lat_frame.pack(fill="both", expand=True, pady=(5, 5))
        l_inner = ctk.CTkFrame(lat_frame, fg_color="transparent")
        l_inner.pack(expand=True)
        ctk.CTkLabel(l_inner, text="Latency Check (ms)",
                     font=ctk.CTkFont(size=FS_PANEL_TITLE, weight="bold")).pack(pady=(10, 5))
        self.lbl_realtime_latency = ctk.CTkLabel(l_inner, text="Real-time Avg: -- ms",
                                                  text_color="#FFFFFF",
                                                  font=ctk.CTkFont(family="Consolas",
                                                                   size=FS_REALTIME_LAT, weight="bold"))
        self.lbl_realtime_latency.pack(pady=5)
        self.btn_lat_start = ctk.CTkButton(l_inner, text="Measure", corner_radius=12, height=48,
                                           fg_color="#0277BD",
                                           font=ctk.CTkFont(size=FS_BTN, weight="bold"),
                                           command=lambda: self.start_trial("latency"))
        self.btn_lat_start.pack(fill="x", padx=20, pady=8)
        self.lat_inds = []
        l_ind_f = ctk.CTkFrame(l_inner, fg_color="transparent")
        l_ind_f.pack(pady=5)
        for i in range(5):
            lbl = ctk.CTkLabel(l_ind_f, text="--",
                                font=ctk.CTkFont(family="Consolas", size=FS_LAT_IND),
                                width=52, fg_color="#212121", corner_radius=8)
            lbl.grid(row=0, column=i, padx=3)
            self.lat_inds.append(lbl)

        # Robot State
        status_frame = ctk.CTkFrame(right_col, corner_radius=25, fg_color=PANEL_BG,
                                    border_width=2, border_color="#333333")
        status_frame.pack(fill="both", expand=True, pady=(10, 0))
        status_inner = ctk.CTkFrame(status_frame, fg_color="transparent")
        status_inner.pack(expand=True, fill="x")
        ctk.CTkLabel(status_inner, text="Robot State",
                     font=ctk.CTkFont(size=FS_PANEL_TITLE, weight="bold"),
                     text_color="#FFFFFF").pack(pady=(12, 5))
        self.lbl_robot_states = ctk.CTkLabel(status_inner, text="Joints(deg): --\nGripper: --",
                                              font=ctk.CTkFont(family="Consolas", size=FS_VALUE_MONO))
        self.lbl_robot_states.pack(pady=5)
        self.lbl_motor_current = ctk.CTkLabel(status_inner, text="Current: 0.0 mA",
                                               font=ctk.CTkFont(family="Consolas", size=FS_VALUE_MONO))
        self.lbl_motor_current.pack(pady=5)

        # ─────────────────────────────────────────────────────────
        # [하단]: 비상 정지 + 로그
        # ─────────────────────────────────────────────────────────
        bottom_wrapper = ctk.CTkFrame(self.root, fg_color=ROOT_BG)
        bottom_wrapper.pack(fill="x", padx=20, pady=(0, 10))
        self.log_area = ctk.CTkTextbox(bottom_wrapper, height=130, corner_radius=15,
                                       fg_color="#000000", text_color="#00FF00",
                                       font=ctk.CTkFont(family="Consolas", size=FS_LOG))
        self.log_area.pack(side="left", fill="both", expand=True, padx=(0, 20))
        self.btn_stop = ctk.CTkButton(bottom_wrapper, text="EMERGENCY\nSTOP",
                                      width=130, height=130, corner_radius=65,
                                      fg_color="#B71C1C", hover_color="#D32F2F",
                                      font=ctk.CTkFont(size=FS_BTN_EMSTOP, weight="bold"),
                                      border_width=4, border_color="#FFCDD2",
                                      command=self.mock_stop_all)
        self.btn_stop.pack(side="right")

    # ─────────────────────────────────────────────────────────────
    # 유틸리티
    # ─────────────────────────────────────────────────────────────
    def log_message(self, msg):
        self.log_area.configure(state="normal")
        self.log_area.insert("end", f"[{time.strftime('%H:%M:%S')}] {msg}\n")
        self.log_area.see("end")
        self.log_area.configure(state="disabled")

    def update_payload_current(self, current_val):
        self.lbl_motor_current.configure(text=f"Current load: {current_val} %")

    def update_robot_states(self, state_str):
        self.lbl_robot_states.configure(text=state_str)

    # ─────────────────────────────────────────────────────────────
    # 첫 번째 카메라: 모니터링 피드 (233522074207)
    # ─────────────────────────────────────────────────────────────
    def open_camera(self):
        if not self.video_running:
            try:
                self.rs_pipeline = rs.pipeline()
                config = rs.config()
                config.enable_device("233522074207")
                config.enable_stream(rs.stream.color, 640, 480, rs.format.bgr8, 30)
                self.rs_pipeline.start(config)
                self.video_running = True
                self.update_video_frame()
                self.log_message("Monitor cam started (S/N: 233522074207).")
            except Exception as e:
                self.lbl_video.configure(text=f"RealSense Error:\n{e}", text_color="#FF5252")
                self.log_message(f"Monitor cam init failed: {e}")

    def update_video_frame(self):
        try:
            if self.video_running and self.rs_pipeline:
                frames      = self.rs_pipeline.wait_for_frames()
                color_frame = frames.get_color_frame()
                if color_frame:
                    frame     = np.asanyarray(color_frame.get_data())
                    frame     = cv2.resize(frame, (640, 360))
                    frame_rgb = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
                    img       = Image.fromarray(frame_rgb)
                    imgtk     = ctk.CTkImage(light_image=img, dark_image=img, size=(640, 360))
                    self.lbl_video.configure(image=imgtk, text="")
                self.root.after(30, self.update_video_frame)
        except Exception:
            pass

    # ─────────────────────────────────────────────────────────────
    # 두 번째 카메라: /vision_frame 토픽
    # ─────────────────────────────────────────────────────────────
    def update_vision_frame(self, bgr_frame: np.ndarray):
        try:
            frame     = cv2.resize(bgr_frame, (640, 360))
            frame_rgb = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
            img       = Image.fromarray(frame_rgb)
            imgtk     = ctk.CTkImage(light_image=img, dark_image=img, size=(640, 360))
            self.lbl_vision_frame.configure(image=imgtk, text="")
        except Exception:
            pass

    # ─────────────────────────────────────────────────────────────
    # 노드 제어
    # ─────────────────────────────────────────────────────────────
    def toggle_realsense(self):
        if not self.realsense_online:
            if _launch_ros2_run(WORKSPACE_SETUP, "avatar", "vision_nav.py", [], "RealSense", "realsense_key"):
                self.realsense_online = True
                self.lbl_rs_status.configure(text="[ D435i Online ]", text_color="#4CAF50")
                self.btn_realsense.configure(text="Stop RealSense", fg_color="#D81B60")
                self.lbl_vision_frame.configure(text="연결 중...", text_color="#FFB300")
                self.log_message("vision_nav.py started — waiting for /vision_frame ...")
        else:
            _cleanup_processes_by_key("realsense_key")
            self.realsense_online = False
            self.lbl_rs_status.configure(text="[ D435i Offline ]", text_color="#FF5252")
            self.btn_realsense.configure(text="Start RealSense", fg_color="#0277BD")
            self.lbl_vision_frame.configure(image=None, text="RealSense 버튼을 눌러 시작",
                                            text_color="#888888")
            self.log_message("vision_nav.py stopped.")

    def toggle_clock(self):
        if not self.clock_online:
            if _launch_ros2_run(WORKSPACE_SETUP, "avatar", "clock.py", [], "Clock", "clock_key"):
                self.clock_online = True
                self.lbl_clock_status.configure(text="[ Clock Online ]", text_color="#4CAF50")
                self.btn_clock.configure(text="Stop Clock", fg_color="#D81B60")
                self.log_message("Clock node started.")
        else:
            _cleanup_processes_by_key("clock_key")
            self.clock_online = False
            self.lbl_clock_status.configure(text="[ Clock Offline ]", text_color="#FF5252")
            self.btn_clock.configure(text="Start Clock", fg_color="#0277BD")
            self.log_message("Clock node stopped.")

    # ─────────────────────────────────────────────────────────────
    # Planning
    # ─────────────────────────────────────────────────────────────
    def _tts_and_launch_planning(self):
        try:
            from gtts import gTTS
            import playsound
            text     = "자리에 앉아서 차렷자세를 취해주세요. 3초 후에 시작합니다."
            filename = "/tmp/planning_announce.mp3"
            gTTS(text=text, lang='ko').save(filename)
            playsound.playsound(filename)
            if os.path.exists(filename):
                os.remove(filename)
        except Exception as e:
            print(f"[TTS] Error: {e}")

        import time as _time
        for n in range(3, 0, -1):
            self.root.after(0, self.lbl_countdown.configure, {"text": str(n)})
            self.root.after(0, self.lbl_robot_status.configure,
                            {"text": f"[ Starting in {n}s... ]", "text_color": "#FF5252"})
            _time.sleep(1)

        self.root.after(0, self.lbl_countdown.configure, {"text": ""})

        if _launch_ros2_run(WORKSPACE_SETUP, "avatar", "dxl_subscriber.py", None, "RobotPlanning", "planning_key"):
            self.root.after(0, self.lbl_robot_status.configure,
                            {"text": "[ Planning Online ]", "text_color": "#0277BD"})
            self.root.after(0, self.btn_planning.configure, {"state": "disabled"})
            self.root.after(0, self.log_message, "Planning node started.")
            _time.sleep(4)
            try:
                from gtts import gTTS
                import playsound
                tts2 = gTTS(text="이제 텔레오퍼레이션을 시작해주세요.", lang='ko')
                tts2.save("/tmp/teleop_start.mp3")
                playsound.playsound("/tmp/teleop_start.mp3")
                if os.path.exists("/tmp/teleop_start.mp3"):
                    os.remove("/tmp/teleop_start.mp3")
            except Exception as e:
                print(f"[TTS] Error: {e}")
        else:
            self.root.after(0, self.lbl_robot_status.configure,
                            {"text": "[ Planning Offline ]", "text_color": "#FF5252"})
            self.root.after(0, self.btn_planning.configure, {"state": "normal"})
            self.root.after(0, self.log_message, "Failed to start planning node.")

    def start_planning_with_tts(self):
        self.btn_planning.configure(state="disabled")
        self.lbl_robot_status.configure(text="[ Preparing... ]", text_color="#FFB300")
        self.log_message("TTS 안내 중 — 3초 후 Planning 노드 시작 예정.")
        threading.Thread(target=self._tts_and_launch_planning, daemon=True).start()

    # ─────────────────────────────────────────────────────────────
    # Trials
    # ─────────────────────────────────────────────────────────────
    def start_trial(self, t_type):
        if t_type == "payload":
            if not self.payload_online:
                self.log_message("Starting Payload Test (80g)...")
                if _launch_ros2_run(WORKSPACE_SETUP, "avatar", "payload_test.py", [], "PayloadTest", "payload_key"):
                    self.payload_online = True
                    self.btn_payload_start.configure(text="Stop Payload Test", fg_color="#D81B60")
                    self.log_message("payload_test.py node started.")
                else:
                    self.log_message("Failed to start payload test node.")
            else:
                _cleanup_processes_by_key("payload_key")
                self.payload_online = False
                self.btn_payload_start.configure(text="Execute Payload Test", fg_color="#0277BD")
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
            mins = self.pnp_time_left // 60
            secs = self.pnp_time_left % 60
            self.lbl_timer.configure(text=f"{mins:02d}:{secs:02d}")
            self.pnp_time_left -= 1
            self.root.after(1000, self.update_timer)
        elif self.pnp_time_left <= 0:
            self.lbl_timer.configure(text="00:00", text_color="#FF5252")
            self.pnp_timer_running = False
            self.btn_pnp_start.configure(state="normal")
            self.log_message("Pick & Place Timer Finished.")

    def reset_pnp(self):
        self.pnp_timer_running = False
        self.pnp_time_left     = 120
        self.lbl_timer.configure(text="02:00", text_color="#00E5FF")
        self.btn_pnp_start.configure(state="normal")
        self.log_message("PnP Timer Reset.")

    def update_latency_buffer(self, new_val):
        self.latency_buffer.append(new_val)
        self.current_avg_latency = sum(self.latency_buffer) / len(self.latency_buffer)
        self.lbl_realtime_latency.configure(
            text=f"Real-time Avg: {int(self.current_avg_latency)} ms")

    def record_latency(self):
        if not self.latency_buffer:
            self.log_message("Warning: No latency data received yet.")
            return
        val = int(self.current_avg_latency)
        self.lat_inds[self.latency_trial].configure(text=f"{val}")
        self.latency_trial += 1
        if self.latency_trial < self.max_latency_trials:
            self.btn_lat_start.configure(state="normal")
        else:
            self.btn_lat_start.configure(text="Done", state="disabled")
        self.log_message(f"Latency Recorded: {val} ms (Averaged)")

    # ─────────────────────────────────────────────────────────────
    # 비상 정지
    # ─────────────────────────────────────────────────────────────
    def mock_stop_all(self):
        _cleanup_processes_by_key("realsense_key")
        _cleanup_processes_by_key("planning_key")
        _cleanup_processes_by_key("clock_key")
        _cleanup_processes_by_key("payload_key")

        self.video_running = False
        if hasattr(self, 'rs_pipeline') and self.rs_pipeline:
            self.rs_pipeline.stop()
            self.rs_pipeline = None

        self.realsense_online  = False
        self.clock_online      = False
        self.payload_online    = False
        self.pnp_timer_running = False

        self.lbl_rs_status.configure(text="[ D435i Offline ]",      text_color="#FF5252")
        self.lbl_clock_status.configure(text="[ Clock Offline ]",    text_color="#FF5252")
        self.lbl_robot_status.configure(text="[ Planning Offline ]", text_color="#FF5252")
        self.lbl_countdown.configure(text="")

        self.btn_realsense.configure(text="Start RealSense",          fg_color="#0277BD")
        self.btn_clock.configure(text="Start Clock",                  fg_color="#0277BD")
        self.btn_payload_start.configure(text="Execute Payload Test", fg_color="#0277BD")
        self.btn_planning.configure(state="normal")

        self.lbl_vision_frame.configure(image=None, text="RealSense 버튼을 눌러 시작",
                                        text_color="#888888")
        self.log_message("Emergency Stop Initiated.")


def main(args=None):
    root = ctk.CTk()
    app  = VisualTestGUI(root)

    def on_closing():
        app.video_running = False
        if hasattr(app, 'rs_pipeline') and app.rs_pipeline:
            app.rs_pipeline.stop()
        _cleanup_processes_by_key("realsense_key")
        _cleanup_processes_by_key("planning_key")
        _cleanup_processes_by_key("clock_key")
        _cleanup_processes_by_key("payload_key")
        os._exit(0)

    root.protocol("WM_DELETE_WINDOW", on_closing)
    root.mainloop()


if __name__ == "__main__":
    main()