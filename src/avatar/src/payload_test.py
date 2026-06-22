#!/usr/bin/env python3

import rclpy
from rclpy.node import Node
from std_msgs.msg import Bool, Int32
from sensor_msgs.msg import JointState
import dynamixel_sdk as dxl
import numpy as np
import math

# --- 다이나믹셀 제어 테이블 주소 ---
ADDR_OPERATING_MODE         = 11
ADDR_TORQUE_ENABLE          = 64
ADDR_GOAL_POSITION          = 116
ADDR_PROFILE_VELOCITY       = 112
ADDR_PROFILE_ACCELERATION   = 108
ADDR_PWM_LIMIT              = 36
ADDR_PRESENT_POSITION       = 132
ADDR_GOAL_PWM               = 100
ADDR_POSITION_D_GAIN        = 80  
ADDR_FEEDFORWARD_2ND_GAIN   = 88  
ADDR_FEEDFORWARD_1ST_GAIN   = 90
ADDR_PRESENT_CURRENT        = 126  

# --- 튜닝 및 한계 설정 변수 ---
LIMIT_VELOCITY = 120
LIMIT_ACCELERATION = 30
D_GAIN_VALUE     = 2000 
FF1_GAIN_VALUE   = 150  
DEADBAND_STEP    = 3    

PROTOCOL_VERSION        = 2.0
BAUDRATE                = 1000000        
DEVICENAME              = '/dev/ttyUSB0' 
TORQUE_ENABLE           = 1
TORQUE_DISABLE          = 0
OP_MODE_PWM             = 16 

class DxlHardwareController(Node):
    def __init__(self):
        super().__init__('dxl_hardware_controller')

        self.portHandler = dxl.PortHandler(DEVICENAME)
        self.packetHandler = dxl.PacketHandler(PROTOCOL_VERSION)

        if not self.portHandler.openPort():
            self.get_logger().error(f'포트 열기 실패: {DEVICENAME}')
            return
        if not self.portHandler.setBaudRate(BAUDRATE):
            self.get_logger().error('보드레이트 설정 실패')
            return
            
        self.dxl_ids = [1, 2, 3, 4, 5, 6, 7]
        self.last_sent_pos = {dxl_id: -1 for dxl_id in self.dxl_ids}
        self.hand_prev_pos = -1 

        # --- SyncRead 초기화 ---
        self.groupSyncRead = dxl.GroupSyncRead(self.portHandler, self.packetHandler, ADDR_PRESENT_POSITION, 4)
        for i in range(1, 7):
            self.groupSyncRead.addParam(i)

        # --- 모터 설정 (가속도, 속도) ---
        for dxl_id in self.dxl_ids:
            if dxl_id != 7:
                self.packetHandler.write1ByteTxRx(self.portHandler, dxl_id, ADDR_TORQUE_ENABLE, TORQUE_DISABLE)
                self.packetHandler.write4ByteTxRx(self.portHandler, dxl_id, ADDR_PROFILE_ACCELERATION, 3)
                self.packetHandler.write4ByteTxRx(self.portHandler, dxl_id, ADDR_PROFILE_VELOCITY, 5)

                dxl_comm_result, dxl_error = self.packetHandler.write4ByteTxRx(self.portHandler, dxl_id, ADDR_PROFILE_ACCELERATION, 20)
                if dxl_comm_result != dxl.COMM_SUCCESS:
                    print("%s" % self.packetHandler.getTxRxResult(dxl_comm_result))
                elif dxl_error != 0:
                    print("%s" % self.packetHandler.getRxPacketError(dxl_error))

        # --- 토크 ON ---
        for dxl_id in self.dxl_ids:
            self.packetHandler.write1ByteTxRx(self.portHandler, dxl_id, ADDR_TORQUE_ENABLE, TORQUE_ENABLE)

        # Publisher 및 Timer 분리 생성
        self.payload_pub = self.create_publisher(Int32, "/payload", 10)
        self.joint_timer = self.create_timer(0.1, self.joint_state_callback)
        self.payload_timer = self.create_timer(0.1, self.payload_publisher)
        
        self.flag = 1
        self.init_time = 0.0 # 3초 대기를 위한 시간 저장 변수
        self.second_time = 0.0
        self.third_time = 0.0

    def rad_to_dxl(self, rad):
        step = int((rad / (2.0 * math.pi)) * 4096.0) + 2048
        return max(0, min(4095, step)) 

    def joint_state_callback(self):
        if self.flag == 1:
            # 1. 초기 위치(0도, 정중앙 기준)로 이동
            for dxl_id in self.dxl_ids:
                if dxl_id != 7:
                    # 안전을 위해 0(값)이 아닌 rad_to_dxl(0) 사용 -> 2048(0도)
                    self.packetHandler.write4ByteTxRx(self.portHandler, dxl_id, ADDR_GOAL_POSITION, int(self.rad_to_dxl(0))) 

            # 5번 모터 90도로 이동
            self.packetHandler.write4ByteTxRx(self.portHandler, 5, ADDR_GOAL_POSITION, int(self.rad_to_dxl(np.deg2rad(90)))) 

            self.get_logger().info("초기 이동 명령 완료! 3초간 대기합니다.")
            
            # 현재 시간을 기록하고 flag를 2로 넘김 (ROS를 멈추지 않음)
            self.init_time = self.get_clock().now().nanoseconds / 1e9
            self.flag = 2         
        
        elif self.flag == 2:
            # 2. 3초가 지났는지 체크
            self.second_time = self.get_clock().now().nanoseconds / 1e9
            if self.second_time - self.init_time >= 3.0:
                self.get_logger().info("3초 경과! 1번 모터를 100도로 들어 올립니다.")
                self.packetHandler.write4ByteTxOnly(self.portHandler, 1, ADDR_GOAL_POSITION, int(self.rad_to_dxl(np.deg2rad(100))))
                
                # 목적지 명령을 한 번만 보내기 위해 flag를 3으로 변경
                self.flag = 3

        elif self.flag == 3:

            self.third_time = self.get_clock().now().nanoseconds / 1e9
            if self.third_time - self.second_time >= 15.0:
                self.get_logger().info("3초 경과! 1번 모터를 100도로 들어 올립니다.")
                self.packetHandler.write4ByteTxOnly(self.portHandler, 1, ADDR_GOAL_POSITION, int(self.rad_to_dxl(np.deg2rad(0))))

                self.flag = 4

    def payload_publisher(self):
        msg = Int32()

        dxl_present_current, dxl_comm_result, dxl_error = self.packetHandler.read2ByteTxRx(self.portHandler, 1, ADDR_PRESENT_CURRENT)

        # self.COMM_SUCCESS -> dxl.COMM_SUCCESS 로 수정
        if dxl_comm_result != dxl.COMM_SUCCESS:
            # 패킷 에러 출력 로그는 주석 처리하거나 빈도를 낮추는 것이 터미널 가독성에 좋습니다.
            pass
        elif dxl_error != 0:
            pass
        else:
            if dxl_present_current > 0x7FFF: # 32767보다 크면 음수
                dxl_present_current -= 65536

            # 단위 변환 및 퍼센티지 계산
            real_current_mA = dxl_present_current * 2.69
            # 분모의 3209가 기준 최대 전류(Stall Current)라면 이 계산식은 정상 작동합니다.
            msg.data = int(np.abs(real_current_mA / 3209.0 * 100))

            print(f"[계산값] 1번 모터 실제 전류: {real_current_mA:.2f} mA | 부하량: {msg.data}%")

            self.payload_pub.publish(msg)

    def destroy_node(self):
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
        node.get_logger().info("키보드 인터럽트 발생, 노드를 종료합니다.")
    finally:
        node.destroy_node()
        rclpy.shutdown()

if __name__ == '__main__':
    main()