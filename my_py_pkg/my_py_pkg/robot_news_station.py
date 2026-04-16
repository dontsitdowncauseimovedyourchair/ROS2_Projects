import rclpy
from rclpy.node import Node
from example_interfaces.msg import String

class RobotNewsStationNode(Node):
    def __init__(self, node_name: str):
        super().__init__(node_name)
        self.publisher_ = self.create_publisher(String, "robots_news", 10)
        self.robot_name = "C3P0"
        self.create_timer(0.5, self.publish_news)
        self.get_logger().info("Robots news station has been set up")

    def publish_news(self):
        msg = String()
        msg.data = "Hello papus, this is " + self.robot_name + "from the robot news channel"
        self.publisher_.publish(msg)


def main():
    rclpy.init()
    node = RobotNewsStationNode("robot_news_station")
    rclpy.spin(node)
    rclpy.shutdown()

if __name__ == "__main__":
    main()