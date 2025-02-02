# Clang-Format を使用してビルド前にソースコードを自動整形するオプション
option(FORMAT_FILES_WITH_CLANG_FORMAT_BEFORE_EACH_BUILD
  "If the command clang-format is available, format source files before each build.\
Turn this off if the build time is too slow."
  ON)

# clang-format の実行ファイルを検索
find_program(CLANG_FORMAT_EXE clang-format)

# 指定されたターゲットのソースコードを clang-format で整形する関数
function(clang_format target)
  # clang-format が見つかった場合にのみ処理を実行
  if(CLANG_FORMAT_EXE)
    message(STATUS "Enable Clang-Format ${target}")

    # ターゲットのソースファイルリストを取得
    get_target_property(MY_SOURCES ${target} SOURCES)

    # clang-format を実行するカスタムターゲットを作成
    add_custom_target(
      "${target}_format-with-clang-format"
      COMMAND "${CLANG_FORMAT_EXE}" -i -style=file ${MY_SOURCES} # 取得したソースファイルを in-place で整形
      WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} # CMake のソースディレクトリを作業ディレクトリとして設定
    )

    # ユーザが `FORMAT_FILES_WITH_CLANG_FORMAT_BEFORE_EACH_BUILD` を ON にしている場合、
    # ビルドの依存関係として clang-format を追加し、ビルド前にフォーマットを実行
    if(FORMAT_FILES_WITH_CLANG_FORMAT_BEFORE_EACH_BUILD)
      add_dependencies(${target} "${target}_format-with-clang-format")
    endif()
  endif()
endfunction()

