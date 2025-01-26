#pragma once

#include <functional>
#include <string>

#include "InputData.hpp"

class IIoHandler {
public:
  virtual void output_data(std::string data) const = 0;
  // Ioから入力があったら常にこのcallbackが呼ばれる。callbackはGameManageのインスタンスメソッド。callbackはユーザの入力内容等を含んだstructを引数としたvoidを変えす関数（中ではそのデータを処理する）。
  virtual void set_callback(std::function<void(InputData)> callback) = 0; 
  virtual void start_io_handler() = 0;
  virtual ~IIoHandler() = default;
};
