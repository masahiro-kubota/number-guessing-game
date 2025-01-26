#include "CliIo.hpp"

void CliIo::output_data(std::string data) const {
  // whileでcinで入力をGameManagerの状態遷移の関数を実行する
  std::cout << data << std::endl;
}

void CliIo::get_input() const {
  std::string user_input;
  std::cin >> user_input;
  InputData input_data(user_input);
  callback(input_data); // GameManagerの状態遷移の関数を実行する
}

void CliIo::set_callback(std::function<void(InputData)> cb) {
  callback = cb;
}    

void CliIo::start_io_handler() {
  while (true) {
    output_data("Input the number");
    get_input();
  }
}
