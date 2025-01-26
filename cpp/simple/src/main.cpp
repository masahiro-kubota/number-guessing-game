#include "cliio/CliIo.hpp"
#include "GameManager.hpp"
#include "IIoHandler.hpp"

#include <glog/logging.h>

void func() {
  throw;
}


int main(int /*argc*/, char *argv[]){
  // google glogの初期化
  google::InitGoogleLogging(argv[0]);

  // クラッシュ時にスタックトレースを吐くシグナルハンドラを設定
  google::InstallFailureSignalHandler();

  // func(); # call std::terminate()
  // ポリモーフィズムを使うためには、値ではなくポインタを生成するしかない。
  std::shared_ptr<IIoHandler> io_handler_ptr = std::make_shared<CliIo>(); // プレゼンテーション層の初期化
  GameManager game_manager;
  io_handler_ptr->set_callback(std::bind(&GameManager::process_data, &game_manager, std::placeholders::_1, io_handler_ptr)); // user_presentation.set_calbackでsubscribeしたとき用のコールバックを設定している。setter injection
  game_manager.start_game(io_handler_ptr);  // io_handler_ptrでpubish用のコールバックを実装している
}
