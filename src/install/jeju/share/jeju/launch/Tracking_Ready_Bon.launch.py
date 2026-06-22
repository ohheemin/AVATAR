# Tracking_Ready_Bon

from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch_ros.actions import Node
from launch_ros.substitutions import FindPackageShare

def generate_launch_description():
    return LaunchDescription([
        #tracking_planner_pre 노드 실행
        Node(
            package='macaron_07',
            executable='tracking_planner_bon.py',
            output='screen'
        ),
        
        Node(
            package='macaron_07',
            executable='state_bon.py',
            output='screen'
        ),
        
    ])