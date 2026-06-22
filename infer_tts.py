"""
아바타 음성 대화 시스템
- STT: faster-whisper (로컬, 한국어)
- TTS: gTTS (Google TTS, 한국어)
- 설치: pip install faster-whisper gtts sounddevice numpy scipy
"""

import os
import sys
import tempfile
import threading
import numpy as np
import sounddevice as sd
import scipy.io.wavfile as wavfile
import torch
from transformers import AutoModelForCausalLM, AutoTokenizer

# ── 설치 확인 ──────────────────────────────────────────────
try:
    from faster_whisper import WhisperModel
except ImportError:
    print("[오류] faster-whisper 미설치. 실행: pip install faster-whisper")
    sys.exit(1)

try:
    from gtts import gTTS
    import pygame
    pygame.mixer.init()
    USE_PYGAME = True
except ImportError:
    USE_PYGAME = False
    try:
        import subprocess
        subprocess.run(["which", "mpg123"], check=True, capture_output=True)
        USE_MPG123 = True
    except Exception:
        USE_MPG123 = False
        print("[경고] pygame 또는 mpg123 없음. TTS 재생 불가.")
        print("       설치: pip install pygame  또는  sudo apt install mpg123")

# ── 설정 ───────────────────────────────────────────────────
MODEL_PATH      = "./avatar_merged"
WHISPER_MODEL   = "small"          # tiny / base / small / medium
SAMPLE_RATE     = 16000
RECORD_SECONDS  = 4               # 녹음 최대 길이 (초)
SILENCE_THRESH  = 0.02            # 묵음 판단 임계값
SILENCE_FRAMES  = 30              # 이 프레임 수 연속 묵음 → 녹음 종료
VOICE_MODE      = True            # False 면 텍스트 모드

# ── LLM 로드 ───────────────────────────────────────────────
print("모델 로드 중...")
model = AutoModelForCausalLM.from_pretrained(
    MODEL_PATH,
    trust_remote_code=True,
    torch_dtype=torch.float16,
    device_map="auto",
)
tokenizer = AutoTokenizer.from_pretrained(
    MODEL_PATH,
    trust_remote_code=True,
)
model.eval()

# ── Whisper 로드 ───────────────────────────────────────────
print("Whisper 로드 중...")
whisper = WhisperModel(WHISPER_MODEL, device="cuda" if torch.cuda.is_available() else "cpu",
                       compute_type="float16" if torch.cuda.is_available() else "int8")

print("준비 완료! 종료하려면 'quit' 또는 Ctrl+C\n")

# ── LLM 추론 ───────────────────────────────────────────────
def chat(instruction: str) -> str:
    prompt = (
        f"[|system|]당신은 아바타입니다. "
        f"로봇팔 제어와 3D pose estimation을 돕는 AI 어시스턴트입니다.[|endofturn|]\n"
        f"[|user|]{instruction}[|endofturn|]\n"
        f"[|assistant|]"
    )
    inputs = tokenizer(prompt, return_tensors="pt").to(model.device)
    with torch.no_grad():
        outputs = model.generate(
            **inputs,
            max_new_tokens=256,
            do_sample=False,
            eos_token_id=tokenizer.eos_token_id,
        )
    return tokenizer.decode(
        outputs[0][inputs["input_ids"].shape[1]:],
        skip_special_tokens=True,
    ).strip()

# ── STT: 마이크 녹음 → 텍스트 ─────────────────────────────
def record_until_silence() -> np.ndarray:
    """VAD 기반 자동 종료 녹음"""
    chunk = int(SAMPLE_RATE * 0.1)   # 100ms 단위
    frames = []
    silent_count = 0
    recording = False

    print("🎙  말씀하세요... (묵음 감지 시 자동 종료)")
    with sd.InputStream(samplerate=SAMPLE_RATE, channels=1,
                        dtype="float32", blocksize=chunk) as stream:
        while True:
            data, _ = stream.read(chunk)
            vol = float(np.abs(data).mean())
            frames.append(data.copy())

            if vol > SILENCE_THRESH:
                recording = True
                silent_count = 0
            elif recording:
                silent_count += 1
                if silent_count >= SILENCE_FRAMES:   # ~3초 묵음
                    break

            # 최대 30초 제한
            if len(frames) > SAMPLE_RATE // chunk * 30:
                break

    audio = np.concatenate(frames, axis=0).flatten()
    return audio

def stt(audio: np.ndarray) -> str:
    """faster-whisper로 음성 → 텍스트"""
    # float32 → int16 WAV 임시 파일
    with tempfile.NamedTemporaryFile(suffix=".wav", delete=False) as f:
        tmp_path = f.name
        wavfile.write(tmp_path, SAMPLE_RATE,
                      (audio * 32767).astype(np.int16))

    try:
        segments, info = whisper.transcribe(
            tmp_path,
            language="ko",
            beam_size=5,
            vad_filter=True,
        )
        text = " ".join(s.text for s in segments).strip()
    finally:
        os.unlink(tmp_path)

    return text

# ── TTS: 텍스트 → 음성 재생 ────────────────────────────────
def speak(text: str):
    """gTTS로 텍스트 → 음성 재생"""
    with tempfile.NamedTemporaryFile(suffix=".mp3", delete=False) as f:
        tmp_path = f.name

    try:
        tts = gTTS(text=text, lang="ko", slow=False)
        tts.save(tmp_path)

        if USE_PYGAME:
            pygame.mixer.music.load(tmp_path)
            pygame.mixer.music.play()
            while pygame.mixer.music.get_busy():
                pygame.time.Clock().tick(10)
        else:
            # mpg123 fallback
            import subprocess
            subprocess.run(["mpg123", "-q", tmp_path],
                           capture_output=True)
    finally:
        try:
            os.unlink(tmp_path)
        except Exception:
            pass

# ── 메인 루프 ──────────────────────────────────────────────
def main():
    global VOICE_MODE

    print("=" * 50)
    print("  아바타 음성 대화 시스템")
    print("  'v' 입력: 음성/텍스트 모드 전환")
    print("  'quit'  : 종료")
    print("=" * 50)
    print(f"현재 모드: {'🎙 음성' if VOICE_MODE else '⌨  텍스트'}\n")

    while True:
        try:
            if VOICE_MODE:
                # ── 음성 입력 ──────────────────────────────
                audio = record_until_silence()
                user_input = stt(audio)

                if not user_input:
                    print("(인식 실패, 다시 말씀해 주세요)\n")
                    continue

                print(f"You (음성): {user_input}")

                if user_input.strip().lower() in ("quit", "종료", "끝"):
                    print("종료합니다.")
                    break
                if user_input.strip() == "v":
                    VOICE_MODE = False
                    print("→ 텍스트 모드 전환\n")
                    continue

            else:
                # ── 텍스트 입력 ────────────────────────────
                user_input = input("You: ").strip()
                if not user_input:
                    continue
                if user_input.lower() == "quit":
                    print("종료합니다.")
                    break
                if user_input == "v":
                    VOICE_MODE = True
                    print("→ 음성 모드 전환\n")
                    continue

            # ── LLM 응답 ───────────────────────────────────
            response = chat(user_input)
            print(f"Avatar: {response}\n")

            # ── TTS 재생 (백그라운드) ───────────────────────
            if VOICE_MODE:
                tts_thread = threading.Thread(
                    target=speak, args=(response,), daemon=True
                )
                tts_thread.start()
                tts_thread.join()   # 말 끝날 때까지 대기 후 다음 녹음
            else:
                # 텍스트 모드에서도 TTS 원하면 주석 해제
                # speak(response)
                pass

        except KeyboardInterrupt:
            print("\n종료합니다.")
            break
        except Exception as e:
            print(f"[오류] {e}")
            continue

if __name__ == "__main__":
    main()