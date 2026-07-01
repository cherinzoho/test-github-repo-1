"""ROS2 launch file — starts arm and vision nodes."""

from __future__ import annotations

from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration, PathJoinSubstitution
from launch_ros.actions import Node
from launch_ros.substitutions import FindPackageShare


def generate_launch_description() -> LaunchDescription:
    use_sim = DeclareLaunchArgument("use_sim_time", default_value="false")
    config = PathJoinSubstitution([FindPackageShare("robot_arm"), "config", "arm_params.yaml"])

    arm = Node(
        package="robot_arm",
        executable="arm_node",
        name="arm",
        parameters=[config, {"use_sim_time": LaunchConfiguration("use_sim_time")}],
        output="screen",
    )

    vision = Node(
        package="perception",
        executable="vision_node",
        name="vision",
        output="screen",
    )

    return LaunchDescription([use_sim, arm, vision])
