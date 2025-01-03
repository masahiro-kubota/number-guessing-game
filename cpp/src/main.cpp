#include <iostream>
#include "main.hpp"

void Main::start() {
  current_attempt = 0;
  is_success = false;
  while (current_attempt < MAX_ATTEMPTS && !is_success) {
    std::cout << "Input the number" << std::endl;
    std::cin >> input;
    try {
      int num = std::stoi(input);
      current_attempt++;
      if (SECRET_NUM == num) {
        std::cout << "Correct" << std::endl;
        is_success = true;
      } else {
        std::cout << "Incorrect" << std::endl;
      }
    } catch (std::invalid_argument) {
      // 例外オブジェクトを使わない場合は、const参照を使わなくてもいい。
      std::cout << "Invalid Input" << std::endl;
    } catch (const std::out_of_range& e) {
      std::cout << "Out of range" << std::endl;
    }
  }
  if (current_attempt == MAX_ATTEMPTS) {
    std::cout << "max attempts" << std::endl;
  }
}

int main(){
  Main main_instance(43, 7);
  main_instance.start();
}
