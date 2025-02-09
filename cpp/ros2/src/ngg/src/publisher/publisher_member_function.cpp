// Copyright 2019 Open Source Robotics Foundation, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "publisher_member_function.hpp"

MinimalPublisher::MinimalPublisher() : Node("minimal_publisher"), count_(0)
{
  publisher_ = this->create_publisher<std_msgs::msg::String>("topic", 10);
  publish_input();
}

void MinimalPublisher::publish_input()
{
  for (int i = 0; i < 5; i++) {
    auto message = std_msgs::msg::String();
    RCLCPP_INFO(this->get_logger(), "Input the number:");
    std::cin >> message.data;
    publisher_->publish(message);
  }
}
