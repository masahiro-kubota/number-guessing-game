# CMakeの最低バージョンを指定
cmake_minimum_required(VERSION 3.10)

# プロジェクト名と使用する言語を指定
project(NumberGuessingGame LANGUAGES CXX)

# C++の標準バージョンをC++17に設定
set(CMAKE_CXX_STANDARD 17)

# C++標準バージョンの指定を必須に設定
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# C++の拡張機能を無効に設定（標準に準拠）
set(CMAKE_CXX_EXTENSIONS OFF)

# コンパイル時のオプションを設定
# -Wall: 一般的な警告をすべて有効化
# -Wextra: 追加の警告も有効化
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

# ソースファイルとヘッダーファイルをリストとして設定
set(SRCS
    src/main.cpp
    src/core/GameState.cpp
    src/io/cliio/CliIo.cpp
    src/logic/GameManager.cpp)

# 実行可能ファイルを生成
# 'main'という名前の実行ファイルを指定されたソースファイルから作成
add_executable(main ${SRCS})

# インクルードパスを設定
target_include_directories(main
    PRIVATE
        src/core
        src/io
        src/logic
)