#ifndef MAIN_HPP
#define MAIN_HPP

#include <iostream>
class Main {
private:
  const int SECRET_NUM;
  const int MAX_ATTEMPTS;
  int current_attempt;
  bool is_success;
  std::string input;

public:
  Main(int secret_num, int max_attempts)
    : SECRET_NUM(secret_num), MAX_ATTEMPTS(max_attempts) {}
  void start();
};
#endif
