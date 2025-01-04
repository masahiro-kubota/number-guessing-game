#include <iostream>
#include "main.hpp"

GameState GameState::update_state(int input, GameState game_state, GameSetting game_setting) {
  return GameState(
    input,
    game_state.current_attempt_ + 1,
    game_setting.SECRET_NUM == input ? true : false
    );
}

GameManager::GameManager(DictIo dict_io) {
  GameSetting game_setting = GameSetting(43, 7);
  GameState game_state;
  while (game_state.current_attempt_ < game_setting.MAX_ATTEMPTS && !game_state.is_success_) {
    try {
      std::string input = dict_io.get_input();
      int num = std::stoi(input);
      game_state = game_state.update_state(num, game_state, game_setting);
      if (game_state.is_success_) {
        std::cout << "Correct" << std::endl;
      } else {
        std::cout << "Incorrect" << std::endl;
      }
    } catch (const std::invalid_argument&) {
      // 例外オブジェクトを使わない場合は、const参照を使わなくてもいい。
      std::cout << "Invalid Input" << std::endl;
    } catch (const std::out_of_range& e) {
      std::cout << "Out of range" << std::endl;
    }
  }
  if (game_state.current_attempt_ == game_setting.MAX_ATTEMPTS) {
    std::cout << "max attempts" << std::endl;
  }
}

std::string DictIo::get_input() {
  std::string input;
  std::cout << "Input the number" << std::endl;
  std::cin >> input;
  return input;
}



int main(){
  DictIo dict_io;
  GameManager game_manager(dict_io);
}

