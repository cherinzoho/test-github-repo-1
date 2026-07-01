// BAD C++ — intentionally violates ROS2 checks.
// Used ONLY to test that the pre-commit hooks catch these patterns.
// DO NOT commit this file — it will be blocked.
//
// Violations:
//   [1] std::cout  → use RCLCPP_INFO instead
//   [2] while(true) → use rclcpp::TimerBase for periodic work
//   [3] sleep()    → use rclcpp::TimerBase, never block a callback

#include <iostream>   // triggers no-cout check
#include <unistd.h>

#include <rclcpp/rclcpp.hpp>

class BadNode : public rclcpp::Node
{
public:
  BadNode() : Node("bad_node")
  {
    std::cout << "BadNode started" << std::endl;  // [1] VIOLATION: std::cout
  }

  void spin_forever()
  {
    while (true) {  // [2] VIOLATION: while(true)
      std::cout << "tick" << std::endl;  // [1] VIOLATION: std::cout
      sleep(1);  // [3] VIOLATION: blocking sleep
    }
  }
};

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  auto node = std::make_shared<BadNode>();
  printf("Running bad node\n");  // [1] VIOLATION: printf
  rclcpp::spin(node);
  return 0;
}
