#ifndef MAIN_HPP
#define MAIN_HPP

#include <iostream>

class GameSetting {
public:
  const int SECRET_NUM;
  const int MAX_ATTEMPTS;

  GameSetting(int secret_num, int max_attempts)
    : SECRET_NUM(secret_num), MAX_ATTEMPTS(max_attempts) {}
}

class GameState {
public:
  int current_attempt;
  bool is_success;
  GameState()
    : current_attempt(0), is_success(false) {}
  GameState UpdateState(int input) {}
}

class GameManager {
 void GameManager();
#endif
