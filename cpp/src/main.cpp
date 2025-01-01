#include <iostream>

int main(){
  const int SECRET_NUM = 43;
  std::cout << "Hello World!" << std::endl;
  std::string input;
  std::cin >> input;
  std::cout << input << std::endl;
  try {
    int num = std::stoi(input);
    if (SECRET_NUM == num) {
      std::cout << "Correct" << std::endl;
    } else {
      std::cout << "Incorrect" << std::endl;
    }
  } catch (std::invalid_argument) {
    std::cout << "Invalid Input" << std::endl;
  } catch (const std::out_of_range& e) {
    std::cout << "Out of range" << std::endl;
  }

}
