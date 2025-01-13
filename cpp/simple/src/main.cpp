#include "main.hpp"

int main(){
  // ポリモーフィズムを使うためには、値ではなくポインタを生成するしかない。
  GameSetting game_setting = GameSetting(43, 7);
  GameState initial_game_state;
  GameManager game_manager(game_setting, initial_game_state);
  tion> user_presentation = PresentationFactory::CreatePresentationPtr(game_manager);
}
