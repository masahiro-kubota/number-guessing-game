#pragma once

#include <functional>
#include <memory>
#include <stdexcept>
#include <string>

#include "GameSetting.hpp"
#include "GameState.hpp"
#include "IIoHandler.hpp"

class GameManager {
  private:
    GameSetting game_setting; // ゲーム設定（ほぼ不変）constにしてもいい。
    GameState game_state; // ゲームのstateを初期化
  public:
    GameManager();
    void start_game(const std::shared_ptr<IIoHandler>& io_handler_ptr) const;
    void process_data(std::string data, const std::shared_ptr<IIoHandler>& io_handler_ptr); // IoHandlerから呼び出されるcallback
    void restart_game();
};