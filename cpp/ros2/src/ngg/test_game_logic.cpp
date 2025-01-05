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

