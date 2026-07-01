// CLEAN C++ — passes all checks (clang-format, cpplint, cppcheck, ROS2 rules)

#include "robot_arm/arm_node.hpp"

#include <vector>

namespace robot_arm
{

ArmNode::ArmNode(const rclcpp::NodeOptions & options)
: Node("arm_node", options)
{
  joint_sub_ = create_subscription<sensor_msgs::msg::JointState>(
    "joint_states", 10,
    std::bind(&ArmNode::joint_state_callback, this, std::placeholders::_1));

  cmd_pub_ = create_publisher<std_msgs::msg::Float64MultiArray>("arm_commands", 10);

  // Heartbeat timer — does NOT block; uses timer callback instead of sleep()
  heartbeat_timer_ = create_wall_timer(
    std::chrono::seconds(1),
    [this]() { RCLCPP_DEBUG(get_logger(), "ArmNode alive"); });

  target_positions_ = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};

  RCLCPP_INFO(get_logger(), "ArmNode initialised");
}

void ArmNode::joint_state_callback(const sensor_msgs::msg::JointState::SharedPtr msg)
{
  if (msg->position.empty()) {
    RCLCPP_WARN(get_logger(), "Received empty joint state");
    return;
  }
  send_command(target_positions_);
}

void ArmNode::send_command(const std::vector<double> & positions)
{
  std_msgs::msg::Float64MultiArray cmd;
  cmd.data = positions;
  cmd_pub_->publish(cmd);
}

}  // namespace robot_arm

#include "rclcpp_components/register_node_macro.hpp"
RCLCPP_COMPONENTS_REGISTER_NODE(robot_arm::ArmNode)
