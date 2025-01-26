cmake_minimum_required(VERSION 3.8)
project(ngg)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)

# ソースファイルとヘッダーファイルをリストとして設定
set(SRCS
    src/main.cpp
    src/core/GameState.cpp
    src/io/IoFactory.cpp
    src/io/cliio/CliIo.cpp
    src/io/rosio/RosIo.cpp
    src/logic/GameManager.cpp)

# 実行可能ファイルを生成
# 'main'という名前の実行ファイルを指定されたソースファイルから作成
add_executable(main ${SRCS})
ament_target_dependencies(main rclcpp std_msgs)

install(TARGETS
  main
  DESTINATION lib/${PROJECT_NAME})

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

# インクルードパスを設定
target_include_directories(main
    PRIVATE
        src/core
        src/io
        src/logic
)

ament_package()
