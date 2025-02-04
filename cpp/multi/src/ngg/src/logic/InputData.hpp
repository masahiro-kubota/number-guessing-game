#pragma once

#include <chrono>
#include <string>

/*
  InputDataクラス
  ユーザの入力内容を保持するクラス
*/
struct InputData {
  const std::chrono::high_resolution_clock::time_point timestamp;
  const std::string user_name;
  const std::string user_input;

  InputData(std::string input = "default", std::string name = "default")
    : timestamp(std::chrono::high_resolution_clock::now()),
      user_name(name),
      user_input(input){}
};
