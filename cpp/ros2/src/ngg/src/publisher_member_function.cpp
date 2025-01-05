#include "publisher_member_function.hpp"

MinimalPublisher::MinimalPublisher()
: Node("minimal_publisher"), count_(0) {
  publisher_ = this->create_publisher<std_msgs::msg::String>("topic", 10);
  publish_input();
}

void MinimalPublisher::publish_input() {
  for (int i = 0; i < 5 ; i++) {
    auto message = std_msgs::msg::String();
    RCLCPP_INFO(this->get_logger(), "Input the number:");
    std::cin >> message.data;
    publisher_ -> publish(message);
  }
}

int main(int argc, char * argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalPublisher>());
  rclcpp::shutdown();
  return 0;
}
