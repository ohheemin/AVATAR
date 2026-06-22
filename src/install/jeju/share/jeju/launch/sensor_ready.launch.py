from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch_ros.actions import Node
from launch_ros.substitutions import FindPackageShare

def generate_launch_description():
    return LaunchDescription([
        #ublox_gps f9p 실행
        IncludeLaunchDescription(
            PythonLaunchDescriptionSource(
                [FindPackageShare('ublox_gps'), '/launch/ublox_gps_node_base-launch.py']
            )
        ),
        #VLP-16 실행 - 비전팀한테 런치파일 이름 물어보기(파이썬파일)
        IncludeLaunchDescription(
            PythonLaunchDescriptionSource(
                [FindPackageShare('velodyne_driver'), '/launch/velodyne_driver_node-VLP16-launch.py']
            )
        ),
        #microstrain 실행
        IncludeLaunchDescription(
            PythonLaunchDescriptionSource(
                [FindPackageShare('microstrain_inertial_driver'), '/launch/microstrain_launch.py']
                ),
                launch_arguments = {
                    'params_file': '/home/macaron/ros2_ws/src/microstrain_inertial/microstrain_inertial_driver/microstrain_inertial_driver_common/config/params.yml'}.items()
        ),
        #data_hub_smc_laocation 노드 실행
        Node(
            package='macaron_07',
            executable='data_hub_smc_location.py',
            name='data_hub_smc_location',
            output='screen'
        ),
    ])
    
    
    # 런치파일 생성시 setup.py에 지정되어있는 노드는 executable에 경로 따로 지정할 필요 X
