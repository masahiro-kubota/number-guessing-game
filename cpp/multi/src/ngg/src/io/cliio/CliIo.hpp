#pragma once

#include <iostream>

#include "IIoHandler.hpp"

class CliIo : public IIoHandler{
  private:
    std::function<void(InputData)> callback;
  public:
    void get_input() const;
    void output_data(std::string data) const override;
    void set_callback(std::function<void(InputData)> cb) override;
    void start_io_handler() override;
};
