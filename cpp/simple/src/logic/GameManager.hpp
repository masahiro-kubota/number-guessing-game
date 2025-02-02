#pragma once

#include "GameSetting.hpp"
#include "GameState.hpp"
#include "IIoHandler.hpp"

#include <functional>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

class GameManager
{
private:
  GameSetting game_setting;  // ゲーム設定（ほぼ不変）constにしてもいい。
  GameState game_state;      // ゲームのstateを初期化
  std::vector<GameState> input_data_history;

public:
  GameManager();
  void start_game(const std::shared_ptr<IIoHandler> & io_handler_ptr) const;
  void process_data(InputData data, const std::shared_ptr<IIoHandler> & io_handler_ptr);
  std::vector<GameState> update_input_data_history();
  void restart_game();
};
