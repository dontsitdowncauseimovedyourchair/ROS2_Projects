import rclpy
from rclpy.node import Node
from my_robot_interfaces.srv import SetLED
from my_robot_interfaces.msg import LEDPanelState

class LEDPanelNode(Node):
    def __init__(self):
        super().__init__("led_panel")
        self.leds_ = [False, False, False]
        self.server_ = self.create_service(SetLED, "/set_led", self.request_callback)
        self.publisher_ = self.create_publisher(LEDPanelState, "led_panel_state", 10)
        self.get_logger().info("LED panel started")

    def request_callback(self, request: SetLED.Request, response: SetLED.Response):
        self.leds_[request.led_number] = True if request.state else False
        msg = LEDPanelState()
        msg.leds = self.leds_
        self.publisher_.publish(msg)
        response.success = True
        return response

def main(args=None):
    rclpy.init(args=args)
    node = LEDPanelNode()
    rclpy.spin(node)
    rclpy.shutdown()


if __name__ == "__main__":
    main()