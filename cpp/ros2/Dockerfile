# ベースイメージを指定
FROM osrf/ros:humble-desktop

# 必要なパッケージをインストール
RUN apt-get update && apt-get install -y \
    vim \
    zsh \
    git \
    curl \
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
RUN echo 'export PROMPT="%F{yellow}[ros2-custom]%f %F{green}%n@%m%f:%F{blue}%~%f$ "' >> /root/.zshrc

# zsh をデフォルトで起動
CMD ["zsh"]
