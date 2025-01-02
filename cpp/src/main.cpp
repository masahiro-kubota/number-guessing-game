#include <iostream>

int main(){
  const int SECRET_NUM = 43;
  const int MAX_ATTEMPTS = 7;
  int current_attempt = 0;
  bool is_success = false;
  std::string input;

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
      std::cout << "Invalid Input" << std::endl;
    } catch (const std::out_of_range& e) {
      std::cout << "Out of range" << std::endl;
    }
  }
  if (current_attempt == MAX_ATTEMPTS) {
    std::cout << "max attempts" << std::endl;
  }
}
