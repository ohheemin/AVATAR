# AVATAR: Human Pose to Robot Arm Teleoperation

> **카메라 기반 인체 자세 추정을 통한 로봇팔 텔레오퍼레이션 시스템**

실시간 인체 포즈 추정 기술을 이용하여 사람의 팔 움직임을 감지하고, 이를 로봇팔의 관절 각도로 변환하여 직관적인 텔레오퍼레이션 구현

<img width="300" height="300" alt="트랙별 종합설계 프로젝트 1조  아바타" src="https://github.com/user-attachments/assets/db0cc444-f416-47cc-8bf0-ddf86c8655f3" />


## Stack

### Core Technologies
- **Robotics**: ROS2 Humble, MoveIt2
- **Pose Estimation**: MediaPipe, MarkerlessHuman Pose Estimation
- **Sensor**: Intel RealSense D435i
- **Motor**: Dynamixel (XM430-W350, XL430-W250)

### Software Stack
- **Language**: Python 3.10+
- **OS**: Ubuntu 22.04 LTS
- **API**: PyTorch, TensorFlow
- **Visualization**: OpenCV, RViz2

---

## PC Requirement

### OS
```
OS: Ubuntu 22.04 LTS
Python: 3.10 이상
ROS2: Humble
메모리: 8GB 이상 (권장 16GB)
GPU: NVIDIA (권장) - CUDA 11.8+
```

### Hardware
- Dynamixel XM, XL
- Intel RealSense D435i 또는 D455
- 로봇 제어용 PC (권장: i7 이상)

### Main Python Package
```
mediapipe >= 0.10.0
opencv-python >= 4.8.0
numpy >= 1.24.0
scipy >= 1.11.0
torch >= 2.0.0
pyrealsense2 >= 2.54.0
```

---

## Installation

### ROS2 Humble Installation
```bash
# ROS2 공식 설치 가이드 참고
# https://docs.ros.org/en/humble/Installation.html

source /opt/ros/humble/setup.bash
```

### Builing Your Workspace
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

## How to

### Pipeline

1. **D435I Connect**
   - Intel RealSense 카메라를 USB 포트에 연결
   - `ros2 run avatar camera_node`로 카메라 노드 실행

2. **Pose Estimation**
   - MediaPipe가 실시간으로 팔 관절 좌표 추출
   - 3D 포즈 데이터를 ROS 토픽으로 발행

3. **Pose Mapping**
   - 인간 팔의 각도를 로봇팔 좌표계로 변환
   - IK(역기구학) 계산으로 관절각 도출

4. **Manipulator Control**
   - 계산된 관절각을 로봇에 명령
   - 피드백을 통한 제어 안정화
---

## Function

### Pose Estimator (포즈 추정)
```python
# MediaPipe Holistic 모델 사용
# 입력: RGB 이미지 (640x480)
# 출력: 손목(wrist), 팔꿈치(elbow), 어깨(shoulder) 3D 좌표
```
 
---

## Team Avatar

| 이름 | 역할 |
|------|------|
| **오희민** | Vision,LLM |
| **이준수** | Planning |
| **한찬우** | GUI, Hardware |

---

## Link

- **GitHub Repository**: https://github.com/ohheemin/AVATAR
- **Issues & Bug Reports**: [GitHub Issues](https://github.com/ohheemin/AVATAR/issues)

---

<div align="center">

**Made with by AVATAR Team**

*Human Arm Pose → Robot Arm Control*

</div>
