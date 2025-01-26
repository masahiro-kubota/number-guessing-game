#include "RosIo.hpp"

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


void RosIo::start_io_handler() { // ここでNodeのインスタンスを生成している。
  rclcpp::init(0, nullptr);
  rclcpp::spin(std::make_shared<RosIoCore>(this));
  rclcpp::shutdown();
}


RosIoCore::RosIoCore(RosIo* ros_io) : Node("number_guessing_game") {
  ros_io->publisher_ = this->create_publisher<std_msgs::msg::String>("topic_output", 10);
  subscription_ = this->create_subscription<std_msgs::msg::String>(
    "topic_input", 10,
    [this, ros_io](const std_msgs::msg::String::SharedPtr msg) {
      this->internal_callback(msg, ros_io);
    }); // RosIoのcallback関数を呼び出す
}

void RosIoCore::internal_callback(const std_msgs::msg::String::SharedPtr msg, RosIo* ros_io) {
  ros_io->callback(InputData{msg->data});
}

