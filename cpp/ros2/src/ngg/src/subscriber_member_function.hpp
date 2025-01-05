#ifndef SUBSCRIBER_MEMBER_FUNCTION_HPP_
#define SUBSCRIBER_MEMBER_FUNCTION_HPP_

#include <functional>
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

using std::placeholders::_1;

class GameSetting {
public:
  const int SECRET_NUM;
  const int MAX_ATTEMPTS;

  GameSetting(int secret_num, int max_attempts)
    : SECRET_NUM(secret_num), MAX_ATTEMPTS(max_attempts) {};
};

class GameState {
public:
  int last_input_number_;
  int current_attempt_;
  bool is_success_;
  GameState(int last_input_number = 0, int current_attempt = 0, bool is_success = false)
    : last_input_number_(last_input_number), current_attempt_(current_attempt), is_success_(is_success) {};
  GameState update_state(int input, GameState game_state, GameSetting game_setting);
};

class MinimalSubscriber : public rclcpp::Node {
public:
  MinimalSubscriber();

private:
  void topic_callback(const std_msgs::msg::String & msg);
  rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_;
  GameSetting game_setting;
  GameState game_state;
};


#endif // SUBSCRIBER_MEMBER_FUNCTION_HPP_
