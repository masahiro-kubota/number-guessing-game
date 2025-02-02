# CMakeの最低バージョンを指定
cmake_minimum_required(VERSION 3.10)

# プロジェクト名と使用する言語を指定
project(NumberGuessingGame LANGUAGES CXX)

include("${CMAKE_SOURCE_DIR}/DoClangTidy.cmake")

# C++の標準バージョンをC++17に設定
set(CMAKE_CXX_STANDARD 17)

# C++の拡張機能を無効に設定（標準に準拠）
set(CMAKE_CXX_EXTENSIONS OFF)

# デフォルトのビルドタイプをDebugにして、-g -O0などのデバッグ用のフラグが自動的に有効になる
set(CMAKE_BUILD_TYPE Debug)

# アドレスサニタイザーを有効化。メモリ関連の問題を実行時に検出する
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g3 -ggdb")

# コンパイル時のオプションを設定
# -Wall: 一般的な警告をすべて有効化
# -Wextra: 追加の警告も有効化
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")


# For glog
find_package(glog REQUIRED)

# ソースファイルとヘッダーファイルをリストとして設定
set(SRCS
    src/main.cpp
    src/core/GameState.cpp
    src/io/cliio/CliIo.cpp
    src/logic/GameManager.cpp)

set(TARGET main)

# 実行可能ファイルを生成
# 'main'という名前の実行ファイルを指定されたソースファイルから作成
add_executable(${TARGET} ${SRCS})

# For cland-tidy
clang_tidy(${TARGET})
set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # For manual clang-tidy

# インクルードパスを設定
target_include_directories(${TARGET}
    PRIVATE
        src/core
        src/io
        src/logic
)

target_link_libraries(${TARGET} PRIVATE glog::glog)
