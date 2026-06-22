import rclpy
from rclpy.node import Node
from std_msgs.msg import Bool
from sensor_msgs.msg import JointState
import dynamixel_sdk as dxl  # 다이나믹셀 SDK
import math

# --- 다이나믹셀 제어 테이블 주소 (X-시리즈 공통) ---
ADDR_OPERATING_MODE         = 11
ADDR_TORQUE_ENABLE      = 64
ADDR_GOAL_POSITION      = 116
ADDR_PROFILE_VELOCITY   = 112
ADDR_PROFILE_ACCELERATION = 108
ADDR_PWM_LIMIT          = 36
ADDR_PRESENT_POSITION     = 132
ADDR_GOAL_PWM               = 100

# --- 추가된 제어 테이블 주소 (튜닝용) ---
ADDR_POSITION_D_GAIN      = 80  # 2 Byte
ADDR_FEEDFORWARD_2ND_GAIN = 88  # 2 Byte (Acceleration FF)
ADDR_FEEDFORWARD_1ST_GAIN = 90  # 2 Byte (Velocity FF)

# --- 튜닝 및 한계 설정 변수 ---
LIMIT_VELOCITY = 120
LIMIT_ACCELERATION = 30

# 잔떨림 방지를 위한 튜닝 파라미터 (사용 환경에 맞춰 조절하세요)
D_GAIN_VALUE     = 2000 # (기본값 0) 제동력을 높여 잔떨림 방지. 소음이 나면 낮추세요.
FF1_GAIN_VALUE   = 150  # (기본값 0) 속도 피드포워드. 목표 추종 지연(Lag)을 줄여줍니다.
DEADBAND_STEP    = 3    # (소프트웨어 데드밴드) 이전 명령과 3스텝(약 0.26도) 이하의 차이는 무시

# --- 프로토콜 및 통신 설정 ---
PROTOCOL_VERSION        = 2.0
BAUDRATE                = 1000000        # 다이나믹셀 위자드에서 설정한 통신 속도
DEVICENAME              = '/dev/ttyUSB0' # U2D2 통신 포트

TORQUE_ENABLE           = 1
TORQUE_DISABLE          = 0
OP_MODE_PWM             = 16 

class DxlHardwareController(Node):
    def __init__(self):
        super().__init__('dxl_hardware_controller')

        # 1. 다이나믹셀 포트 및 패킷 핸들러 초기화
        self.portHandler = dxl.PortHandler(DEVICENAME)
        self.packetHandler = dxl.PacketHandler(PROTOCOL_VERSION)

        # 포트 열기 및 보드레이트 설정
        if not self.portHandler.openPort():
            self.get_logger().error(f'포트를 열 수 없습니다: {DEVICENAME}. 권한(chmod)을 확인하세요.')
            return
        if not self.portHandler.setBaudRate(BAUDRATE):
            self.get_logger().error('보드레이트 설정 실패')
            return
            
        self.get_logger().info('다이나믹셀 포트 연결 성공!')

        # 2. 모터 ID 리스트 (1: XM430, 2~6: XL430, 7: 그리퍼)
        self.dxl_ids = [1, 2, 3, 4, 5, 6, 7]
        self.dxl_x_lim = [1, 3, 5]
        self.dxl_o_lim = [2, 4]
        self.dxl_6_lim = [6]

        # 이전 명령 상태를 저장할 딕셔너리 (소프트웨어 데드밴드용)
        self.last_sent_pos = {dxl_id: -1 for dxl_id in self.dxl_ids}

        # --- 로봇 팔 모터(1~6) 튜닝 설정 (Ruckig 최적화) ---
        for dxl_id in self.dxl_ids:
            if dxl_id != 7: # 그리퍼가 아닌 팔 관절의 경우
                # 내부 프로필 끄기 (Ruckig 궤적을 방해하지 않도록 0으로 설정)
                self.packetHandler.write4ByteTxRx(self.portHandler, dxl_id, ADDR_PROFILE_ACCELERATION, 0)
                self.packetHandler.write4ByteTxRx(self.portHandler, dxl_id, ADDR_PROFILE_VELOCITY, 0)
                
                # D-Gain 설정 (잔떨림 방지)
                self.packetHandler.write2ByteTxRx(self.portHandler, dxl_id, ADDR_POSITION_D_GAIN, D_GAIN_VALUE)
                
                # 피드포워드 게인 설정 (추종 성능 향상)
                self.packetHandler.write2ByteTxRx(self.portHandler, dxl_id, ADDR_FEEDFORWARD_1ST_GAIN, FF1_GAIN_VALUE)

        # --- 그리퍼(7) 설정 ---
        self.packetHandler.write4ByteTxRx(self.portHandler, 7, ADDR_PROFILE_ACCELERATION, LIMIT_ACCELERATION)
        self.packetHandler.write4ByteTxRx(self.portHandler, 7, ADDR_PROFILE_VELOCITY, LIMIT_VELOCITY)
        self.get_logger().info(f'Hand 속도({LIMIT_VELOCITY}) 및 가속도({LIMIT_ACCELERATION}) 제한 설정 완료')

        dxl_comm_result, dxl_error = self.packetHandler.write1ByteTxRx(self.portHandler, 7, ADDR_OPERATING_MODE, OP_MODE_PWM)
        if dxl_comm_result != dxl.COMM_SUCCESS:
            print(f"모드 변경 실패: {self.packetHandler.getTxRxResult(dxl_comm_result)}")
        else:
            print("PWM 제어 모드로 설정되었습니다.")

        dxl_pwm_result, dxl_error = self.packetHandler.write2ByteTxRx(self.portHandler, 7, ADDR_PWM_LIMIT, 442)
        if dxl_pwm_result != dxl.COMM_SUCCESS:
            self.get_logger().error(f'그리퍼 PWM 제한 실패: {self.packetHandler.getTxRxResult(dxl_pwm_result)}')
        else:
            self.get_logger().info('그리퍼 PWM 제한 ON')

        # --- 모든 모터 토크 켜기 ---
        for dxl_id in self.dxl_ids:
            dxl_comm_result, dxl_error = self.packetHandler.write1ByteTxRx(
                self.portHandler, dxl_id, ADDR_TORQUE_ENABLE, TORQUE_ENABLE)
            if dxl_comm_result != dxl.COMM_SUCCESS:
                self.get_logger().error(f'ID {dxl_id} 토크 켜기 실패: {self.packetHandler.getTxRxResult(dxl_comm_result)}')
            else:
                self.get_logger().info(f'ID {dxl_id} 토크 ON')

        # 3. URDF 관절 이름과 하드웨어 ID 매핑
        self.joint_name_to_id = {
            'joint_1': 1,
            'joint_2': 2,
            'joint_3': 3,
            'joint_4': 4,
            'joint_5': 5,
            'joint_6': 6
        }

        # 4. ROS 2 Subscriber 설정
        self.subscription = self.create_subscription(
            JointState,
            '/dynamixel_controller/joint_cmds',
            self.joint_state_callback,
            10)
        
        self.hand_sub = self.create_subscription(
            Bool,
            '/hand_open/right',
            self.hand_state_callback,
            10)

    def rad_to_dxl(self, rad):
        step = int((rad / (2.0 * math.pi)) * 4096.0) + 2048
        return max(0, min(4095, step)) 
    
    def rad_to_dxl_lim(self, rad):
        step = int((rad / (2.0 * math.pi)) * 4096.0) + 2048
        return max(2048, min(4095, step)) 
    
    def rad_to_dxl_6(self, rad):
        step = int((rad / (2.0 * math.pi)) * 4096.0) + 2048
        return max(2048, min(3072, step)) 

    def joint_state_callback(self, msg):
        # 수신된 관절 배열을 순회하며 모터에 명령 전송
        for i, name in enumerate(msg.name):
            if name in self.joint_name_to_id:
                dxl_id = self.joint_name_to_id[name]
                target_rad = msg.position[i]
                
                if dxl_id in self.dxl_x_lim:
                    target_pos = self.rad_to_dxl(target_rad)
                elif dxl_id in self.dxl_o_lim:
                    target_pos = self.rad_to_dxl_lim(target_rad)
                elif dxl_id in self.dxl_6_lim:
                    target_pos = self.rad_to_dxl_6(target_rad)
                else:
                    target_pos = self.rad_to_dxl(target_rad)

                # --- 5. Position Deadband (소프트웨어 데드밴드 필터 적용) ---
                if dxl_id != 7: # 팔 관절일 경우
                    # 이전 명령 값과 현재 목표 값의 차이가 데드밴드 스텝 이하이면 송신 생략
                    if abs(target_pos - self.last_sent_pos[dxl_id]) <= DEADBAND_STEP:
                        continue
                    
                    # 새 목표 위치 저장
                    self.last_sent_pos[dxl_id] = target_pos

                # 다이나믹셀에 목표 위치 쓰기
                self.packetHandler.write4ByteTxRx(
                    self.portHandler, dxl_id, ADDR_GOAL_POSITION, target_pos)
                
    def hand_state_callback(self, msg):
        hand_state = msg.data

        dxl_present_position = None

        if dxl_present_position is None:
            prev_pos = 0
        else:
            prev_pos = dxl_present_position

        dxl_present_position, dxl_comm_result, dxl_error = self.packetHandler.read4ByteTxRx(self.portHandler, 7, ADDR_PRESENT_POSITION)

        if hand_state == False:
            self.packetHandler.write2ByteTxRx(self.portHandler, 7, ADDR_GOAL_PWM, -300)
            if dxl_present_position > 700:
                if prev_pos == dxl_present_position:
                    self.packetHandler.write2ByteTxRx(self.portHandler, 7, ADDR_GOAL_PWM, -600)
                else:
                    self.packetHandler.write2ByteTxRx(self.portHandler, 7, ADDR_GOAL_PWM, -300)
        else:
            if dxl_present_position > 2048:
                self.packetHandler.write2ByteTxRx(self.portHandler, 7, ADDR_GOAL_PWM, 0)
            else:
                self.packetHandler.write2ByteTxRx(self.portHandler, 7, ADDR_GOAL_PWM, 300)
                if prev_pos == dxl_present_position:
                    self.packetHandler.write2ByteTxRx(self.portHandler, 7, ADDR_GOAL_PWM, 600)
                else:
                    self.packetHandler.write2ByteTxRx(self.portHandler, 7, ADDR_GOAL_PWM, 300)

        self.get_logger().info(f'Gripper Position: {dxl_present_position}')
            

    def destroy_node(self):
        # 프로그램 종료 시 안전을 위해 모든 모터 토크 해제
        for dxl_id in self.dxl_ids:
            self.packetHandler.write1ByteTxRx(self.portHandler, dxl_id, ADDR_TORQUE_ENABLE, TORQUE_DISABLE)
        self.portHandler.closePort()
        super().destroy_node()


def main(args=None):
    rclpy.init(args=args)
    node = DxlHardwareController()
    
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()

if __name__ == '__main__':
    main()