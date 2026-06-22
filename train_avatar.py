from transformers import AutoModelForCausalLM, AutoTokenizer, BitsAndBytesConfig
from peft import get_peft_model, LoraConfig, TaskType
from trl import SFTTrainer, SFTConfig
from datasets import Dataset
import json
import torch
import types

bnb_config = BitsAndBytesConfig(
    load_in_4bit=True,
    bnb_4bit_quant_type="nf4",
    bnb_4bit_compute_dtype=torch.bfloat16 if torch.cuda.is_bf16_supported() else torch.float16,
    bnb_4bit_use_double_quant=True,
)

print("모델 로드 중...")
model = AutoModelForCausalLM.from_pretrained(
    "LGAI-EXAONE/EXAONE-3.5-2.4B-Instruct",
    quantization_config=bnb_config,
    trust_remote_code=True,
    device_map="auto",
)
tokenizer = AutoTokenizer.from_pretrained(
    "LGAI-EXAONE/EXAONE-3.5-2.4B-Instruct",
    trust_remote_code=True,
)

def get_input_embeddings(self):
    return self.transformer.wte
def set_input_embeddings(self, value):
    self.transformer.wte = value
model.get_input_embeddings = types.MethodType(get_input_embeddings, model)
model.set_input_embeddings = types.MethodType(set_input_embeddings, model)

model.gradient_checkpointing_enable()
model.enable_input_require_grads()

# ── LoRA 설정 (r=32, FFN 레이어 추가로 강한 학습) ──────────
lora_config = LoraConfig(
    r=32,
    lora_alpha=64,       # r * 2
    lora_dropout=0.05,
    target_modules=[
        "q_proj", "k_proj", "v_proj", "o_proj",  # Attention
        "gate_proj", "up_proj", "down_proj",       # FFN 추가
    ],
    bias="none",
    task_type=TaskType.CAUSAL_LM,
)
model = get_peft_model(model, lora_config)
model.print_trainable_parameters()

# ── 데이터 로드 ─────────────────────────────────────────────
DATASET_FILE = "avatar_data.jsonl"

def load_jsonl(path):
    data = []
    with open(path, "r", encoding="utf-8") as f:
        for line in f:
            line = line.strip()
            if line:
                data.append(json.loads(line))
    return data

print(f"데이터 로드 중: {DATASET_FILE}")
raw = load_jsonl(DATASET_FILE)
print(f"총 {len(raw)}개 샘플 로드 완료")

def format_chat(example):
    return {
        "text": (
            f"[|system|]당신은 아바타입니다. "
            f"로봇팔 제어와 3D pose estimation을 돕는 AI 어시스턴트입니다.[|endofturn|]\n"
            f"[|user|]{example['instruction']}[|endofturn|]\n"
            f"[|assistant|]{example['output']}[|endofturn|]"
        )
    }

dataset = Dataset.from_list(raw).map(format_chat)

sft_config = SFTConfig(
    output_dir="./avatar_model",
    num_train_epochs=15,
    per_device_train_batch_size=1,
    gradient_accumulation_steps=8,
    warmup_steps=10,
    learning_rate=2e-4,
    fp16=not torch.cuda.is_bf16_supported(),
    bf16=torch.cuda.is_bf16_supported(),
    logging_steps=10,
    save_steps=100,
    optim="adamw_8bit",
    report_to="tensorboard",
    max_length=1024,
    dataset_text_field="text",
)

trainer = SFTTrainer(
    model=model,
    processing_class=tokenizer,
    train_dataset=dataset,
    args=sft_config,
)

print("🚀 학습 시작!")
trainer.train()

model.save_pretrained("./avatar_lora")
tokenizer.save_pretrained("./avatar_lora")
print("LoRA 저장 완료! → ./avatar_lora")
