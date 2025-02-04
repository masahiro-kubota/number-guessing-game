# Copyright 2019 Open Source Robotics Foundation, Inc.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

#include <gtest/gtest.h>
#include "subscriber_member_function.hpp"

TEST(GameStateTest, UpdateStateSuccess) {
  GameSetting game_setting(43, 7);
  GameState game_state(0, 0, false);

  // 正しい入力の場合
  int input = 43;
  GameState new_state = game_state.update_state(input, game_state, game_setting);
  EXPECT_EQ(new_state.last_input_number_, 43);
  EXPECT_EQ(new_state.current_attempt_, 1);
  EXPECT_TRUE(new_state.is_success_);
}

TEST(GameStateTest, UpdateStateFailure) {
  GameSetting game_setting(43, 7);
  GameState game_state(0, 0, false);

  // 間違った入力の場合
  int input = 10;
  GameState new_state = game_state.update_state(input, game_state, game_setting);
  EXPECT_EQ(new_state.last_input_number_, 10);
  EXPECT_EQ(new_state.current_attempt_, 1);
  EXPECT_FALSE(new_state.is_success_);
}

TEST(GameStateTest, MaxAttemptsReached) {
  GameSetting game_setting(43, 7);
  GameState game_state(0, 6, false);

  // 最大試行数に達した場合
  int input = 10;
  GameState new_state = game_state.update_state(input, game_state, game_setting);
  EXPECT_EQ(new_state.current_attempt_, 7);
}
