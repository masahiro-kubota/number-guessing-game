#include "RosIo.hpp"

RosIo::RosIo() : Node("number_gussing_game") {
  publisher_ = this->create_publisher<std_msgs::msg::String>("topic_output", 10);
  subscription_ = this->create_subscription<std_msgs::msg::String>(
    "topic_input", 10, std::bind(&RosIo::internal_callback, this, std::placeholders::_1));
}

void RosIo::internal_callback(const std_msgs::msg::String::SharedPtr msg) {
  callback(InputData{msg->data});
}



void RosIo::output_data(std::string data) const {
  // whileでcinで入力をGameManagerの状態遷移の関数を実行する
  std::cout << data << std::endl;
  auto message = std_msgs::msg::String();
  message.data = data;
  publisher_->publish(message);
}

void RosIo::set_callback(std::function<void(InputData)> cb) {
  callback = cb;
}

void start_io_handler() const {
  rclcpp::init(0, nullptr);
  rclcpp::spin(std::make_shared<RosIo>());
  rclcpp::shutdown();
}
