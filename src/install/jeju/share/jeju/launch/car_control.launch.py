from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch_ros.actions import Node
from launch_ros.substitutions import FindPackageShare

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='jeju',
            executable='total_node.py',
            name = 'total_node',
            output='screen'
        ),
        
        Node(
            package='jeju',
            executable='teleop_key.py',
            name = 'teleop_key',
            output='screen'
        ),
        
        Node(
            package = 'joy',
            executable = 'joy_node',
            name = 'joy_node',
            output = 'screen',
        )
        
    ])