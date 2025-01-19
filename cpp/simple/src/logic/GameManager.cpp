#include "GameManager.hpp"

GameManager::GameManager()
  : game_setting(43, 7),
    game_state(){}

void GameManager::start_game(const std::shared_ptr<IIoHandler>& io_handler_ptr) const {
  io_handler_ptr->start_io_handler();
}

void GameManager::process_data(const std::string data, const std::shared_ptr<IIoHandler>& io_handler_ptr) {
  if (game_state.current_attempt_ < game_setting.MAX_ATTEMPTS && !game_state.is_success_) {
    try {
      int num = std::stoi(data);
      // game_stateを使いまわしてる メンバ変数に代入してある程度の不変性維持
      game_state = game_state.update_state(num, game_state, game_setting);
      if (game_state.is_success_) {
        io_handler_ptr->output_data("Correct");
        restart_game();
      } else {
        io_handler_ptr->output_data("Incorrect");
      }
    } catch (const std::invalid_argument&) {
      io_handler_ptr->output_data("Invalid Input");
    } catch (const std::out_of_range& e) {
      io_handler_ptr->output_data("Out of range");
    }
  } else {
    io_handler_ptr->output_data("max attempts");
    restart_game();
  }
}

void GameManager::restart_game() {
  game_state = GameState();
}