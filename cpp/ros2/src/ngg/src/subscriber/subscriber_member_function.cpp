#include "subscriber_member_function.hpp"

MinimalSubscriber::MinimalSubscriber()
: Node("minimal_subscriber"),
  game_setting(43,7),
  game_state() {
  subscription_ = this->create_subscription<std_msgs::msg::String>(
    "topic", 10, std::bind(&MinimalSubscriber::topic_callback, this, _1));
}

void MinimalSubscriber::topic_callback(const std_msgs::msg::String & msg) {
    RCLCPP_INFO(this->get_logger(), "I heard: '%s'", msg.data.c_str());
    if (game_state.current_attempt_ < game_setting.MAX_ATTEMPTS && !game_state.is_success_) {
      try {
        std::string input = msg.data;
        int num = std::stoi(input);
        game_state = game_state.update_state(num, game_state, game_setting);
        if (game_state.is_success_) {
          std::cout << "Correct" << std::endl;
        } else {
          std::cout << "Incorrect" << std::endl;
        }
      } catch (const std::invalid_argument&) {
        // 例外オブジェクトを使わない場合は、const参照を使わなくてもいい。
        std::cout << "Invalid Input" << std::endl;
      } catch (const std::out_of_range& e) {
        std::cout << "Out of range" << std::endl;
      }
    }
    if (game_state.current_attempt_ == game_setting.MAX_ATTEMPTS) {
      std::cout << "max attempts" << std::endl;
    }
}

GameState GameState::update_state(int input, GameState game_state, GameSetting game_setting) {
  return GameState(
    input,
    game_state.current_attempt_ + 1,
    game_setting.SECRET_NUM == input ? true : false
    );
}

