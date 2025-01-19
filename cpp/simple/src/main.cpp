#include "cliio/CliIo.hpp"
#include "GameManager.hpp"
#include "IIoHandler.hpp"


int main(){
  // ポリモーフィズムを使うためには、値ではなくポインタを生成するしかない。
  std::shared_ptr<IIoHandler> io_handler_ptr = std::make_shared<CliIo>(); // プレゼンテーション層の初期化
  GameManager game_manager;
  io_handler_ptr->set_callback(std::bind(&GameManager::process_data, &game_manager, std::placeholders::_1, io_handler_ptr)); // user_presentation.set_calbackでsubscribeしたとき用のコールバックを設定している。setter injection
  game_manager.start_game(io_handler_ptr);  // io_handler_ptrでpubish用のコールバックを実装している
}
