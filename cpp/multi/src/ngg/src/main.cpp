#include "IoFactory.hpp"
#include "GameManager.hpp"
#include "IIoHandler.hpp"
#include <iostream>


int main(int argc, char* argv[]){
  if (argc < 2) {
    std::cerr << "Usage: " << argv[0] << std::endl;
    return 1;
  }

  std::string io_type = argv[1];
  // ポリモーフィズムを使うためには、値ではなくポインタを生成するしかない。
  //std::shared_ptr<IIoHandler> io_handler_ptr = std::make_shared<RosIo>(); // プレゼンテーション層の初期化
  std::shared_ptr<IIoHandler> io_handler_ptr = generate_io(io_type); // プレゼンテーション層の初期化
  GameManager game_manager;
  io_handler_ptr->set_callback(std::bind(&GameManager::process_data, &game_manager, std::placeholders::_1, io_handler_ptr)); // user_presentation.set_calbackでsubscribeしたとき用のコールバックを設定している。setter injection
  game_manager.start_game(io_handler_ptr);  // io_handler_ptrでpubish用のコールバックを実装している
}
