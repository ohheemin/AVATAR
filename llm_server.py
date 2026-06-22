#!/usr/bin/env python3
"""
아바타 LLM 서버 — GUI와 별도 프로세스로 실행
소켓 통신으로 추론 요청/응답 처리
"""
import socket, json, threading, torch
from transformers import AutoModelForCausalLM, AutoTokenizer
from faster_whisper import WhisperModel
import numpy as np, tempfile, os, sounddevice as sd
import scipy.io.wavfile as wavfile

HOST = "127.0.0.1"
PORT = 65432

print("LLM 로드 중...")
model = AutoModelForCausalLM.from_pretrained(
    "./avatar_merged", trust_remote_code=True,
    torch_dtype=torch.float16, device_map="auto")
tokenizer = AutoTokenizer.from_pretrained(
    "./avatar_merged", trust_remote_code=True)
model.eval()

print("Whisper 로드 중...")
device  = "cuda" if torch.cuda.is_available() else "cpu"
compute = "float16" if torch.cuda.is_available() else "int8"
whisper = WhisperModel("tiny", device=device, compute_type=compute)

SAMPLE_RATE    = 16000
SILENCE_THRESH = 0.02
SILENCE_FRAMES = 25

print(f"서버 시작 — {HOST}:{PORT}")

def llm_infer(text):
    prompt = (
        f"[|system|]당신은 아바타입니다. "
        f"로봇팔 제어와 3D pose estimation을 돕는 AI 어시스턴트입니다.[|endofturn|]\n"
        f"[|user|]{text}[|endofturn|]\n[|assistant|]"
    )
    inputs = tokenizer(prompt, return_tensors="pt").to(model.device)
    with torch.no_grad():
        outputs = model.generate(
            **inputs, max_new_tokens=256, do_sample=False,
            eos_token_id=tokenizer.eos_token_id)
    return tokenizer.decode(
        outputs[0][inputs["input_ids"].shape[1]:],
        skip_special_tokens=True).strip()

def stt_record():
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
    audio = np.concatenate(frames).flatten()
    with tempfile.NamedTemporaryFile(suffix=".wav", delete=False) as f:
        tmp = f.name
        wavfile.write(tmp, SAMPLE_RATE, (audio * 32767).astype(np.int16))
    try:
        segs, _ = whisper.transcribe(tmp, language="ko",
                                     beam_size=5, vad_filter=True)
        return " ".join(s.text for s in segs).strip()
    finally:
        os.unlink(tmp)

def handle(conn):
    with conn:
        data = b""
        while True:
            chunk = conn.recv(4096)
            if not chunk: break
            data += chunk
            if data.endswith(b"\n"): break
        try:
            req = json.loads(data.decode())
            cmd = req.get("cmd")
            if cmd == "infer":
                resp = llm_infer(req["text"])
                conn.sendall((json.dumps({"ok": True, "text": resp}) + "\n").encode())
            elif cmd == "stt":
                text = stt_record()
                conn.sendall((json.dumps({"ok": True, "text": text}) + "\n").encode())
            elif cmd == "ping":
                conn.sendall((json.dumps({"ok": True, "text": "pong"}) + "\n").encode())
        except Exception as e:
            conn.sendall((json.dumps({"ok": False, "text": str(e)}) + "\n").encode())

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    s.bind((HOST, PORT))
    s.listen()
    print("준비 완료! 클라이언트 대기 중...")
    while True:
        conn, _ = s.accept()
        threading.Thread(target=handle, args=(conn,), daemon=True).start()