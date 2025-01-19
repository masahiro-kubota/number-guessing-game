#include "CliIo.hpp"

void CliIo::output_data(std::string data) const {
  // whileでcinで入力をGameManagerの状態遷移の関数を実行する
  std::cout << data << std::endl;
}

void CliIo::get_input() const {
  std::string input;
  std::cin >> input;
  InputData input_data(input);
  callback(input_data); // CUI出力までをやってくれる。
}

void CliIo::set_callback(std::function<void(InputData)> cb) {
  callback = cb;
}    

void CliIo::start_io_handler() const {
  while (true) {
    output_data("Input the number"); // CUI出力までやってくれる これをwhileで動かせばいい。
    get_input();
  }
}
