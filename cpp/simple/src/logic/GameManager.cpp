#include "GameManager.hpp"

#include <iostream>

GameManager::GameManager() : game_setting(43, 7), game_state(), input_data_history(7)
{
}

void GameManager::start_game(const std::shared_ptr<IIoHandler> & io_handler_ptr) const
{
  io_handler_ptr->start_io_handler();  // ioの入力待ちになる
}

// ユーザーごとに処理を変えたりみたいなことをするときは、ここが複雑になるので整理する。
void GameManager::process_data(
  const InputData data, const std::shared_ptr<IIoHandler> & io_handler_ptr)
{
  if (game_state.current_attempt_ < game_setting.MAX_ATTEMPTS && !game_state.is_success_) {
    try {
      int num = std::stoi(data.user_input);
      game_state = game_state.update_state(num, game_state, game_setting);
      input_data_history = update_input_data_history();
      if (game_state.is_success_) {
        io_handler_ptr->output_data("Correct");
        for (GameState gs : input_data_history) {
          io_handler_ptr->output_data(std::to_string(gs.last_input_number_));
        }
        restart_game();
      } else {
        io_handler_ptr->output_data("Incorrect");
      }
    } catch (const std::invalid_argument &) {
      io_handler_ptr->output_data("Invalid Input");
    } catch (const std::out_of_range & e) {
      io_handler_ptr->output_data("Out of range");
    }
  } else {
    io_handler_ptr->output_data("max attempts");
    restart_game();
  }
}

std::vector<GameState> GameManager::update_input_data_history()
{
  input_data_history[game_state.current_attempt_ - 1] = game_state;
  std::vector<GameState> updated_input_data_history = input_data_history;
  return updated_input_data_history;
}

void GameManager::restart_game()
{
  game_state = GameState();
}
