#pragma once

class GameSetting {
public:
  const int SECRET_NUM;
  const int MAX_ATTEMPTS;

  GameSetting(int secret_num, int max_attempts)
    : SECRET_NUM(secret_num), MAX_ATTEMPTS(max_attempts) {};
};
