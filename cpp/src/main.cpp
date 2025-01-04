#include <iostream>
#include "main.hpp"

GameState GameState::UpdateState(int input) {


void GameManager::GameManager() {
  GameSetting game_setting = GameSetting(43, 7);
  GameState game_state = GameState();
  std::string input;
  while (game_state.current_attempt < game_setting.MAX_ATTEMPTS && !game_state.is_success) {
    std::cout << "Input the number" << std::endl;
    std::cin >> input;
    try {
      int num = std::stoi(input);
      game_state.current_attempt++;
      if (game_setting.SECRET_NUM == num) {
        std::cout << "Correct" << std::endl;
        is_success = true;
      } else {
        std::cout << "Incorrect" << std::endl;
      }
    } catch (std::invalid_argument) {
      // 例外オブジェクトを使わない場合は、const参照を使わなくてもいい。
      std::cout << "Invalid Input" << std::endl;
    } catch (const std::out_of_range& e) {
      std::cout << "Out of range" << std::endl;
    }
  }
  if (current_attempt == MAX_ATTEMPTS) {
    std::cout << "max attempts" << std::endl;
  }
}



int main(){
  Main main_instance(43, 7);
  main_instance.start();
}
