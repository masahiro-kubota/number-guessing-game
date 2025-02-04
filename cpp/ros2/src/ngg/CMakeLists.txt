# 必要なCMakeの最低バージョンを指定
cmake_minimum_required(VERSION 3.8)

# プロジェクト名を指定
project(ngg)

# C++の標準バージョンを設定（設定されていない場合はC++14をデフォルトにする）
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

# コンパイラがGCCまたはClangの場合、追加のコンパイルオプションを設定
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# ROS2のamentビルドシステムのCMakeモジュールを探す
find_package(ament_cmake REQUIRED)
# rclcpp（ROS2のC++クライアントライブラリ）を探す
find_package(rclcpp REQUIRED)
# std_msgs（標準メッセージ型）を探す
find_package(std_msgs REQUIRED)
# diagnostic_updaterパッケージを追加
find_package(diagnostic_updater REQUIRED)

# 実行ファイルを定義して、そのソースファイルを指定
add_executable(talker
    src/publisher/publisher_member_function.cpp
    src/publisher/main.cpp)

add_executable(listener
    src/subscriber/subscriber_member_function.cpp
    src/subscriber/main.cpp)

# talkerとlistenerに必要な依存ライブラリをリンク
ament_target_dependencies(talker rclcpp std_msgs)
ament_target_dependencies(listener rclcpp std_msgs diagnostic_updater)

# 実行可能ファイルのインストール先を指定
install(TARGETS
  talker
  listener
  DESTINATION lib/${PROJECT_NAME})

# ビルド時にテストを有効にするオプションが設定されている場合の処理
if(BUILD_TESTING)
  find_package(ament_cmake_gtest REQUIRED)

  # テストの追加 (src/subscriber_member_function.cpp を一時的に除外)
  ament_add_gtest(test_game_logic test/test_game_logic.cpp src/subscriber/subscriber_member_function.cpp)
  if(TARGET test_game_logic)
    # テスト対象のインクルードディレクトリを追加
    target_include_directories(test_game_logic PRIVATE src)
    # テストで使うライブラリをリンク
    ament_target_dependencies(test_game_logic rclcpp std_msgs diagnostic_updater)
    # GTEST_MAIN を有効にする
    target_compile_definitions(test_game_logic PRIVATE GTEST_MAIN)
  endif()
endif()

# Linter のセットアップ
find_package(ament_lint_auto REQUIRED)
# 以下の行のコメントを外すと、特定の Linter をスキップできる
# set(ament_cmake_copyright_FOUND TRUE)  # 著作権チェックをスキップ
# set(ament_cmake_cpplint_FOUND TRUE)    # cpplint チェックをスキップ
ament_lint_auto_find_test_dependencies()

# amentパッケージとしての設定を適用
ament_package()
