#include "IoFactory.hpp"
#include "GameManager.hpp"
#include "IIoHandler.hpp"
#include <iostream>


int main(int argc, char* argv[]){
  if (argc < 2) {
    std::cerr << "Usage: " << argv[0] << " <io_type> " << std::endl;
    return 1;
  }

  std::string io_type = argv[1];
  std::shared_ptr<IIoHandler> io_handler_ptr = generate_io(io_type); // IO層の初期化
  GameManager game_manager;
  // 入力を受け取ったとき用のコールバックを設定している。循環依存をsetter injectionで対応。
  io_handler_ptr->set_callback(std::bind(&GameManager::process_data, &game_manager, std::placeholders::_1, io_handler_ptr));
  game_manager.start_game(io_handler_ptr);
}
