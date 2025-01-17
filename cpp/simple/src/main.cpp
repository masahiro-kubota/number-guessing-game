#include "main.hpp"

int main(){
  // ポリモーフィズムを使うためには、値ではなくポインタを生成するしかない。
  GameSetting game_setting(43, 7);
  GameState initial_game_state;
  GameManager game_manager(game_setting, initial_game_state);
  std::unique_ptr<IPresentation> user_presentation(game_manager);
}
