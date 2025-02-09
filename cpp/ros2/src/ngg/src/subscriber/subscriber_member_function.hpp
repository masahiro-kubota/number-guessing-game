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

#ifndef SUBSCRIBER_MEMBER_FUNCTION_HPP_
#define SUBSCRIBER_MEMBER_FUNCTION_HPP_

#include <diagnostic_updater/diagnostic_updater.hpp>
#include <rclcpp/rclcpp.hpp>

#include <std_msgs/msg/string.hpp>

#include <functional>
#include <memory>
#include <string>

using std::placeholders::_1;

class GameSetting
{
public:
  const int SECRET_NUM;
  const int MAX_ATTEMPTS;

  GameSetting(int secret_num, int max_attempts)
  : SECRET_NUM(secret_num), MAX_ATTEMPTS(max_attempts)
  {
  }
};

class GameState
{
public:
  int last_input_number_;
  int current_attempt_;
  bool is_success_;
  // GameState gs = 5;  // 意図せず GameState(5, 0, false) になるのを防ぐために explicit をつける
  explicit GameState(int last_input_number = 0, int current_attempt = 0, bool is_success = false)
  : last_input_number_(last_input_number),
    current_attempt_(current_attempt),
    is_success_(is_success)
  {
  }
  GameState update_state(int input, GameState game_state, GameSetting game_setting);
};

class MinimalSubscriber : public rclcpp::Node
{
public:
  MinimalSubscriber();

private:
  void topic_callback(const std_msgs::msg::String & msg);
  void produce_diagnostics(diagnostic_updater::DiagnosticStatusWrapper & stat);

  rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_;
  std::unique_ptr<diagnostic_updater::Updater> updater_;
  GameSetting game_setting;
  GameState game_state;
};

#endif  // SUBSCRIBER_MEMBER_FUNCTION_HPP_
