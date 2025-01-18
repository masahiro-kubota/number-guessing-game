#include <iostream>
#include "main.hpp"

GameState GameState::update_state(int input, const GameState& game_state, const GameSetting& game_setting) const {
  return GameState(
    input,
    game_state.current_attempt_ + 1,
    game_setting.SECRET_NUM == input ? true : false
    );
}

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
      // game_stateを使いまわしてる 
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

void CliIo::output_data(std::string data) const {
  // whileでcinで入力をGameManagerの状態遷移の関数を実行する
  std::cout << data << std::endl;
}

void CliIo::get_input() const {
  std::string input;
  std::cin >> input;
  callback(input); // CUI出力までをやってくれる。
}

void CliIo::set_callback(std::function<void(std::string)> cb) {
  callback = cb;
}    

void CliIo::start_io_handler() const {
  while (true) {
    output_data("Input the number"); // CUI出力までやってくれる これをwhileで動かせばいい。
    get_input();
  }
}

