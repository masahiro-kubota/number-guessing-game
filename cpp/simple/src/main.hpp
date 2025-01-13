#ifndef MAIN_HPP
#define MAIN_HPP

#include <iostream>
#include <memory>
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
  GameState update_state(int input, const GameState& game_state, const GameSetting& game_setting) const;
};

class IPresentation {
public:
  virtual std::string get_input() const = 0;
  virtual ~IPresentation() {}
};

class CliIo : public IPresentation{
  std::string get_input() const override;
};

class PresentationFactory {
public:
  static std::unique_ptr<IPresentation> CreatePresentationPtr(const GameManager& game_manager);
};

class GameManager {
public:
  GameManager(const GameSetting& game_setting, const GameState& initial_game_state, const IPresentation& i_presentation);
};

#endif
