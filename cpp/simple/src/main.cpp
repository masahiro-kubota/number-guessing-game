#include <iostream>
#include "main.hpp"

GameState GameState::update_state(int input, GameState game_state, GameSetting game_setting) {
  return GameState(
    input,
    game_state.current_attempt_ + 1,
    game_setting.SECRET_NUM == input ? true : false
    );
}

GameManager::GameManager(const IPresentation& presentation) {
  GameSetting game_setting = GameSetting(43, 7);
  GameState game_state;
  while (game_state.current_attempt_ < game_setting.MAX_ATTEMPTS && !game_state.is_success_) {
    try {
      std::string input = presentation.get_input();
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

std::string CliIo::get_input() const {
  std::string input;
  std::cout << "Input the number" << std::endl;
  std::cin >> input;
  return input;
}

std::unique_ptr<IPresentation> UserInterfaceFactory::CreateUserInterface() {
  return std::make_unique<CliIo>();
}

int main(){
  /*
  std::unique_ptr<CliIo> Cli_io_ptr = std::make_unique<CliIo>();
  GameManager game_manager(*cli_io_ptr);
  */
  GameManager game_manager(*UserInterfaceFactory::CreateUserInterface());
}

