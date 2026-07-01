#pragma once

#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/float64_multi_array.hpp>
#include <sensor_msgs/msg/joint_state.hpp>

namespace robot_arm
{

class ArmNode : public rclcpp::Node
{
public:
  explicit ArmNode(const rclcpp::NodeOptions & options = rclcpp::NodeOptions{});

private:
  void joint_state_callback(const sensor_msgs::msg::JointState::SharedPtr msg);
  void send_command(const std::vector<double> & positions);

  rclcpp::Subscription<sensor_msgs::msg::JointState>::SharedPtr joint_sub_;
  rclcpp::Publisher<std_msgs::msg::Float64MultiArray>::SharedPtr cmd_pub_;
  rclcpp::TimerBase::SharedPtr heartbeat_timer_;

  std::vector<double> target_positions_;
  double max_velocity_{0.5};
};

}  // namespace robot_arm
