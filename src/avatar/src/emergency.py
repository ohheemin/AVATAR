#!/usr/bin/env python3
import ctypes

try:
    ERROR_HANDLER_FUNC = ctypes.CFUNCTYPE(None, ctypes.c_char_p, ctypes.c_int,
                                           ctypes.c_char_p, ctypes.c_int, ctypes.c_char_p)
    def py_error_handler(filename, line, function, err, fmt): pass
    c_error_handler = ERROR_HANDLER_FUNC(py_error_handler)
    asound = ctypes.cdll.LoadLibrary('libasound.so.2')
    asound.snd_lib_error_set_handler(c_error_handler)
except:
    pass

import rclpy
from rclpy.node import Node
from std_msgs.msg import String
import speech_recognition as sr
from gtts import gTTS
import os
import playsound
import threading
from faster_whisper import WhisperModel
import numpy as np
import tempfile
import soundfile as sf
import requests


OLLAMA_URL = "http://localhost:11434/api/generate"
OLLAMA_MODEL = "exaone3.5:7.8b"

SYSTEM_PROMPT = """당신은 로봇 긴급정지 명령 감지기입니다. 반드시 한국어로만 응답하세요.

사용자의 발화를 분석하여 로봇을 멈추려는 의도가 있는지 판단하세요.

정지 의도 예시: 정지, 멈춰, 세워, 그만, 중지, 멈추세요, 스톱

반드시 아래 둘 중 하나로만 답하세요:
정지
계속

다른 말은 절대 하지 마세요. 영어 사용 금지."""


class VoiceStopNode(Node):
    def __init__(self):
        super().__init__('voice_stop_node')
        self.publisher_ = self.create_publisher(String, '/stop', 10)
        self.recognizer = sr.Recognizer()

        # 내장 마이크 (HD-Audio Generic: ALC256 Analog)
        self.microphone = sr.Microphone(device_index=4)
        self.get_logger().info('내장 마이크 (index=4, ALC256) 사용')

        # faster-whisper 모델 로드 (GPU + float16)
        self.get_logger().info('faster-whisper 모델 로딩 중... (medium, CUDA)')
        self.whisper_model = WhisperModel("medium", device="cuda", compute_type="float16")
        self.get_logger().info('faster-whisper 모델 로드 완료')

        # Ollama 연결 확인
        self._check_ollama()

        with self.microphone as source:
            self.get_logger().info('주변 소음 수치를 조정 중...')
            self.recognizer.adjust_for_ambient_noise(source, duration=1)

        self.is_listening = False
        self.timer = self.create_timer(0.1, self.listen_and_process)
        self.get_logger().info('마이크 감시 시작: "정지"라고 말씀하세요.')

    def _check_ollama(self):
        try:
            resp = requests.get("http://localhost:11434/api/tags", timeout=3)
            models = [m['name'] for m in resp.json().get('models', [])]
            self.get_logger().info(f'Ollama 사용 가능 모델: {models}')
            if not any(OLLAMA_MODEL in m for m in models):
                self.get_logger().warn(f'모델 {OLLAMA_MODEL} 없음! 실행: ollama pull {OLLAMA_MODEL}')
        except Exception:
            self.get_logger().error('Ollama 서버 미실행! 실행: ollama serve')

    def listen_and_process(self):
        if self.is_listening:
            return
        self.is_listening = True
        try:
            with self.microphone as source:
                audio = self.recognizer.listen(source, timeout=0.5, phrase_time_limit=3)

            # 1단계: faster-whisper STT
            text = self.recognize_with_whisper(audio)
            if not text:
                return
            self.get_logger().info(f'인식된 음성: "{text}"')

            # 2단계: Ollama 의도 분류
            intent = self.classify_intent_with_ollama(text)
            self.get_logger().info(f'Ollama 판단: {intent}')

            if intent == "STOP":
                self.process_stop_event()

        except sr.WaitTimeoutError:
            pass
        except sr.UnknownValueError:
            pass
        except Exception as e:
            self.get_logger().error(f'에러 발생: {e}')
        finally:
            self.is_listening = False

    def recognize_with_whisper(self, audio):
        """faster-whisper STT - 한국어 고정, GPU 가속"""
        try:
            wav_data = np.frombuffer(audio.get_wav_data(), dtype=np.int16).astype(np.float32) / 32768.0
            with tempfile.NamedTemporaryFile(suffix=".wav", delete=False) as f:
                tmp_path = f.name
                sf.write(tmp_path, wav_data, audio.sample_rate)

            segments, _ = self.whisper_model.transcribe(
                tmp_path,
                language="ko",      # 한국어 고정
                task="transcribe",  # 번역 안 함
                beam_size=5         # 정확도 향상
            )
            os.remove(tmp_path)

            text = "".join([seg.text for seg in segments]).strip()
            return text if text else None

        except Exception as e:
            self.get_logger().error(f'Whisper 에러: {e}')
            return None

    def classify_intent_with_ollama(self, text):
        try:
            payload = {
                "model": OLLAMA_MODEL,
                "prompt": f'{SYSTEM_PROMPT}\n\n사용자 발화: "{text}"\n\n답변:',
                "stream": False,
                "options": {
                    "temperature": 0,
                    "num_predict": 5
                }
            }
            resp = requests.post(OLLAMA_URL, json=payload, timeout=10)
            response = resp.json().get("response", "").strip()
            self.get_logger().info(f'Ollama 원본 응답: "{response}"')

            return "STOP" if "정지" in response else "CONTINUE"

        except Exception as e:
            self.get_logger().error(f'Ollama 에러: {e}')
            keywords = ["정지", "멈춰", "세워", "그만", "중지", "멈추"]
            return "STOP" if any(k in text for k in keywords) else "CONTINUE"

    def process_stop_event(self):
        self.publish_stop_command()
        tts_text = "정지 명령을 듣고, 텔레오퍼레이팅 시스템을 종료합니다."
        threading.Thread(target=self.speak_and_exit, args=(tts_text,)).start()

    def publish_stop_command(self):
        msg = String()
        msg.data = "STOP_SIGNAL_ACTIVATED"
        self.publisher_.publish(msg)
        self.get_logger().warn('정지 명령 발행!')

    def speak_and_exit(self, text):
        try:
            tts = gTTS(text=text, lang='ko')
            filename = "/tmp/stop_announcement.mp3"
            tts.save(filename)
            playsound.playsound(filename)
            if os.path.exists(filename):
                os.remove(filename)
        except Exception as e:
            self.get_logger().error(f'TTS 에러: {e}')


def main(args=None):
    rclpy.init(args=args)
    node = VoiceStopNode()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        node.get_logger().info('노드가 종료되었습니다.')
    finally:
        node.destroy_node()
        try:
            rclpy.shutdown()
        except Exception:
            pass


if __name__ == '__main__':
    main()