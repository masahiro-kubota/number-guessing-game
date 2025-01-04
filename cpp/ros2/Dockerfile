# ベースイメージを指定
FROM osrf/ros:humble-desktop

# パッケージリストを更新し、vim をインストール
RUN apt-get update && apt-get install -y vim

# 作業ディレクトリを設定（必要に応じて変更可能）
WORKDIR /workspace

# シェルをデフォルトのコマンドとして指定
CMD ["/bin/bash"]

