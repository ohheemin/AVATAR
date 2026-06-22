#!/usr/bin/env python3
"""
AVATAR TELEOPERATION AGENT  v3
레이아웃 전면 재설계:

[v3 변경사항]
1. 4-column 비율 재설계 (2560px 기준)
   left  300px : weight=3, minsize=300, maxsize=320
   center 820px: weight=8, minsize=700, maxsize=900
   right  300px: weight=3, minsize=300, maxsize=320
   chat   500px: weight=5, minsize=480, maxsize=600
   → 카메라 2개 각 ~400px 가로 확보, 좌우 패널 글씨 잘림 해결

2. _panel 헤더 폰트 크기 축소 (20→16) + 제목 줄임말 제거
   → 좌측 패널에서 제목이 잘리지 않도록

3. 버튼 폰트 크기 축소 (20→16), 높이 축소 (52→46)
   → 좁은 좌측/우측 컬럼에서 글씨 잘림 방지

4. cam_row: grid_propagate(False) 제거, sticky="nsew" 명시
   → 카메라 패널이 cam_row 안에서 제대로 확장되도록

5. 카메라 lbl height를 pack(expand=True, fill="both")로 확장
   → 세로 방향으로도 꽉 채워지도록

6. chat column weight 5로 축소 (9→5): 너무 넓던 문제 해결

[유지]
- ctk.CTkToplevel 스플래시 (tk.Tk 제거)
- pack_propagate(False) on camera panels
- 동적 카메라 크기 계산 _get_cam_display_size
- E-STOP 로직 전체
- ROS2 / LLM / STT 전체
"""

import customtkinter as ctk
import time, os, cv2, subprocess, threading, signal, tempfile, queue
from collections import deque
from PIL import Image

import rclpy
from rclpy.node import Node
from sensor_msgs.msg import JointState, CompressedImage
from std_msgs.msg import Float64, Int32

import pyrealsense2 as rs
import numpy as np
import torch
from transformers import AutoModelForCausalLM, AutoTokenizer
import sounddevice as sd
import scipy.io.wavfile as wavfile

# ══════════════════════════════════════════════════════════════
# 색상 팔레트
# ══════════════════════════════════════════════════════════════
C_BG         = "#DDE3EA"
C_SURFACE    = "#FFFFFF"
C_SURFACE2   = "#F0F4F8"
C_BORDER     = "#B0BEC5"
C_ACCENT     = "#1565C0"
C_ACCENT_DIM = "#1976D2"
C_ACCENT2    = "#E65100"
C_ESTOP_BG   = "#FFEBEE"
C_ESTOP_RIM  = "#C62828"
C_GREEN      = "#2E7D32"
C_RED        = "#C62828"
C_YELLOW     = "#E65100"
C_CYAN       = "#00838F"
C_TEXT       = "#0D1B2A"
C_TEXT_DIM   = "#78909C"
C_TEXT_MID   = "#37474F"
C_HEADER     = "#0F2744"
C_CHAT_BG    = "#E8F0F7"
C_CHAT_USER  = "#FAE100"
C_CHAT_BOT   = "#FFFFFF"
C_CHAT_SYS   = "#ECEFF1"
C_CHAT_ACT   = "#E8F5E9"
C_CHAT_ESTOP = "#FFCDD2"

F_MONO = "Consolas"
F_SANS = "Malgun Gothic"

ctk.set_appearance_mode("Light")
ctk.set_default_color_theme("blue")

# ══════════════════════════════════════════════════════════════
# E-STOP 키워드
# ══════════════════════════════════════════════════════════════
ESTOP_KEYWORDS = [
    "정지","멈춰","멈춰라","중단","중지","비상","긴급","위험",
    "즉시 멈춰","즉시 정지","로봇 멈춰","로봇 정지","로봇 중단",
    "작동 중지","작동 멈춰","모두 멈춰","전부 멈춰","전체 정지",
    "시스템 정지","시스템 중지","충돌","사고",
    "stop","halt","emergency","abort","freeze","danger",
    "stop all","halt all","emergency stop","e-stop",
    "shut down","shutdown","kill","collision",
]

def _has_estop_keyword(text: str) -> bool:
    return any(kw in text.lower() for kw in ESTOP_KEYWORDS)

# ══════════════════════════════════════════════════════════════
# LLM
# ══════════════════════════════════════════════════════════════
_model       = None
_tokenizer   = None
_model_ready = False

def _load_model_bg(callback):
    global _model, _tokenizer, _model_ready
    _model = AutoModelForCausalLM.from_pretrained(
        "./avatar_merged", trust_remote_code=True,
        torch_dtype=torch.float16, device_map="auto")
    _tokenizer = AutoTokenizer.from_pretrained(
        "./avatar_merged", trust_remote_code=True)
    _model.eval()
    _model_ready = True
    _load_whisper()
    callback()

def llm_chat(instruction):
    prompt = (
        "[|system|]당신은 아바타입니다. "
        "로봇팔 제어와 3D pose estimation을 돕는 AI 어시스턴트입니다.[|endofturn|]\n"
        f"[|user|]{instruction}[|endofturn|]\n[|assistant|]"
    )
    inputs = _tokenizer(prompt, return_tensors="pt").to(_model.device)
    with torch.no_grad():
        outputs = _model.generate(
            **inputs, max_new_tokens=256, do_sample=False,
            eos_token_id=_tokenizer.eos_token_id)
    return _tokenizer.decode(
        outputs[0][inputs["input_ids"].shape[1]:],
        skip_special_tokens=True).strip()

# ══════════════════════════════════════════════════════════════
# STT
# ══════════════════════════════════════════════════════════════
_whisper       = None
_whisper_ready = False
SAMPLE_RATE    = 16000
SILENCE_THRESH = 0.02
SILENCE_FRAMES = 25

def _load_whisper():
    global _whisper, _whisper_ready
    try:
        from faster_whisper import WhisperModel
        dev = "cuda" if torch.cuda.is_available() else "cpu"
        cmp = "float16" if torch.cuda.is_available() else "int8"
        _whisper = WhisperModel("tiny", device=dev, compute_type=cmp)
        _whisper_ready = True
    except Exception as e:
        print(f"[Whisper] 로드 실패: {e}")

def _record_until_silence():
    chunk = int(SAMPLE_RATE * 0.1)
    frames, silent_count, started = [], 0, False
    with sd.InputStream(samplerate=SAMPLE_RATE, channels=1,
                        dtype="float32", blocksize=chunk) as stream:
        while True:
            data, _ = stream.read(chunk)
            frames.append(data.copy())
            vol = float(np.abs(data).mean())
            if vol > SILENCE_THRESH:
                started = True; silent_count = 0
            elif started:
                silent_count += 1
                if silent_count >= SILENCE_FRAMES: break
            if len(frames) > int(SAMPLE_RATE / chunk * 30): break
    return np.concatenate(frames).flatten()

def _stt(audio):
    with tempfile.NamedTemporaryFile(suffix=".wav", delete=False) as f:
        tmp = f.name
        wavfile.write(tmp, SAMPLE_RATE, (audio * 32767).astype(np.int16))
    try:
        segs, _ = _whisper.transcribe(tmp, language="ko", beam_size=5, vad_filter=True)
        return " ".join(s.text for s in segs).strip()
    finally:
        os.unlink(tmp)

# ══════════════════════════════════════════════════════════════
# ROS2 프로세스 관리
# ══════════════════════════════════════════════════════════════
_proc_lock = threading.Lock()
_procs     = {}
WORKSPACE_SETUP = os.path.expanduser("~/ros2_ws/install/setup.bash")

def _ros2_run(pkg, exe, args=None, key=None):
    cmd = ["ros2", "run", pkg, exe] + (args or [])
    src = (f"source {WORKSPACE_SETUP}" if os.path.exists(WORKSPACE_SETUP)
           else "echo 'no setup'")
    bash = f"source /opt/ros/humble/setup.bash && {src} && {' '.join(cmd)}"
    try:
        with _proc_lock:
            if key:
                ex = _procs.get(key)
                if ex and ex.poll() is None: return True
            proc = subprocess.Popen(["bash", "-c", bash], preexec_fn=os.setsid)
            if key: _procs[key] = proc
        return True
    except Exception as e:
        print(f"[ERROR] {e}"); return False

def _kill(key):
    with _proc_lock:
        proc = _procs.get(key)
        if proc and proc.poll() is None:
            try:
                os.killpg(os.getpgid(proc.pid), signal.SIGINT)
                proc.wait(timeout=3)
            except Exception:
                try: os.killpg(os.getpgid(proc.pid), signal.SIGKILL)
                except: pass
            _procs[key] = None

# ══════════════════════════════════════════════════════════════
# ROS2 Node
# ══════════════════════════════════════════════════════════════
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
    def __init__(self, app):
        super().__init__('teleop_gui_monitor')
        self.app = app
        self.create_subscription(Int32,           '/payload',          self._cb_payload, 10)
        self.create_subscription(JointState,      '/joint_states',     self._cb_joint,   10)
        self.create_subscription(Float64,         '/calculated_clock', self._cb_clock,   10)
        self.create_subscription(CompressedImage, '/vision_frame',     self._cb_frame,   10)

    def _cb_payload(self, msg):
        self.app.root.after(0, self.app.update_payload_current, msg.data)

    def _cb_joint(self, msg):
        try:
            js = ", ".join([f"{v:.2f}" for v in msg.position[:3]])
            gv = msg.position[-1] if msg.position else 0.0
            gs = "OPEN" if gv > 0.5 else "CLOSED"
            self.app.root.after(0, self.app.update_robot_states,
                                f"Joints(deg): [{js}]\nGripper: {gs}")
        except: pass

    def _cb_clock(self, msg):
        self.app.root.after(0, self.app.update_latency_buffer, msg.data)

    def _cb_frame(self, msg):
        try:
            self.app._ros_frame_queue.put_nowait(bytes(msg.data))
        except queue.Full:
            pass
        except: pass

# ══════════════════════════════════════════════════════════════
# 위젯 헬퍼
# ══════════════════════════════════════════════════════════════
def _panel(parent, title=None, **kwargs):
    f = ctk.CTkFrame(parent, fg_color=C_SURFACE, corner_radius=10,
                     border_width=1, border_color=C_BORDER, **kwargs)
    if title:
        hdr = ctk.CTkFrame(f, fg_color=C_HEADER, corner_radius=0, height=48)
        hdr.pack(fill="x")
        hdr.pack_propagate(False)
        ctk.CTkFrame(hdr, fg_color=C_ACCENT, width=4,
                     corner_radius=0).pack(side="left", fill="y")
        ctk.CTkLabel(hdr, text=f"  {title}",
                     font=ctk.CTkFont(F_MONO, 16, "bold"),   # 20→16
                     text_color="#FFFFFF", anchor="w").pack(fill="x", padx=8, pady=12)
    return f

def _status_dot(parent, color):
    return ctk.CTkLabel(parent, text="◉", font=ctk.CTkFont(size=17),
                        text_color=color, fg_color="transparent")

def _ind_label(parent, text, color=C_TEXT_DIM):
    return ctk.CTkLabel(parent, text=text, font=ctk.CTkFont(F_MONO, 17),
                        text_color=color, fg_color="transparent")

def _btn(parent, text, cmd, color=C_SURFACE2, width=None,
         height=46, accent=C_ACCENT, **kw):          # height 52→46
    kargs = dict(text=text, command=cmd, fg_color=color,
                 hover_color="#DBEAFE", border_width=2, border_color=accent,
                 text_color=accent, font=ctk.CTkFont(F_MONO, 16, "bold"),  # 20→16
                 height=height, corner_radius=12)
    if width: kargs["width"] = width
    kargs.update(kw)
    return ctk.CTkButton(parent, **kargs)

# ══════════════════════════════════════════════════════════════
# 스플래시 — ctk.CTkToplevel 기반 (tk.Tk 완전 제거)
# ══════════════════════════════════════════════════════════════
def run_splash(root: ctk.CTk):
    root.withdraw()
    splash = ctk.CTkToplevel(root)
    splash.overrideredirect(True)
    splash.attributes("-topmost", True)
    W, H = 740, 660
    sw = splash.winfo_screenwidth()
    sh = splash.winfo_screenheight()
    splash.geometry(f"{W}x{H}+{(sw-W)//2}+{(sh-H)//2}")
    splash.configure(fg_color="#1565C0")

    card = ctk.CTkFrame(splash, fg_color="#F4F7FB", corner_radius=0, border_width=0)
    card.pack(fill="both", expand=True, padx=6, pady=6)

    try:
        _logo_dir = os.path.dirname(os.path.abspath(__file__))
        _logo_pil = Image.open(os.path.join(_logo_dir, "avatar_logo.png")).convert("RGBA")
        _logo_pil = _logo_pil.resize((480, 320), Image.LANCZOS)
        _logo_ctk = ctk.CTkImage(light_image=_logo_pil, size=(480, 320))
        ctk.CTkLabel(card, image=_logo_ctk, text="", fg_color="transparent").pack(pady=(28, 0))
    except Exception:
        ctk.CTkLabel(card, text="AVATAR",
                     font=ctk.CTkFont(F_MONO, 64, "bold"),
                     text_color="#1565C0", fg_color="transparent").pack(pady=(60, 0))

    ctk.CTkLabel(card, text="AVATAR TELEOPERATION AGENT",
                 font=ctk.CTkFont(F_MONO, 20, "bold"),
                 text_color="#1565C0", fg_color="transparent").pack(pady=(8, 0))
    ctk.CTkFrame(card, fg_color="#B0C8E8", height=2,
                 corner_radius=0).pack(fill="x", padx=70, pady=(22, 0))
    lbl_status = ctk.CTkLabel(card, text="시스템 초기화 중...",
                              font=ctk.CTkFont(F_SANS, 17),
                              text_color="#546E7A", fg_color="transparent")
    lbl_status.pack(pady=(16, 0))
    bar = ctk.CTkProgressBar(card, width=480, height=12, corner_radius=6,
                             fg_color="#D8E4F0", progress_color="#1565C0")
    bar.pack(pady=(12, 0))
    bar.set(0)

    steps = [
        (0.15, "ROS2 환경 확인 중..."),
        (0.35, "카메라 모듈 로드 중..."),
        (0.55, "LLM 모델 초기화 중..."),
        (0.75, "음성 인식 엔진 준비 중..."),
        (0.95, "UI 빌드 중..."),
        (1.00, "완료!"),
    ]
    state = {"step": 0}

    def tick():
        i = state["step"]
        if i < len(steps):
            val, msg = steps[i]
            bar.set(val); lbl_status.configure(text=msg)
            state["step"] += 1
            splash.after(480 if i + 1 < len(steps) else 700, tick)
        else:
            splash.after(200, _finish)

    def _finish():
        splash.destroy()
        root.deiconify()

    splash.after(350, tick)

# ══════════════════════════════════════════════════════════════
# 메인 앱
# ══════════════════════════════════════════════════════════════
class CombinedGUI:
    _CHAT_INPUT_H = 70
    _CHAT_BTN_W   = 34
    _CHAT_BTN_H   = 34
    _CHAT_AREA_H  = 90

    def __init__(self, root):
        self.root = root
        self.root.title("AVATAR TELEOPERATION AGENT")
        self.root.geometry("2560x1440")

        self.realsense_online = False
        self.clock_online     = False
        self.payload_online   = False
        self.rs_pipeline      = None
        self.pnp_time_left    = 120
        self.pnp_running      = False
        self.pnp_start_time   = None   # 타이머 시작 시각 (time.time())
        self.latency_trial    = 0
        self.max_lat_trials   = 5
        self.latency_buffer   = deque(maxlen=100)
        self.current_avg_lat  = 0.0
        self.save_latency     = DataBuffer(100, 1)
        self._estop_active    = False

        self._cam01_imgtk = None
        self._cam02_imgtk = None
        self._cam01_queue     = queue.Queue(maxsize=2)
        self._ros_frame_queue = queue.Queue(maxsize=2)
        self._cam_stop_event  = threading.Event()

        self._build_ui()

        self.root.after(600, self._init_ros)
        self.root.after(300, self.open_camera)
        self.root.after(33, self._poll_cam01)
        self.root.after(33, self._poll_cam02)

        threading.Thread(
            target=_load_model_bg,
            args=(lambda: self.root.after(0, self._on_model_ready),),
            daemon=True).start()

    # ── 동적 카메라 표시 크기 ────────────────────────────────
    def _get_cam_display_size(self, label_widget):
        try:
            w = label_widget.winfo_width()
            h = label_widget.winfo_height()
            if w > 20 and h > 20:
                w = max(w - 6, 80)
                h = max(h - 6, 50)
                # 16:9 비율 유지 — 가로 기준
                h_by_w = int(w * 9 / 16)
                if h_by_w <= h:
                    return w, h_by_w
                else:
                    return int(h * 16 / 9), h
        except Exception:
            pass
        return 400, 225  # 기본값

    # ── 큐 폴러 ──────────────────────────────────────────────
    def _poll_cam01(self):
        try:
            rgb = self._cam01_queue.get_nowait()
            dw, dh = self._get_cam_display_size(self.lbl_video)
            img   = Image.fromarray(rgb).resize((dw, dh), Image.LANCZOS)
            imgtk = ctk.CTkImage(light_image=img, dark_image=img, size=(dw, dh))
            self._cam01_imgtk = imgtk
            self.lbl_video.configure(image=imgtk, text="")
        except queue.Empty:
            pass
        except Exception:
            pass
        self.root.after(33, self._poll_cam01)

    def _poll_cam02(self):
        try:
            raw   = self._ros_frame_queue.get_nowait()
            buf   = np.frombuffer(raw, dtype=np.uint8)
            frame = cv2.imdecode(buf, cv2.IMREAD_COLOR)
            if frame is not None:
                dw, dh = self._get_cam_display_size(self.lbl_vision_frame)
                frame = cv2.resize(frame, (dw, dh))
                rgb   = frame[:, :, ::-1].copy()
                img   = Image.fromarray(rgb)
                imgtk = ctk.CTkImage(light_image=img, dark_image=img, size=(dw, dh))
                self._cam02_imgtk = imgtk
                self.lbl_vision_frame.configure(image=imgtk, text="")
        except queue.Empty:
            pass
        except Exception:
            pass
        self.root.after(33, self._poll_cam02)

    # ── UI 빌드 ──────────────────────────────────────────────
    def _build_ui(self):
        titlebar = ctk.CTkFrame(self.root, fg_color=C_HEADER,
                                corner_radius=0, height=60)
        titlebar.pack(fill="x")
        titlebar.pack_propagate(False)
        ctk.CTkFrame(titlebar, fg_color=C_ACCENT, width=5,
                     corner_radius=0).pack(side="left", fill="y")
        ctk.CTkLabel(titlebar, text="  AVATAR TELEOPERATION AGENT",
                     font=ctk.CTkFont(F_MONO, 26, "bold"),
                     text_color="#FFFFFF").pack(side="left", padx=14, pady=14)
        self.lbl_sys_time = ctk.CTkLabel(titlebar, text="",
                                         font=ctk.CTkFont(F_MONO, 20),
                                         text_color="#B0C8E8")
        self.lbl_sys_time.pack(side="right", padx=20)
        self._tick_clock()
        ctk.CTkLabel(titlebar, text="SYS: ONLINE",
                     font=ctk.CTkFont(F_MONO, 19, "bold"),
                     text_color="#90EE90").pack(side="right", padx=16)

        main = ctk.CTkFrame(self.root, fg_color=C_BG, corner_radius=0)
        main.pack(fill="both", expand=True, padx=6, pady=(4, 4))

        # ══════════════════════════════════════════════════════
        # [v3] 컬럼 비율 재설계
        # 2560px 창 기준 목표 배분:
        #   col0 left   : 300px  weight=3  minsize=290
        #   col1 center : 820px  weight=8  minsize=680  (카메라 2개 각 ~400px)
        #   col2 right  : 300px  weight=3  minsize=290
        #   col3 chat   : 500px  weight=5  minsize=460
        # 합계 weight=19, 2560 / 19 ≈ 134px per weight unit
        # ══════════════════════════════════════════════════════
        col_cfgs = [
            (3, 290),   # col0 left
            (8, 680),   # col1 center
            (3, 290),   # col2 right
            (3, 307),   # col3 chat  ← 기존 대비 2/3 (weight 5→3, minsize 460→307)
        ]
        for c, (w, mn) in enumerate(col_cfgs):
            main.columnconfigure(c, weight=w, minsize=mn)
        main.rowconfigure(0, weight=1)

        self._build_left(main)
        self._build_center(main)
        self._build_right(main)
        self._build_chat(main)
        self._build_test_panels()
        self._build_bottom()

    # ── Left column ──────────────────────────────────────────
    def _build_left(self, parent):
        col = ctk.CTkFrame(parent, fg_color=C_BG, corner_radius=0)
        col.grid(row=0, column=0, sticky="nsew", padx=(0, 3))

        # VISION NODE
        p = _panel(col, "VISION NODE  ·  REALSENSE")
        p.pack(fill="both", expand=True, pady=(0, 3))
        inn = ctk.CTkFrame(p, fg_color="transparent")
        inn.pack(fill="x", padx=10, pady=10)
        row = ctk.CTkFrame(inn, fg_color="transparent")
        row.pack(fill="x", pady=(0, 8))
        _ind_label(row, "STATUS ").pack(side="left")
        self._dot_rs = _status_dot(row, C_RED)
        self._dot_rs.pack(side="left", padx=3)
        self.lbl_rs_status = ctk.CTkLabel(row, text="OFFLINE",
                                          font=ctk.CTkFont(F_MONO, 18, "bold"),
                                          text_color=C_RED, fg_color="transparent")
        self.lbl_rs_status.pack(side="left")
        self.btn_rs = _btn(inn, "START VISION NODE", self.toggle_realsense)
        self.btn_rs.pack(fill="x", pady=(2, 0))

        # PLANNING NODE
        p2 = _panel(col, "PLANNING NODE  ·  DYNAMIXEL")
        p2.pack(fill="both", expand=True, pady=(0, 3))
        inn2 = ctk.CTkFrame(p2, fg_color="transparent")
        inn2.pack(fill="x", padx=10, pady=10)
        row2 = ctk.CTkFrame(inn2, fg_color="transparent")
        row2.pack(fill="x", pady=(0, 8))
        _ind_label(row2, "STATUS ").pack(side="left")
        self._dot_plan = _status_dot(row2, C_RED)
        self._dot_plan.pack(side="left", padx=3)
        self.lbl_robot_status = ctk.CTkLabel(row2, text="OFFLINE",
                                             font=ctk.CTkFont(F_MONO, 18, "bold"),
                                             text_color=C_RED, fg_color="transparent")
        self.lbl_robot_status.pack(side="left")
        self.lbl_countdown = ctk.CTkLabel(inn2, text="",
                                          font=ctk.CTkFont(F_MONO, 60, "bold"),
                                          text_color=C_ACCENT2, fg_color="transparent")
        self.lbl_countdown.pack()
        self.btn_planning = _btn(inn2, "START PLANNING NODE",
                                 self.start_planning_with_tts)
        self.btn_planning.pack(fill="x", pady=(2, 0))

        # CLOCK NODE
        p3 = _panel(col, "CLOCK NODE  ·  LATENCY")
        p3.pack(fill="both", expand=True)
        inn3 = ctk.CTkFrame(p3, fg_color="transparent")
        inn3.pack(fill="x", padx=10, pady=10)
        row3 = ctk.CTkFrame(inn3, fg_color="transparent")
        row3.pack(fill="x", pady=(0, 8))
        _ind_label(row3, "STATUS ").pack(side="left")
        self._dot_clk = _status_dot(row3, C_RED)
        self._dot_clk.pack(side="left", padx=3)
        self.lbl_clock_status = ctk.CTkLabel(row3, text="OFFLINE",
                                             font=ctk.CTkFont(F_MONO, 18, "bold"),
                                             text_color=C_RED, fg_color="transparent")
        self.lbl_clock_status.pack(side="left")
        self.btn_clock = _btn(inn3, "START CLOCK NODE", self.toggle_clock)
        self.btn_clock.pack(fill="x", pady=(2, 0))

    # ── Center column ─────────────────────────────────────────
    def _build_center(self, parent):
        col = ctk.CTkFrame(parent, fg_color=C_BG, corner_radius=0)
        col.grid(row=0, column=1, sticky="nsew", padx=3)
        # 자식이 이 frame 크기를 팽창시키지 못하도록 차단
        col.pack_propagate(False)

        # ── 카메라 행 ─────────────────────────────────────────
        cam_row = ctk.CTkFrame(col, fg_color=C_BG)
        cam_row.pack(fill="both", expand=True)
        # grid_propagate(False) 제거 — sticky="nsew"가 동작하려면 propagate 허용 필요
        cam_row.columnconfigure(0, weight=1)
        cam_row.columnconfigure(1, weight=1)
        cam_row.rowconfigure(0, weight=1)

        # CAM-01
        cl = _panel(cam_row, "CAM-01  ·  MONITOR")
        cl.grid(row=0, column=0, sticky="nsew", padx=(0, 2), pady=(0, 2))
        cl.pack_propagate(False)   # 이미지가 패널을 팽창시키지 못하게
        self.lbl_video = ctk.CTkLabel(cl, text="INITIALIZING...",
                                      fg_color="#030405", corner_radius=0,
                                      font=ctk.CTkFont(F_MONO, 16),
                                      text_color=C_TEXT_DIM)
        self.lbl_video.pack(expand=True, fill="both", padx=3, pady=3)

        # CAM-02
        cr = _panel(cam_row, "CAM-02  ·  HUMAN POSE")
        cr.grid(row=0, column=1, sticky="nsew", padx=(2, 0), pady=(0, 2))
        cr.pack_propagate(False)   # 이미지가 패널을 팽창시키지 못하게
        self.lbl_vision_frame = ctk.CTkLabel(cr, text="START VISION NODE",
                                             fg_color="#030405", corner_radius=0,
                                             font=ctk.CTkFont(F_MONO, 16),
                                             text_color=C_TEXT_DIM)
        self.lbl_vision_frame.pack(expand=True, fill="both", padx=3, pady=3)

        # ── Pick & Place 타이머 ───────────────────────────────
        pnp = _panel(col, "PICK & PLACE TEST  ·  TIMER")
        pnp.pack(fill="x")
        pnp.pack_propagate(False)
        pnp.configure(height=120)
        pnp_in = ctk.CTkFrame(pnp, fg_color="transparent")
        pnp_in.pack(fill="x", padx=10, pady=6)
        self.lbl_timer = ctk.CTkLabel(pnp_in, text="02:00",
                                      font=ctk.CTkFont(F_MONO, 60, "bold"),
                                      text_color=C_ACCENT, fg_color="transparent")
        self.lbl_timer.pack(side="left", padx=(0, 16))
        btn_row = ctk.CTkFrame(pnp_in, fg_color="transparent")
        btn_row.pack(side="left")
        self.btn_pnp = _btn(btn_row, "[ START TIMER ]",
                            lambda: self.start_trial("pnp"), width=160)
        self.btn_pnp.pack(side="left", padx=(0, 6))
        _btn(btn_row, "[ RESET ]", self.reset_pnp,
             width=100, accent=C_TEXT_DIM).pack(side="left")

    # ── Right column ──────────────────────────────────────────
    def _build_right(self, parent):
        col = ctk.CTkFrame(parent, fg_color=C_BG, corner_radius=0)
        col.grid(row=0, column=2, sticky="nsew", padx=3)

        pp = _panel(col, "PAYLOAD TEST  ·  80g")
        pp.pack(fill="both", expand=True, pady=(0, 3))
        pp_in = ctk.CTkFrame(pp, fg_color="transparent")
        pp_in.pack(fill="x", padx=10, pady=10)
        self._dot_pay = _status_dot(pp_in, C_RED)
        self._dot_pay.pack(anchor="w", pady=(0, 8))
        self.btn_payload = _btn(pp_in, "EXECUTE PAYLOAD TEST",
                                lambda: self.start_trial("payload"))
        self.btn_payload.pack(fill="x")

        lp = _panel(col, "LATENCY CHECK  ·  ms")
        lp.pack(fill="both", expand=True, pady=(0, 3))
        lp_in = ctk.CTkFrame(lp, fg_color="transparent")
        lp_in.pack(fill="x", padx=10, pady=10)
        self.lbl_realtime_lat = ctk.CTkLabel(lp_in, text="REAL-TIME AVG:  -- ms",
                                             font=ctk.CTkFont(F_MONO, 18, "bold"),
                                             text_color=C_CYAN, fg_color="transparent")
        self.lbl_realtime_lat.pack(anchor="w", pady=(0, 8))
        self.btn_lat = _btn(lp_in, "[ MEASURE ]",
                            lambda: self.start_trial("latency"), accent=C_CYAN)
        self.btn_lat.pack(fill="x", pady=(0, 8))
        ind_row = ctk.CTkFrame(lp_in, fg_color="transparent")
        ind_row.pack(fill="x")
        self.lat_inds = []
        for i in range(5):
            lbl = ctk.CTkLabel(ind_row, text="--",
                               font=ctk.CTkFont(F_MONO, 17), width=54,
                               fg_color=C_SURFACE2, corner_radius=8,
                               text_color=C_TEXT_MID)
            lbl.grid(row=0, column=i, padx=2)
            self.lat_inds.append(lbl)

        sp = _panel(col, "ROBOT STATE  ·  JOINT MONITOR")
        sp.pack(fill="both", expand=True)
        sp_in = ctk.CTkFrame(sp, fg_color="transparent")
        sp_in.pack(fill="x", padx=10, pady=10)
        # self.lbl_robot_states = ctk.CTkLabel(sp_in,
        #                                      text="\nGripper:     --",
        #                                      font=ctk.CTkFont(F_MONO, 18),
        #                                      text_color=C_TEXT, fg_color="transparent",
        #                                      justify="left")
        # self.lbl_robot_states.pack(anchor="w", pady=(0, 8))
        self.lbl_motor_current = ctk.CTkLabel(sp_in, text="Current load:  -- %",
                                              font=ctk.CTkFont(F_MONO, 18),
                                              text_color=C_TEXT_MID,
                                              fg_color="transparent", justify="left")
        self.lbl_motor_current.pack(anchor="w")

    # ── Chat column ───────────────────────────────────────────
    def _build_chat(self, parent):
        chat_col = ctk.CTkFrame(parent, fg_color=C_CHAT_BG,
                                corner_radius=10, border_width=1,
                                border_color=C_BORDER)
        chat_col.grid(row=0, column=3, sticky="nsew", padx=(3, 0))

        # 헤더
        ch = ctk.CTkFrame(chat_col, fg_color=C_HEADER, corner_radius=0, height=58)
        ch.pack(fill="x", pady=(0, 1))
        ch.pack_propagate(False)
        ctk.CTkFrame(ch, fg_color=C_ACCENT, width=5,
                     corner_radius=0).pack(side="left", fill="y")
        ctk.CTkLabel(ch, text="  ◈  AVATAR AGENT",
                     font=ctk.CTkFont(F_MONO, 20, "bold"),
                     text_color="#FFFFFF").pack(side="left", padx=10, pady=12)
        self.lbl_ai_status = ctk.CTkLabel(ch, text="LOADING...",
                                          font=ctk.CTkFont(F_MONO, 18),
                                          text_color=C_YELLOW)
        self.lbl_ai_status.pack(side="right", padx=12)

        # 상태 바
        node_bar = ctk.CTkFrame(chat_col, fg_color="#D0DCE8",
                                corner_radius=0, height=38)
        node_bar.pack(fill="x", pady=(0, 1))
        node_bar.pack_propagate(False)
        self._nd_estop = ctk.CTkLabel(node_bar, text="ESTOP: ARMED",
                                      font=ctk.CTkFont(F_MONO, 15, "bold"),
                                      text_color=C_ACCENT_DIM)
        self._nd_estop.pack(side="right", padx=12)

        # 스크롤 채팅 영역
        self.chat_scroll = ctk.CTkScrollableFrame(chat_col, fg_color=C_CHAT_BG,
                                                  corner_radius=0, border_width=0)
        self.chat_scroll.pack(fill="both", expand=True, pady=(0, 1))

        # 입력 영역
        inp = ctk.CTkFrame(chat_col, fg_color="#C9D4DF", corner_radius=0,
                           height=self._CHAT_AREA_H,
                           border_width=1, border_color=C_BORDER)
        inp.pack(fill="x")
        inp.pack_propagate(False)

        self.mic_btn = ctk.CTkButton(
            inp, text="🎙",
            width=self._CHAT_BTN_W, height=self._CHAT_BTN_H,
            corner_radius=17, fg_color="#FFFFFF", hover_color="#E8F0FF",
            border_width=0, text_color=C_TEXT_MID, font=ctk.CTkFont(size=14),
            state="disabled", command=self._start_voice)
        self.mic_btn.pack(side="left", padx=(8, 4), anchor="center")

        self.chat_input = ctk.CTkTextbox(
            inp, height=self._CHAT_INPUT_H, corner_radius=14,
            font=ctk.CTkFont(F_SANS, 14), fg_color="#FFFFFF",
            text_color=C_TEXT, border_width=0)
        self.chat_input.pack(side="left", fill="x", expand=True, padx=(0, 4), pady=10)
        self.chat_input.bind("<Return>", self._on_enter)
        self.chat_input.bind("<Shift-Return>", lambda e: None)

        self.send_btn = ctk.CTkButton(
            inp, text="▶",
            width=self._CHAT_BTN_W, height=self._CHAT_BTN_H,
            corner_radius=17, fg_color="#FAE100", hover_color="#F0D500",
            border_width=0, text_color="#3C1E00",
            font=ctk.CTkFont(F_MONO, 13, "bold"),
            state="disabled", command=self._send_chat)
        self.send_btn.pack(side="right", padx=(0, 8), anchor="center")

        self._add_bubble("SYSTEM INITIALIZING...\n모델 로드 중입니다.", is_sys=True)

    # ── Bottom log ────────────────────────────────────────────
    def _build_test_panels(self):
        """카메라 아래 / 로그 위 — 3개 테스트 패널 행"""
        outer = ctk.CTkFrame(self.root, fg_color=C_BG, corner_radius=0)
        outer.pack(fill="x", padx=6, pady=(0, 3))

        outer.columnconfigure(0, weight=1)
        outer.columnconfigure(1, weight=1)
        outer.columnconfigure(2, weight=1)

        # ── 공통: 5개 토글 버튼 생성 헬퍼 ────────────────────
        def _make_toggle_btns(parent, labels):
            btn_frame = ctk.CTkFrame(parent, fg_color="transparent")
            btn_frame.pack(fill="x", padx=8, pady=(6, 8))
            btns = []
            for i, lbl in enumerate(labels):
                b = ctk.CTkButton(
                    btn_frame, text=lbl,
                    width=0, height=36, corner_radius=8,
                    fg_color=C_SURFACE2, hover_color="#DBEAFE",
                    border_width=2, border_color=C_BORDER,
                    text_color=C_TEXT_MID,
                    font=ctk.CTkFont(F_MONO, 13, "bold"))
                b.grid(row=0, column=i, padx=3, sticky="ew")
                btn_frame.columnconfigure(i, weight=1)
                btns.append(b)

            def _toggle(idx):
                for j, btn in enumerate(btns):
                    if j == idx:
                        active = btn.cget("fg_color") != C_ACCENT
                        btn.configure(
                            fg_color=C_ACCENT if active else C_SURFACE2,
                            text_color="#FFFFFF" if active else C_TEXT_MID,
                            border_color=C_ACCENT if active else C_BORDER)
                    # 다른 버튼은 그대로 (독립 토글 — 다중 선택 가능)

            for i in range(len(btns)):
                btns[i].configure(command=lambda idx=i: _toggle(idx))
            return btns

        # ── PAYLOAD TEST ──────────────────────────────────────
        p1 = _panel(outer, "PAYLOAD TEST")
        p1.grid(row=0, column=0, sticky="nsew", padx=(0, 3), pady=2)
        _make_toggle_btns(p1, ["TRIAL 1", "TRIAL 2", "TRIAL 3", "TRIAL 4", "TRIAL 5"])

        # ── LATENCY TEST ──────────────────────────────────────
        p2 = _panel(outer, "LATENCY TEST")
        p2.grid(row=0, column=1, sticky="nsew", padx=3, pady=2)
        _make_toggle_btns(p2, ["TRIAL 1", "TRIAL 2", "TRIAL 3", "TRIAL 4", "TRIAL 5"])

        # ── PEG IN HOLE TEST ──────────────────────────────────
        p3 = _panel(outer, "PEG IN HOLE TEST")
        p3.grid(row=0, column=2, sticky="nsew", padx=(3, 0), pady=2)
        _make_toggle_btns(p3, ["TRIAL 1", "TRIAL 2", "TRIAL 3", "TRIAL 4", "TRIAL 5"])

        # 경과 시간 기록 창 (5개) ───────────────────────────────
        rec_frame = ctk.CTkFrame(p3, fg_color="transparent")
        rec_frame.pack(fill="x", padx=8, pady=(0, 8))
        self._pih_time_lbls = []
        for i in range(5):
            cell = ctk.CTkFrame(rec_frame, fg_color=C_SURFACE2,
                                corner_radius=8, border_width=1,
                                border_color=C_BORDER)
            cell.grid(row=0, column=i, padx=3, sticky="ew")
            rec_frame.columnconfigure(i, weight=1)
            ctk.CTkLabel(cell, text=f"T{i+1}",
                         font=ctk.CTkFont(F_MONO, 11),
                         text_color=C_TEXT_DIM,
                         fg_color="transparent").pack(pady=(4, 0))
            lbl = ctk.CTkLabel(cell, text="--:--",
                               font=ctk.CTkFont(F_MONO, 13, "bold"),
                               text_color=C_ACCENT,
                               fg_color="transparent")
            lbl.pack(pady=(0, 4))
            self._pih_time_lbls.append(lbl)

        # 기록 슬롯 인덱스
        self._pih_slot = 0

    # ── Bottom log ────────────────────────────────────────────
    def _build_bottom(self):
        bot = ctk.CTkFrame(self.root, fg_color="#D6DDE5", corner_radius=0,
                           height=175, border_width=1, border_color=C_BORDER)
        bot.pack(fill="x", padx=6, pady=(0, 6))
        bot.pack_propagate(False)

        self.log_area = ctk.CTkTextbox(bot, height=145, corner_radius=10,
                                       fg_color="#F0F4F8", text_color="#1A3A5C",
                                       font=ctk.CTkFont(F_MONO, 17),
                                       border_width=1, border_color=C_BORDER)
        self.log_area.pack(side="left", fill="both", expand=True,
                           padx=(10, 6), pady=12)

        ef = ctk.CTkFrame(bot, fg_color="transparent")
        ef.pack(side="right", padx=12, pady=12)
        self.lbl_estop_source = ctk.CTkLabel(ef, text="",
                                             font=ctk.CTkFont(F_MONO, 15),
                                             text_color=C_RED, fg_color="transparent")
        self.lbl_estop_source.pack(pady=(0, 4))
        self.btn_estop = ctk.CTkButton(ef, text="⬡\nE-STOP",
                                       width=148, height=148, corner_radius=74,
                                       fg_color=C_ESTOP_BG, hover_color="#FFD7D7",
                                       border_width=4, border_color=C_ESTOP_RIM,
                                       text_color=C_RED,
                                       font=ctk.CTkFont(F_MONO, 20, "bold"),
                                       command=self._manual_estop)
        self.btn_estop.pack()

    # ── 말풍선 ───────────────────────────────────────────────
    def _wrap(self, margin=60):
        try:
            w = self.chat_scroll.winfo_width()
            return max(w - margin, 160)
        except Exception:
            return 400

    def _add_bubble(self, text, is_user=False, is_action=False,
                    is_sys=False, is_estop=False):
        row = ctk.CTkFrame(self.chat_scroll, fg_color="transparent")
        row.pack(fill="x", padx=8, pady=3)

        if is_sys:
            lbl = ctk.CTkLabel(row, text=text, wraplength=self._wrap(),
                               font=ctk.CTkFont(F_MONO, 12), justify="left",
                               fg_color=C_CHAT_SYS, text_color=C_TEXT_DIM,
                               corner_radius=10, padx=10, pady=7)
            lbl.pack(fill="x")
            row.bind("<Configure>", lambda e, l=lbl:
                     l.configure(wraplength=max(e.width - 30, 80)))

        elif is_estop:
            ctk.CTkLabel(row, text="⚠  EMERGENCY STOP",
                         font=ctk.CTkFont(F_MONO, 12, "bold"),
                         text_color=C_RED, fg_color="transparent").pack(anchor="w", pady=(0,2))
            lbl = ctk.CTkLabel(row, text=text, wraplength=self._wrap(),
                               font=ctk.CTkFont(F_MONO, 12), justify="left",
                               fg_color=C_CHAT_ESTOP, text_color=C_RED,
                               corner_radius=10, padx=10, pady=7)
            lbl.pack(fill="x")
            row.bind("<Configure>", lambda e, l=lbl:
                     l.configure(wraplength=max(e.width - 30, 80)))

        elif is_user:
            lbl = ctk.CTkLabel(row, text=text, wraplength=self._wrap(50),
                               font=ctk.CTkFont(F_SANS, 14), justify="left",
                               fg_color=C_CHAT_USER, text_color=C_ACCENT,
                               corner_radius=12, padx=12, pady=9)
            lbl.pack(side="right", anchor="e")
            row.bind("<Configure>", lambda e, l=lbl:
                     l.configure(wraplength=max(e.width - 50, 80)))

        elif is_action:
            ctk.CTkLabel(row, text="⚙", font=ctk.CTkFont(F_MONO, 12),
                         text_color=C_CYAN, fg_color="transparent").pack(
                             side="left", padx=(0,4), anchor="n")
            lbl = ctk.CTkLabel(row, text=text, wraplength=self._wrap(50),
                               font=ctk.CTkFont(F_MONO, 12), justify="left",
                               fg_color=C_CHAT_ACT, text_color=C_CYAN,
                               corner_radius=10, padx=10, pady=7)
            lbl.pack(side="left", anchor="w", fill="x", expand=True)
            row.bind("<Configure>", lambda e, l=lbl:
                     l.configure(wraplength=max(e.width - 50, 80)))

        else:
            ctk.CTkLabel(row, text="AI ▸", font=ctk.CTkFont(F_MONO, 11, "bold"),
                         text_color=C_ACCENT_DIM, fg_color="transparent").pack(
                             anchor="w", pady=(0,2))
            lbl = ctk.CTkLabel(row, text=text, wraplength=self._wrap(30),
                               font=ctk.CTkFont(F_SANS, 14), justify="left",
                               fg_color=C_CHAT_BOT, text_color=C_TEXT,
                               corner_radius=12, padx=12, pady=9, anchor="w")
            lbl.pack(fill="x")
            row.bind("<Configure>", lambda e, l=lbl:
                     l.configure(wraplength=max(e.width - 30, 80)))

        self.root.after(80, lambda: self.chat_scroll._parent_canvas.yview_moveto(1.0))

    # ── 모델 준비 ────────────────────────────────────────────
    def _on_model_ready(self):
        self.lbl_ai_status.configure(text="ONLINE", text_color=C_GREEN)
        self.send_btn.configure(state="normal", fg_color="#FAE100",
                                hover_color="#F0D500", text_color="#3C1E00")
        if _whisper_ready:
            self.mic_btn.configure(state="normal", fg_color="#E3F2FD",
                                   border_width=0, text_color=C_ACCENT)
        self._add_bubble("AVATAR SYSTEM READY\n명령을 입력하거나 🎙 버튼으로 음성 명령을 내리세요.")
        self.log_message("AVATAR AI: 모델 로드 완료.")
        self.log_message("AI-ESTOP: 자동 정지 감지 활성화됨.")

    def _on_enter(self, event):
        if not (event.state & 0x1):
            self._send_chat(); return "break"

    def _send_chat(self):
        text = self.chat_input.get("1.0", "end").strip()
        if not text or not _model_ready: return
        self.chat_input.delete("1.0", "end")
        self.send_btn.configure(state="disabled")
        self.mic_btn.configure(state="disabled")
        self._add_bubble(text, is_user=True)
        self._add_bubble("PROCESSING...")
        self._loading = self.chat_scroll.winfo_children()[-1]
        threading.Thread(
            target=lambda: self.root.after(0, self._on_resp, llm_chat(text)),
            daemon=True).start()

    def _on_resp(self, response):
        try: self._loading.destroy()
        except: pass
        if _has_estop_keyword(response):
            self._add_bubble(response)
            self.root.after(100, lambda: self._llm_triggered_estop(response))
        else:
            self._add_bubble(response)
            threading.Thread(target=self._run_dispatch, args=(response,),
                             daemon=True).start()
        self.send_btn.configure(state="normal")
        if _whisper_ready:
            self.mic_btn.configure(state="normal")

    def _run_dispatch(self, r):
        msg = self._dispatch(r)
        if msg:
            self.root.after(0, lambda: (
                self._add_bubble(msg, is_action=True),
                self.log_message(f"[AVATAR] {msg}")
            ))

    def _llm_triggered_estop(self, resp):
        found = [kw for kw in ESTOP_KEYWORDS if kw in resp.lower()]
        kw_str = ", ".join(f'"{k}"' for k in found[:3])
        self._add_bubble("비상 정지 명령 - 모든 노드 종료", is_estop=True)
        self.log_message(f"ESTOP TRIGGERED 키워드: {kw_str}")
        self._execute_estop(source="LLM")

    def _manual_estop(self):
        self.lbl_estop_source.configure(text="수동 트리거")
        self._add_bubble("E-STOP 실행됨.\n모든 노드 즉시 종료합니다.", is_estop=True)
        self.log_message("MANUAL E-STOP TRIGGERED")
        self._execute_estop(source="MANUAL")

    def _execute_estop(self, source="UNKNOWN"):
        self._estop_active = True
        self._cam_stop_event.set()
        for k in ("realsense_key", "planning_key", "clock_key", "payload_key"):
            _kill(k)
        self.realsense_online = self.clock_online = \
            self.payload_online = self.pnp_running = False
        if self.rs_pipeline:
            try: self.rs_pipeline.stop()
            except: pass
            self.rs_pipeline = None
        for dot in (self._dot_rs, self._dot_plan, self._dot_clk, self._dot_pay):
            dot.configure(text_color=C_RED)
        self.lbl_rs_status.configure(text="OFFLINE",    text_color=C_RED)
        self.lbl_clock_status.configure(text="OFFLINE", text_color=C_RED)
        self.lbl_robot_status.configure(text="OFFLINE", text_color=C_RED)
        self.lbl_countdown.configure(text="")
        self.btn_rs.configure(text="START VISION NODE",
                              border_color=C_ACCENT, text_color=C_ACCENT)
        self.btn_clock.configure(text="START CLOCK NODE",
                                 border_color=C_ACCENT, text_color=C_ACCENT)
        self.btn_payload.configure(text="EXECUTE PAYLOAD TEST",
                                   border_color=C_ACCENT, text_color=C_ACCENT)
        self.btn_planning.configure(state="normal")
        self.lbl_vision_frame.configure(image=None,
                                        text="START VISION NODE",
                                        text_color=C_TEXT_DIM)
        self.btn_estop.configure(fg_color="#FFD7D7", border_color="#FF4444")
        self.root.after(2000, lambda: self.btn_estop.configure(
            fg_color=C_ESTOP_BG, border_color=C_ESTOP_RIM))
        self._nd_estop.configure(text=f"AI-ESTOP: FIRED [{source}]", text_color=C_RED)
        self.root.after(5000, lambda: self._nd_estop.configure(
            text="AI-ESTOP: ARMED", text_color=C_ACCENT_DIM))
        self.log_message(f"E-STOP EXECUTED [{source}] — ALL NODES TERMINATED")
        self._estop_active = False

    def _start_voice(self):
        if not _whisper_ready: return
        self.mic_btn.configure(text="⏺", fg_color="#FFEBEE",
                               border_width=0, text_color=C_RED, state="disabled")
        self.send_btn.configure(state="disabled")
        self.lbl_ai_status.configure(text="REC...", text_color=C_RED)
        def run():
            try:
                audio = _record_until_silence()
                self.root.after(0, self.lbl_ai_status.configure,
                                {"text": "인식 중...", "text_color": C_YELLOW})
                text = _stt(audio)
                if text: self.root.after(0, self._on_voice_ok, text)
                else:    self.root.after(0, self._on_voice_fail, "인식 실패")
            except Exception as e:
                self.root.after(0, self._on_voice_fail, str(e))
        threading.Thread(target=run, daemon=True).start()

    def _on_voice_ok(self, text):
        self.lbl_ai_status.configure(text="ONLINE", text_color=C_GREEN)
        self.mic_btn.configure(text="🎙", fg_color="#E3F2FD",
                               border_width=0, text_color=C_ACCENT, state="normal")
        self.chat_input.delete("1.0", "end")
        self.chat_input.insert("end", text)
        self._send_chat()

    def _on_voice_fail(self, reason):
        self.lbl_ai_status.configure(text="ONLINE", text_color=C_GREEN)
        self.mic_btn.configure(text="🎙", fg_color="#E3F2FD",
                               border_width=0, text_color=C_ACCENT, state="normal")
        self.send_btn.configure(state="normal")
        self._add_bubble(f"음성 인식 실패: {reason}", is_action=True)

    def _dispatch(self, r):
        if "리얼센스 카메라 스트리밍" in r:
            if not self.realsense_online: self.root.after(0, self.toggle_realsense)
            return r
        if "Depth camera 스트리밍을 종료" in r:
            if self.realsense_online: self.root.after(0, self.toggle_realsense)
            return r
        if "텔레오퍼레이션 모드 시작" in r:
            self.root.after(0, self.start_planning_with_tts); return r
        if "플래닝 노드를 종료" in r:
            self.root.after(0, lambda: _kill("planning_key")); return r
        if "클락 노드를 시작" in r:
            if not self.clock_online: self.root.after(0, self.toggle_clock)
            return r
        if "클락 노드를 종료" in r:
            if self.clock_online: self.root.after(0, self.toggle_clock)
            return r
        if "가반하중평가 노드 시작" in r or "워크스페이스를 제거" in r:
            if not self.payload_online:
                self.root.after(0, lambda: self.start_trial("payload"))
            return r
        return None

    def _tick_clock(self):
        self.lbl_sys_time.configure(text=time.strftime("  %Y-%m-%d   %H:%M:%S  "))
        self.root.after(1000, self._tick_clock)

    def log_message(self, msg):
        self.log_area.configure(state="normal")
        self.log_area.insert("end", f"[{time.strftime('%H:%M:%S')}]  {msg}\n")
        self.log_area.see("end")
        self.log_area.configure(state="disabled")

    def _init_ros(self):
        try:
            rclpy.init(args=None)
            self.ros_node = TeleopMonitorNode(self)
            threading.Thread(target=rclpy.spin, args=(self.ros_node,),
                             daemon=True).start()
            self.log_message("ROS2: 노드 초기화 완료.")
        except Exception as e:
            self.log_message(f"ROS2 init failed: {e}")

    def open_camera(self):
        try:
            self._cam_stop_event.clear()
            self.rs_pipeline = rs.pipeline()
            cfg = rs.config()
            cfg.enable_device("233522074207")
            cfg.enable_stream(rs.stream.color, 640, 480, rs.format.bgr8, 30)
            self.rs_pipeline.start(cfg)
            threading.Thread(target=self._camera_loop, daemon=True).start()
            self.log_message("CAM-01 started.")
        except Exception as e:
            self.lbl_video.configure(text=f"CAM ERROR:\n{e}", text_color=C_RED)
            self.log_message(f"CAM-01 init failed: {e}")

    def _camera_loop(self):
        while not self._cam_stop_event.is_set():
            try:
                if self.rs_pipeline is None: break
                frames = self.rs_pipeline.wait_for_frames(timeout_ms=1000)
                cf = frames.get_color_frame()
                if cf:
                    raw = np.asanyarray(cf.get_data())
                    rgb = raw[:, :, ::-1].copy()   # BGR→RGB, 원본 해상도 유지
                    try:
                        self._cam01_queue.put_nowait(rgb)
                    except queue.Full:
                        pass
            except Exception:
                pass

    def update_payload_current(self, val):
        self.lbl_motor_current.configure(text=f"Current load:  {val} %")

    def update_robot_states(self, txt):
        self.lbl_robot_states.configure(text=txt)

    def update_latency_buffer(self, val):
        self.latency_buffer.append(val)
        self.current_avg_lat = sum(self.latency_buffer) / len(self.latency_buffer)
        self.lbl_realtime_lat.configure(
            text=f"REAL-TIME AVG:  {int(self.current_avg_lat)} ms")

    def toggle_realsense(self):
        if not self.realsense_online:
            if _ros2_run("avatar", "vision_nav.py", key="realsense_key"):
                self.realsense_online = True
                self._dot_rs.configure(text_color=C_GREEN)
                self.lbl_rs_status.configure(text="ONLINE", text_color=C_GREEN)
                self.btn_rs.configure(text="STOP VISION NODE",
                                      border_color=C_RED, text_color=C_RED)
                self.lbl_vision_frame.configure(text="CONNECTING...", text_color=C_YELLOW)
                self.log_message("VISION NODE: started.")
        else:
            _kill("realsense_key")
            self.realsense_online = False
            self._dot_rs.configure(text_color=C_RED)
            self.lbl_rs_status.configure(text="OFFLINE", text_color=C_RED)
            self.btn_rs.configure(text="START VISION NODE",
                                  border_color=C_ACCENT, text_color=C_ACCENT)
            self.lbl_vision_frame.configure(image=None,
                                            text="START VISION NODE",
                                            text_color=C_TEXT_DIM)
            self.log_message("VISION NODE: stopped.")

    def toggle_clock(self):
        if not self.clock_online:
            if _ros2_run("avatar", "clock.py", key="clock_key"):
                self.clock_online = True
                self._dot_clk.configure(text_color=C_GREEN)
                self.lbl_clock_status.configure(text="ONLINE", text_color=C_GREEN)
                self.btn_clock.configure(text="STOP CLOCK NODE",
                                         border_color=C_RED, text_color=C_RED)
                self.log_message("CLOCK NODE: started.")
        else:
            _kill("clock_key")
            self.clock_online = False
            self._dot_clk.configure(text_color=C_RED)
            self.lbl_clock_status.configure(text="OFFLINE", text_color=C_RED)
            self.btn_clock.configure(text="START CLOCK NODE",
                                     border_color=C_ACCENT, text_color=C_ACCENT)
            self.log_message("CLOCK NODE: stopped.")

    def _tts_and_launch_planning(self):
        try:
            from gtts import gTTS; import playsound
            fn = "/tmp/planning_announce.mp3"
            gTTS(text="자리에 앉아서 차렷자세를 취해주세요. 3초 후에 시작합니다.",
                 lang='ko').save(fn)
            playsound.playsound(fn)
            if os.path.exists(fn): os.remove(fn)
        except Exception as e:
            print(f"[TTS] {e}")
        import time as _t
        for n in range(3, 0, -1):
            self.root.after(0, self.lbl_countdown.configure, {"text": str(n)})
            _t.sleep(1)
        self.root.after(0, self.lbl_countdown.configure, {"text": ""})
        if _ros2_run("avatar", "dxl_subscriber.py", key="planning_key"):
            self.root.after(0, self._dot_plan.configure, {"text_color": C_GREEN})
            self.root.after(0, self.lbl_robot_status.configure,
                            {"text": "ONLINE", "text_color": C_GREEN})
            self.root.after(0, self.btn_planning.configure, {"state": "disabled"})
            self.root.after(0, self.log_message, "PLANNING NODE: started.")
            _t.sleep(4)
            try:
                from gtts import gTTS; import playsound
                fn2 = "/tmp/teleop_start.mp3"
                gTTS(text="이제 텔레오퍼레이션을 시작해주세요.", lang='ko').save(fn2)
                playsound.playsound(fn2)
                if os.path.exists(fn2): os.remove(fn2)
            except: pass
        else:
            self.root.after(0, self.lbl_robot_status.configure,
                            {"text": "OFFLINE", "text_color": C_RED})
            self.root.after(0, self.btn_planning.configure, {"state": "normal"})
            self.root.after(0, self.log_message, "PLANNING NODE: failed.")

    def start_planning_with_tts(self):
        self.btn_planning.configure(state="disabled")
        self.lbl_robot_status.configure(text="PREPARING...", text_color=C_YELLOW)
        self.log_message("PLANNING NODE: TTS 안내 후 시작 예정.")
        threading.Thread(target=self._tts_and_launch_planning, daemon=True).start()

    def start_trial(self, t):
        if t == "payload":
            if not self.payload_online:
                if _ros2_run("avatar", "payload_test.py", key="payload_key"):
                    self.payload_online = True
                    self._dot_pay.configure(text_color=C_GREEN)
                    self.btn_payload.configure(text="STOP PAYLOAD TEST",
                                               border_color=C_RED, text_color=C_RED)
                    self.log_message("PAYLOAD TEST: started.")
            else:
                _kill("payload_key")
                self.payload_online = False
                self._dot_pay.configure(text_color=C_RED)
                self.btn_payload.configure(text="EXECUTE PAYLOAD TEST",
                                           border_color=C_ACCENT, text_color=C_ACCENT)
                self.log_message("PAYLOAD TEST: stopped.")
        elif t == "pnp":
            self.btn_pnp.configure(state="disabled")
            self.pnp_time_left = 120
            self.pnp_running   = True
            self.pnp_start_time = time.time()   # 시작 시각 기록
            self._tick_pnp()
            self.log_message("PICK & PLACE: timer started.")
        elif t == "latency":
            if self.latency_trial < self.max_lat_trials:
                self.btn_lat.configure(state="disabled")
                self.root.after(500, self.record_latency)

    def _tick_pnp(self):
        if self.pnp_running and self.pnp_time_left > 0:
            m, s = divmod(self.pnp_time_left, 60)
            self.lbl_timer.configure(text=f"{m:02d}:{s:02d}")
            self.pnp_time_left -= 1
            self.root.after(1000, self._tick_pnp)
        elif self.pnp_time_left <= 0:
            self.lbl_timer.configure(text="00:00", text_color=C_RED)
            self.pnp_running = False
            self.btn_pnp.configure(state="normal")
            self.log_message("PICK & PLACE: timer finished.")

    def reset_pnp(self):
        # 경과 시간 계산 후 Peg-in-Hole 슬롯에 기록
        if self.pnp_running and self.pnp_start_time is not None:
            elapsed = int(time.time() - self.pnp_start_time)
            m, s = divmod(elapsed, 60)
            time_str = f"{m:02d}:{s:02d}"
            if hasattr(self, '_pih_time_lbls') and self._pih_slot < 5:
                self._pih_time_lbls[self._pih_slot].configure(
                    text=time_str, text_color=C_GREEN)
                self._pih_slot += 1
            self.log_message(f"PEG IN HOLE: T{self._pih_slot} 경과 {time_str}")

        self.pnp_running = False
        self.pnp_time_left = 120
        self.pnp_start_time = None
        self.lbl_timer.configure(text="02:00", text_color=C_ACCENT)
        self.btn_pnp.configure(state="normal")
        self.log_message("PICK & PLACE: timer reset.")

    def record_latency(self):
        if not self.latency_buffer:
            self.log_message("WARNING: no latency data yet."); return
        val = int(self.current_avg_lat)
        self.lat_inds[self.latency_trial].configure(text=f"{val}", text_color=C_ACCENT)
        self.latency_trial += 1
        if self.latency_trial < self.max_lat_trials:
            self.btn_lat.configure(state="normal")
        else:
            self.btn_lat.configure(text="[ DONE ]", state="disabled")
        self.log_message(f"LATENCY: recorded {val} ms (avg)")


# ══════════════════════════════════════════════════════════════
# 진입점
# ══════════════════════════════════════════════════════════════
def main():
    root = ctk.CTk()
    root.withdraw()

    app = CombinedGUI.__new__(CombinedGUI)
    app.root = root

    run_splash(root)

    def _start_app():
        CombinedGUI.__init__(app, root)

    root.after(100, _start_app)

    def on_close():
        app._cam_stop_event.set()
        if app.rs_pipeline:
            try: app.rs_pipeline.stop()
            except: pass
        if hasattr(app, 'ros_node'):
            try: app.ros_node.destroy_node()
            except: pass
        try: rclpy.shutdown()
        except: pass
        for k in ("realsense_key", "planning_key", "clock_key", "payload_key"):
            _kill(k)
        os._exit(0)

    root.protocol("WM_DELETE_WINDOW", on_close)
    root.mainloop()


if __name__ == "__main__":
    main()