// Copyright 2019 Open Source Robotics Foundation, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "subscriber_member_function.hpp"

MinimalSubscriber::MinimalSubscriber()
: Node("minimal_subscriber"), game_setting(43, 7), game_state()
{
  subscription_ = this->create_subscription<std_msgs::msg::String>(
    "topic", 10, std::bind(&MinimalSubscriber::topic_callback, this, _1));
  updater_ = std::make_unique<diagnostic_updater::Updater>(this);
  updater_->setHardwareID("number_guessing_game");
  updater_->add("game_status", this, &MinimalSubscriber::produce_diagnostics);
}

void MinimalSubscriber::produce_diagnostics(diagnostic_updater::DiagnosticStatusWrapper & stat)
{
  if (game_state.is_success_) {
    stat.summary(diagnostic_msgs::msg::DiagnosticStatus::OK, "Game completed successfully");
  } else if (game_state.current_attempt_ >= game_setting.MAX_ATTEMPTS) {
    stat.summary(diagnostic_msgs::msg::DiagnosticStatus::ERROR, "Game over - max attempts reached");
  } else {
    stat.summary(diagnostic_msgs::msg::DiagnosticStatus::WARN, "Game in progress");
  }
}

void MinimalSubscriber::topic_callback(const std_msgs::msg::String & msg)
{
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
      updater_->force_update();
    } catch (const std::invalid_argument &) {
      // 例外オブジェクトを使わない場合は、const参照を使わなくてもいい。
      std::cout << "Invalid Input" << std::endl;
    } catch (const std::out_of_range & e) {
      std::cout << "Out of range" << std::endl;
    }
  }
  if (game_state.current_attempt_ == game_setting.MAX_ATTEMPTS) {
    std::cout << "max attempts" << std::endl;
    updater_->force_update();
  }
}

GameState GameState::update_state(int input, GameState game_state, GameSetting game_setting)
{
  return GameState(
    input, game_state.current_attempt_ + 1, game_setting.SECRET_NUM == input ? true : false);
}
