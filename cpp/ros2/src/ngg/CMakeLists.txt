cmake_minimum_required(VERSION 3.8)
project(ngg)

if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)

add_executable(talker src/publisher_member_function.cpp)
add_executable(listener src/subscriber_member_function.cpp)
ament_target_dependencies(talker rclcpp std_msgs)
ament_target_dependencies(listener rclcpp std_msgs)

install(TARGETS
  talker
  listener
  DESTINATION lib/${PROJECT_NAME})

if(BUILD_TESTING)
  find_package(ament_cmake_gtest REQUIRED)

  # テストの追加 (src/subscriber_member_function.cpp を一時的に除外)
  ament_add_gtest(test_game_logic test/test_game_logic.cpp src/subscriber_member_function.cpp)
  if(TARGET test_game_logic)
    target_include_directories(test_game_logic PRIVATE src)
    ament_target_dependencies(test_game_logic rclcpp std_msgs)

    # GTEST_MAIN を有効にする
    target_compile_definitions(test_game_logic PRIVATE GTEST_MAIN)
  endif()
endif()

ament_package()
