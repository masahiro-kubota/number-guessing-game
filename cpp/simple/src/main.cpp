#include "main.hpp"

int main(){
  // ポリモーフィズムを使うためには、値ではなくポインタを生成するしかない。
  std::unique_ptr<IPresentation> user_presentation_ptr = PresentationFactory::CreatePresentationPtr();
  GameSetting game_setting = GameSetting(43, 7);
  GameState initial_game_state;
  GameManager game_manager(game_setting, initial_game_state, *user_presentation_ptr);
}
