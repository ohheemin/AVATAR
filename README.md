# AVATAR: Human Pose to Robot Arm Teleoperation

> **카메라 기반 인체 자세 추정을 통한 로봇팔 텔레오퍼레이션 시스템**

실시간 인체 포즈 추정 기술을 이용하여 사람의 팔 움직임을 감지하고, 이를 로봇팔의 관절 각도로 변환하여 직관적인 텔레오퍼레이션을 구현합니다.

---

## 주요 기능

- **실시간 포즈 추정**: MediaPipe를 활용한 고정확도 인체 포즈 감지
- **자동 포즈 매핑**: 인간 팔의 각도를 로봇팔 관절각으로 실시간 변환
- **멀티 카메라 지원**: Intel RealSense D435i를 통한 RGB-D 입력
- **직관적 제어**: 사람의 자연스러운 팔 움직임으로 로봇 제어
- **시뮬레이션 환경**: Isaac Sim에서 검증 및 디버깅 가능
- **상태 모니터링**: 실시간 포즈 데이터 및 로봇 상태 시각화

---

## 스택

### Core Technologies
- **로보틱스**: ROS2 Humble, MoveIt2
- **포즈 추정**: MediaPipe, MarkerlessHuman Pose Estimation
- **센서**: Intel RealSense D435i
- **모터 제어**: Dynamixel (XM430-W350, XL430-W250)

### Software Stack
- **언어**: Python 3.10+
- **OS**: Ubuntu 22.04 LTS
- **프레임워크**: PyTorch, TensorFlow
- **시각화**: OpenCV, RViz2

---

## 요구사항

### 시스템 요구사항
```
OS: Ubuntu 22.04 LTS
Python: 3.10 이상
ROS2: Humble
메모리: 8GB 이상 (권장 16GB)
GPU: NVIDIA (권장) - CUDA 11.8+
```

### 하드웨어 요구사항
- Techman TM12 로봇팔 또는 호환 로봇
- Intel RealSense D435i 또는 D455
- 로봇 제어용 PC (권장: i7 이상)

### 주요 Python 패키지
```
mediapipe >= 0.10.0
opencv-python >= 4.8.0
numpy >= 1.24.0
scipy >= 1.11.0
torch >= 2.0.0
pyrealsense2 >= 2.54.0
```

---

## 설치 및 실행

### ROS2 Humble 설치
```bash
# ROS2 공식 설치 가이드 참고
# https://docs.ros.org/en/humble/Installation.html

source /opt/ros/humble/setup.bash
```

### 워크스페이스 설정
```bash
# 저장소 클론
git clone https://github.com/ohheemin/AVATAR.git
cd AVATAR

# 의존성 설치
rosdep install --from-paths src --ignore-src -r -y

# 빌드
colcon build --symlink-install
source install/setup.bash
```
---

## 사용 방법

### 기본 텔레오퍼레이션 플로우

1. **카메라 연결**
   - Intel RealSense 카메라를 USB 포트에 연결
   - `ros2 run avatar camera_node`로 카메라 노드 실행

2. **포즈 추정 시작**
   - MediaPipe가 실시간으로 팔 관절 좌표 추출
   - 3D 포즈 데이터를 ROS 토픽으로 발행

3. **포즈 매핑**
   - 인간 팔의 각도를 로봇팔 좌표계로 변환
   - IK(역기구학) 계산으로 관절각 도출

4. **로봇 제어**
   - 계산된 관절각을 로봇에 명령
   - 피드백을 통한 제어 안정화

### 키보드 명령어 (RViz)
```
SPACE  : 로봇 제어 활성화/해제
R      : 초기 자세로 리셋
G      : 그리퍼 제어 토글
Q      : 프로그램 종료
```

---

## 주요 구성 요소

### Pose Estimator (포즈 추정)
```python
# MediaPipe Holistic 모델 사용
# 입력: RGB 이미지 (640x480)
# 출력: 손목(wrist), 팔꿈치(elbow), 어깨(shoulder) 3D 좌표
```
``
---

## 트러블슈팅

### 카메라 연결 안 됨
```bash
# 권한 확인
ls -la /dev/video*

# udev 규칙 확인
cat /etc/udev/rules.d/99-realsense-libusb.rules

# 카메라 리셋
ros2 service call /camera/reset std_srvs/srv/Empty
```

### 포즈 추정 오류율 높음
- 조명 개선 (밝은 환경 필요)
- 카메라 클리닝
- MediaPipe 신뢰도 임계값 조정 (config/mediapipe.yaml)

### 로봇 응답 지연
```bash
# ROS2 QoS 설정 확인
# config/qos.yaml 에서 지연시간 최적화
```

---

## 조원

| 이름 | 역할 |
|------|------|
| **오희민** | 시스템 아키텍처, ROS2 통합, 시뮬레이션 |
| **이준수** | 포즈 추정, MediaPipe 최적화 |
| **한찬우** | 로봇 제어, 하드웨어 통합 |

---

## 🔗 링크

- **GitHub Repository**: https://github.com/ohheemin/AVATAR
- **Issues & Bug Reports**: [GitHub Issues](https://github.com/ohheemin/AVATAR/issues)

---

<div align="center">

**Made with ❤️ by AVATAR Team**

*Human Arm Pose → Robot Arm Control*

</div>
