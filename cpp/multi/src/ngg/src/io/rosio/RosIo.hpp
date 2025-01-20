#pragma once

#include <iostream>

#include "IIoHandler.hpp"
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"



class RosIo : public rclcpp::Node {
  private:
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_;
  public:
    RosIo();
    void internal_callback(const std_msgs::msg::String::SharedPtr msg);
    
    
};

class RosIoAdapter : public IIoHandler {
  private:
    std::function<void(InputData)> callback;
  public:
    void output_data(std::string data) const override;
    void set_callback(std::function<void(InputData)> cb) override;
    void start_io_handler() const override;
};