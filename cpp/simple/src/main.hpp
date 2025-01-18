#ifndef MAIN_HPP
#define MAIN_HPP

#include <functional>
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

class IIoHandler {
public:
  virtual void get_input() const = 0;
  virtual void set_callback(std::function<void(std::string)> callback) = 0; // Ioから入力があったら全てこのcallbackが呼ばれる。callbackはGameManageのインスタンスメソッド。callbackはユーザの入力内容等を含んだstructを引数としたvoidを変えす関数（中ではそのデータを処理する）。
  virtual void start_io_handler() const = 0;
  virtual ~IIoHandler() = default;
};


class CliIo : public IIoHandler{
  private:
    std::function<void(std::string)> callback;
  public:
    void get_input() const override;
    void set_callback(std::function<void(std::string)> cb) override;
    void start_io_handler() const override;
};

class GameManager {
  private:
    GameSetting game_setting; // ゲーム設定（ほぼ不変）
    GameState game_state; // ゲームのstateを初期化
  public:
    GameManager();
    void start_game(const std::shared_ptr<IIoHandler>& io_handler_ptr) const;
    void process_data(std::string data) ;
};

#endif
