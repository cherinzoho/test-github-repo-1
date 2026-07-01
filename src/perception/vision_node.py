"""ROS2 vision node — clean Python that passes all ruff checks."""

from __future__ import annotations

import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Image
from std_msgs.msg import String


class VisionNode(Node):
    """Subscribes to a camera topic and publishes object detections."""

    def __init__(self) -> None:
        super().__init__("vision_node")
        self._sub = self.create_subscription(Image, "camera/image_raw", self._on_image, 10)
        self._pub = self.create_publisher(String, "detections", 10)
        self.get_logger().info("VisionNode ready")

    def _on_image(self, msg: Image) -> None:
        label = self._detect(msg)
        out = String()
        out.data = label
        self._pub.publish(out)

    def _detect(self, msg: Image) -> str:
        # Placeholder — real inference goes here
        _ = msg
        return "object:unknown"


def main() -> None:
    rclpy.init()
    node = VisionNode()
    try:
        rclpy.spin(node)
    finally:
        node.destroy_node()
        rclpy.shutdown()


if __name__ == "__main__":
    main()
