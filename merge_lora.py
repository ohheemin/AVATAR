from transformers import AutoModelForCausalLM, AutoTokenizer
from peft import PeftModel
import torch
import types

# EXAONE 패치 함수
def patch_exaone(model):
    def get_input_embeddings(self):
        return self.transformer.wte
    def set_input_embeddings(self, value):
        self.transformer.wte = value
    model.get_input_embeddings = types.MethodType(get_input_embeddings, model)
    model.set_input_embeddings = types.MethodType(set_input_embeddings, model)
    return model

print("베이스 모델 로드 중...")
base_model = AutoModelForCausalLM.from_pretrained(
    "LGAI-EXAONE/EXAONE-3.5-2.4B-Instruct",
    trust_remote_code=True,
    torch_dtype=torch.float16,
    device_map="cpu",
)

# 패치 적용
base_model = patch_exaone(base_model)

print("LoRA 병합 중...")
model = PeftModel.from_pretrained(base_model, "./avatar_lora")
model = model.merge_and_unload()

print("저장 중...")
model.save_pretrained("./avatar_merged", safe_serialization=True)
tokenizer = AutoTokenizer.from_pretrained(
    "LGAI-EXAONE/EXAONE-3.5-2.4B-Instruct",
    trust_remote_code=True,
)
tokenizer.save_pretrained("./avatar_merged")
print("병합 완료! ./avatar_merged 에 저장됨")