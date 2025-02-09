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

#include <gtest/gtest.h>
#include "subscriber/subscriber_member_function.hpp"


TEST(GameStateTest, UpdateStateSuccess) {
  std::cout << "Test started" << std::endl;

  GameSetting game_setting(43, 7);
  std::cout << "GameSetting initialized" << std::endl;

  GameState game_state(0, 0, false);
  std::cout << "GameState initialized" << std::endl;

  int input = 43;
  std::cout << "Calling update_state" << std::endl;
  GameState new_state = game_state.update_state(input, game_state, game_setting);

  std::cout << "update_state returned" << std::endl;

  EXPECT_EQ(new_state.last_input_number_, 43) << "last_input_number_ mismatch";
  EXPECT_EQ(new_state.current_attempt_, 1) << "current_attempt_ mismatch";
  EXPECT_TRUE(new_state.is_success_) << "is_success_ mismatch";

  std::cout << "Test finished" << std::endl;
}
