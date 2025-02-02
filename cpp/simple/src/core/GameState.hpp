#pragma once

#include "GameSetting.hpp"

struct GameState
{
  // constメンバ変数にするとGameStateの再代入ができなくなる。
  // どこでもメンバ変数を変えられるの危ないけど、変更したらGameStateに再代入することで明確化するようにする。
  int last_input_number_;
  int current_attempt_;
  bool is_success_;
  GameState(int last_input_number = 0, int current_attempt = 0, bool is_success = false)
  : last_input_number_(last_input_number),
    current_attempt_(current_attempt),
    is_success_(is_success){};
  GameState update_state(
    int input, const GameState & game_state, const GameSetting & game_setting) const;
};
