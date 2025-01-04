#ifndef MAIN_HPP
#define MAIN_HPP

#include <iostream>
#include <vector>

class GameSetting {
public:
  const int SECRET_NUM;
  const int MAX_ATTEMPTS;

  GameSetting(int secret_num, int max_attempts)
    : SECRET_NUM(secret_num), MAX_ATTEMPTS(max_attempts) {};
};

class GameState {
public:
  int last_input_number_;
  int current_attempt_;
  bool is_success_;
  GameState(int last_input_number = 0, int current_attempt = 0, bool is_success = false)
    : last_input_number_(last_input_number), current_attempt_(current_attempt), is_success_(is_success) {};
  GameState update_state(int input, GameState game_state, GameSetting game_setting);
};

class DictIo {
public:
  std::string get_input();
};

class GameManager {
public:
  GameManager(DictIo dict_io);
};

#endif
