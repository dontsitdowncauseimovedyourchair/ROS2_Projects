from functools import partial

import rclpy
from rclpy.node import Node
from my_robot_interfaces.srv import SetLED

class BatteryNode(Node):
    def __init__(self):
        super().__init__("battery")
        self.battery_state_ = True #True means full
        self.time_count_ = 0
        self.timer_ = self.create_timer(1.0, self.callback_battery)
        self.client_ = self.create_client(SetLED, "set_led")

    def callback_battery(self):
        if not self.battery_state_ and self.time_count_ >= 6:
            self.get_logger().info("Battery Full, requesting LED off")
            self.send_msg(2, False)
            self.time_count_ = 0
            self.battery_state_ = not self.battery_state_
            return

        if self.battery_state_ and self.time_count_ >= 4:
            self.get_logger().info("Battery empty, requesting LED on")
            self.send_msg(2, True)
            self.time_count_ = 0
            self.battery_state_ = not self.battery_state_
            return

        self.time_count_ += 1

    def send_msg(self, ledN, state):
        while not self.client_.wait_for_service(5.0):
            self.get_logger().warn("Waiting for LEDs")
        msg = SetLED.Request()
        msg.led_number = ledN
        msg.state = state
        future = self.client_.call_async(msg)
        future.add_done_callback(partial(self.done_callback, request=msg))
        return

    def done_callback(self, future, request):
        if future.result().success:
            self.get_logger().info("LEDs turned " + "on" if request.state else "off")
        else:
            self.get_logger().warn("Request unfulfilled")


def main():
    rclpy.init()
    node = BatteryNode()
    rclpy.spin(node)
    rclpy.shutdown()

if __name__ == "__main__":
    main()