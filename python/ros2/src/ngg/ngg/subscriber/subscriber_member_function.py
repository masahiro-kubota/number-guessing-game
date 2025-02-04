import rclpy
from rclpy.node import Node

from std_msgs.msg import String

class MinimalSubscriber(Node):
    def __init__(self, game_manager):
        super().__init__('minimal_subscriber')
        self._game_manager = game_manager
        self.subscription_ = self.create_subscription(
                String,
                'topic',
                self.listener_callback,
                10)
        self.subscription_

    def listener_callback(self, msg):
        self.get_logger().info(f'I heard: {msg.data}')
        self._game_manager.process_data(msg.data)

class GameSetting:
    def __init__(self, secret_number, max_attempts):
        self._secret_number = secret_number
        self._max_attempts = max_attempts

class GameState:
    def __init__(self, input=0, current_attempt=0, is_success=False):
        self._last_input_number = input
        self._current_attempt = current_attempt
        self._is_success = is_success

    def update_state(self, input, game_setting):
        print(input)
        print(game_setting._secret_number==input)
        return GameState(
                input,
                self._current_attempt+1,
                game_setting._secret_number==input)

class GameManager:
    def __init__(self):
        self._game_setting = GameSetting(43, 7)
        self._game_state = GameState()

    def str_to_int(self, input):
        try:
            return int(input)
        except ValueError:
            print(f'{input}はintに変換できません')
            return None
    def process_data(self, input):
        input_int = self.str_to_int(input)
        if input_int:
            self._game_state = self._game_state.update_state(input_int, self._game_setting)
            if self._game_state._is_success:
                print("正解です")
            else:
                print("不正解です")




def main(args=None):
    rclpy.init(args=args)
    game_manager = GameManager()
    minimal_subscriber = MinimalSubscriber(game_manager)
    rclpy.spin(minimal_subscriber)
    minimal_subscriber.destroy_node()
    rclpy.shutdown()
