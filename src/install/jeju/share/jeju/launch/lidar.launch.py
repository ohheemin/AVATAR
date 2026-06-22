from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch_ros.actions import Node
from launch_ros.substitutions import FindPackageShare

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='jeju',
            executable='cone_detect.py',   
            name='cone_detect',
            output='screen',
        ),
        Node(
            package='jeju',
            executable='dynamic_by_pc2_test.py',   
            name='dynamic_by_pc2_test',
            output='screen',
        ),
        Node(
            package='jeju',
            executable='tunnel_distance.py',  
            name='tunnel_distance',
            output='screen',
        ),
        Node(
            package='jeju',
            executable='ransac.py',  
            name='ransac',
            output='screen',
        ),
    ])
