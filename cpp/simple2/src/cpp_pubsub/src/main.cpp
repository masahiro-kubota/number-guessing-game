#include "publish_member_function.hpp"

int main() {
  // subscribeのコールバックにmainの関数を指定する。
  // mainの関数の中でpublishの関数を実行する。
  start_ros2_publisher();
}
