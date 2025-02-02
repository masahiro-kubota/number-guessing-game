#include "GameState.hpp"

GameState GameState::update_state(
  int input, const GameState & game_state, const GameSetting & game_setting) const
{
  return GameState(
    input, game_state.current_attempt_ + 1, game_setting.SECRET_NUM == input ? true : false);
}
