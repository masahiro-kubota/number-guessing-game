# ターゲットの名前（ビルド後に生成される実行ファイル名）
TARGET = main

# ソースファイルのリスト（複数ファイルの場合はスペースで区切る）
SRCS = src/main.cpp

# 使用するC++コンパイラ（必要に応じて変更可能）
CXX = g++

# コンパイラのフラグ
# -Wall: 全ての警告を表示
# -Wextra: 追加の警告を表示
# -std=c++17: C++17規格に準拠
CXXFLAGS = -Wall -Wextra -std=c++17

# サンプル用のテキスト（このMakefileでは使われていないが、他のルールで利用可能）
TEXT = "this is a sample"

# デフォルトのターゲット（Makeを実行したときに最初に実行される）
all: $(TARGET)
	@echo "Running $(TARGET)..."
	@./$(TARGET)

# 実行ファイルのビルドルール
# $^: 依存するすべてのファイル（ここではsrc/main.cpp）
# $@: ターゲットの名前（ここではmain）
$(TARGET): $(SRCS)
	@$(CXX) $(CXXFLAGS) $^ -o $@

# クリーンアップ用ルール
# ビルドで生成されたファイルを削除
clean:
	@rm -f $(TARGET)
