#!/usr/bin/env python3

import rclpy
from rclpy.node import Node

class MyNode(Node):
    def __init__(self):
        super().__init__("OOP_Node")
        self.counter = 0
        self.get_logger().info("Hola papus como están OOP OOP")
        self.create_timer(1.0, self.timer_func)

    def timer_func(self):
        self.get_logger().info("Hola papus infinitamente parte " + str(self.counter))
        self.counter += 1

def main(argos=None):
    rclpy.init(args=argos)
    node = MyNode()
    rclpy.spin(node)
    rclpy.shutdown()

if __name__ == "__main__":
    main()

