# ベースイメージを指定
FROM osrf/ros:humble-desktop

# 必要なパッケージをインストール
RUN apt-get update && apt-get install -y \
    vim \
    zsh \
    git \
    curl \
    tmux \
    && apt-get clean

# zsh をデフォルトシェルに設定
RUN chsh -s /usr/bin/zsh

# 作業ディレクトリを設定
WORKDIR /root

# dotfiles リポジトリをクローン
RUN git clone https://github.com/masahiro-kubota/dotfiles.git

# dotfiles ディレクトリに移動して install.sh を実行
RUN cd dotfiles && chmod +x install.sh && ./install.sh

# 作業ディレクトリを /workspace に設定
WORKDIR /workspace

# Zsh プロンプトをカスタマイズ
RUN echo 'export PROMPT="%F{yellow}[ros2-custom]%f %F{green}%n%f:%F{blue}%~%f$ "' >> /root/.zshrc

# 環境変数を設定 .zshrcに色々書いてるのでENVではなく.zshrcに書き込み
RUN echo 'export CC=/usr/bin/gcc' >> /root/.zshrc
RUN echo 'export CXX=/usr/bin/g++' >> /root/.zshrc

# zsh をデフォルトで起動
CMD ["zsh"]
