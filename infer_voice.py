"""
아바타 텍스트 대화 시스템
- LLM: EXAONE (avatar_merged)
"""

import sys
import torch
from transformers import AutoModelForCausalLM, AutoTokenizer

# ── 설정 ───────────────────────────────────────────────────
MODEL_PATH = "./avatar_merged"

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

# ── 메인 루프 ──────────────────────────────────────────────
def main():
    # print("=" * 50)
    # print("  아바타 텍스트 대화 시스템")
    # print("  'quit' : 종료")
    # print("=" * 50 + "\n")

    while True:
        try:
            user_input = input("You: ").strip()
            if not user_input:
                continue
            if user_input.lower() in ("quit", "종료", "끝"):
                print("종료합니다.")
                break

            response = chat(user_input)
            print(f"Avatar: {response}\n")

        except KeyboardInterrupt:
            print("\n종료합니다.")
            break
        except Exception as e:
            print(f"[오류] {e}")
            continue

if __name__ == "__main__":
    main()