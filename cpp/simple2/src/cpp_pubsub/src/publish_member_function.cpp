#include "publish_member_function.hpp"

using namespace std::chrono_literals;

MinimalPublisher::MinimalPublisher() : Node("minimal_publisher"), count_(0) {
  publisher_ = this->create_publisher<std_msgs::msg::String>("topic", 10);
  timer_ = this->create_wall_timer(
      500ms, std::bind(&MinimalPublisher::timer_callback, this));
  subscription_ = this->create_subscription<std_msgs::msg::String>(
    "topic", 10, std::bind(&MinimalPublisher::topic_callback, this, std::placeholders::_1));

}

void MinimalPublisher::timer_callback() {
  auto message = std_msgs::msg::String();
  message.data = "Hello World" + std::to_string(count_++);
  RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", message.data.c_str());
  publisher_->publish(message);
}

void MinimalPublisher::topic_callback(const std_msgs::msg::String & msg) const {
  RCLCPP_INFO(this->get_logger(), "I heard: '%s'", msg.data.c_str());
} 

void start_ros2_publisher() {

  rclcpp::init(0, nullptr);
  rclcpp::spin(std::make_shared<MinimalPublisher>());
  rclcpp::shutdown();
}
