#include <iostream>
#include "main.hpp"

GameState GameState::update_state(int input, const GameState& game_state, const GameSetting& game_setting) const {
  return GameState(
    input,
    game_state.current_attempt_ + 1,
    game_setting.SECRET_NUM == input ? true : false
    );
}

GameManager::GameManager(const GameSetting& game_setting, const GameState& initial_game_state, const IPresentation& presentation) {
  GameState game_state = initial_game_state;
  while (game_state.current_attempt_ < game_setting.MAX_ATTEMPTS && !game_state.is_success_) {
    std::cout << game_state.current_attempt_ << std::endl;
    try {
      std::string input = presentation.get_input();
      int num = std::stoi(input);
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

std::unique_ptr<IPresentation> PresentationFactory::CreatePresentationPtr() {
  return std::make_unique<CliIo>();
}


