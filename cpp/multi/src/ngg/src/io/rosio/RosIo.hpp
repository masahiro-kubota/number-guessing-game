#pragma once

#include <iostream>

#include "IIoHandler.hpp"
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"


class RosIo : public IIoHandler {
  public:
    std::function<void(InputData)> callback;
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
    void output_data(std::string data) const override;
    void set_callback(std::function<void(InputData)> cb) override;
    void start_io_handler() override;
};

class RosIoCore : public rclcpp::Node {
  private:
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_;
  public:
    RosIoCore(RosIo* ros_io);
    void internal_callback(const std_msgs::msg::String::SharedPtr msg, RosIo* ros_io);
};

