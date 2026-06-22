#!/usr/bin/env python3
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node

def generate_launch_description():
    # 런치 인자들
    cam_params_arg = DeclareLaunchArgument(
        'cam_params', default_value='/home/ohheemin/ros2_ws/brio.yaml'
    )
    topic_arg   = DeclareLaunchArgument('topic',   default_value='/image_raw')
    outfile_arg = DeclareLaunchArgument('outfile', default_value='/home/ohheemin/brio_record.mp4')
    fps_arg     = DeclareLaunchArgument('fps',     default_value='30')

    cam_params = LaunchConfiguration('cam_params')
    topic      = LaunchConfiguration('topic')
    outfile    = LaunchConfiguration('outfile')
    fps        = LaunchConfiguration('fps')

    cam_node = Node(
        package='v4l2_camera',
        executable='v4l2_camera_node',
        name='v4l2_camera_node',
        output='screen',
        parameters=[cam_params],   # <-- params 파일로 안전하게 타입 전달
    )

    rec_node = Node(
        package='video_recorder',
        executable='record_video',
        name='video_recorder',
        output='screen',
        parameters=[{
            'image_topic': topic,
            'outfile': outfile,
            'fps': fps,  # 기록 FPS 메타
        }],
    )

    return LaunchDescription([
        cam_params_arg, topic_arg, outfile_arg, fps_arg,
        cam_node,
        rec_node,
    ])
