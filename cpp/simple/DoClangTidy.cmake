cmake_minimum_required(VERSION 3.10)

# clang-tidy を有効化するかどうかを指定
# デフォルトで ON に設定
option(CLANG_TIDY_ENABLE
  "If the command clang-tidy is available, tidy source files.\
Turn this off if the build time is too slow."
  ON)

# clang-tidy の実行ファイルを探す
find_program(CLANG_TIDY_EXE clang-tidy)

# clang-tidy をターゲットに適用するための関数を定義
function(clang_tidy target)
  if(CLANG_TIDY_EXE)
    if(CLANG_TIDY_ENABLE)
      # clang-tidy を有効にしたことをメッセージとして出力
      message(STATUS "Enable Clang-Tidy ${target}")

      # 指定したターゲットのプロパティとして clang-tidy を適用
      # - C_CLANG_TIDY: C 言語のソースコードに clang-tidy を適用
      # - CXX_CLANG_TIDY: C++ 言語のソースコードに clang-tidy を適用
      # -fix と -fix-errors オプションを指定し、コードの修正を自動適用
      set_target_properties(${target} PROPERTIES
        CXX_CLANG_TIDY "${CLANG_TIDY_EXE};-fix;-fix-errors;--header-filter=.*")
    endif()
  endif()
endfunction()

