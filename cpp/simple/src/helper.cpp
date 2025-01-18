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

void GameManager::process_data(const std::string data) {
  if (game_state.current_attempt_ < game_setting.MAX_ATTEMPTS && !game_state.is_success_) {
    try {
      int num = std::stoi(data);
      // game_stateを使いまわしてる 
      game_state = game_state.update_state(num, game_state, game_setting);
      if (game_state.is_success_) {
        std::cout << "Correct" << std::endl;
      } else {
        std::cout << "Incorrect" << std::endl;
      }
    } catch (const std::invalid_argument&) {
      std::cout << "Invalid Input" << std::endl;
    } catch (const std::out_of_range& e) {
      std::cout << "Out of range" << std::endl;
    }
  } else {
    std::cout << "max attempts" << std::endl;
  }
}

void GameManager::start_game(const std::shared_ptr<IIoHandler>& io_handler_ptr) const {
  io_handler_ptr->start_io_handler();
}

void CliIo::get_input() const {
  std::string input;
  // whileでcinで入力をGameManagerの状態遷移の関数を実行する
  std::cout << "Input the number" << std::endl;
  std::cin >> input;
  callback(input); // CUI出力までをやってくれる。
}

void CliIo::set_callback(std::function<void(std::string)> cb) {
  callback = cb;
}    

void CliIo::start_io_handler() const {
  get_input(); // CUI出力までやってくれる これをwhileで動かせばいい。
}

