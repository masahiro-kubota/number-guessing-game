#pragma once

#include <functional>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#include "GameSetting.hpp"
#include "GameState.hpp"
#include "IIoHandler.hpp"

class GameManager {
  private:
    GameSetting game_setting; // ゲーム設定（ほぼ不変）constにしてもいい。
    GameState game_state; // ゲームのstateを初期化
    std::array<GameState, 5> input_data_hisotry;

  public:
    GameManager();
    void start_game(const std::shared_ptr<IIoHandler>& io_handler_ptr) const;
    void process_data(InputData data, const std::shared_ptr<IIoHandler>& io_handler_ptr);
    void restart_game();
};
