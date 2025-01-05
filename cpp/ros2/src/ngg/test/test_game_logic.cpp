#include <gtest/gtest.h>
#include "subscriber_member_function.hpp"


TEST(GameStateTest, UpdateStateSuccess) {
  std::cerr << "Test started" << std::endl;

  GameSetting game_setting(43, 7);
  std::cerr << "GameSetting initialized" << std::endl;

  GameState game_state(0, 0, false);
  std::cerr << "GameState initialized" << std::endl;

  std::cerr << "Test finished" << std::endl;
}
