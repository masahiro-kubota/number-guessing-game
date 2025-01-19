#include "IIoHandler.hpp"

#include <iostream>

class CliIo : public IIoHandler{
  private:
    std::function<void(std::string)> callback;
  public:
    void get_input() const;
    void output_data(std::string data) const override;
    void set_callback(std::function<void(std::string)> cb) override;
    void start_io_handler() const override;
};