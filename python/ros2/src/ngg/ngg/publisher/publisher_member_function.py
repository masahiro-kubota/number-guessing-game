import rclpy
from rclpy.node import Node

from std_msgs.msg import String

class MinimalPublisher(Node):
    def __init__(self):
        super().__init__('minimal_publisher')
        self.publisher_ = self.create_publisher(String,'topic', 10)
        # timer_period = 0.5
        # self.timer = self.create_timer(timer_period, self.timer_callback)
        # self.i = 0

    def timer_callback(self):
        msg = String()
        msg.data = f'Hello World: {self.i}'
        self.publisher_.publish(msg)
        self.get_logger().info(f'Publishing: {msg.data}')
        self.i += 1

    def publish_cli_input(self):
        while True:
            msg = String()
            msg.data = input('Input a number: ')
            self.publisher_.publish(msg)
            self.get_logger().info(f'Publishing: {msg.data}')



def main(args=None):
    rclpy.init(args=args)
    minimal_publisher = MinimalPublisher() # ノードの初期化
    minimal_publisher.publish_cli_input()
    rclpy.spin(minimal_publisher)
    minimal_publisher.destroy_node()
    rclpy.shutdown()

