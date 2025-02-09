#!/bin/bash

# セッション名を設定
SESSION="ros2_dev"

# 既存のセッションを終了
tmux kill-session -t $SESSION 2>/dev/null

# 新しいセッションを作成
tmux new-session -d -s $SESSION

# ウィンドウ名を設定
tmux rename-window -t $SESSION:0 'ros2'

# ペインを垂直分割
tmux split-window -v

# 上部ペインでtalkerを実行
tmux send-keys -t $SESSION:0.0 'colcon build --symlink-install' C-m
tmux send-keys -t $SESSION:0.0 '. install/setup.zsh' C-m
tmux send-keys -t $SESSION:0.0 'ros2 run ngg talker' C-m

# 下部ペインでlistenerを実行
tmux send-keys -t $SESSION:0.1 '. install/setup.zsh' C-m
tmux send-keys -t $SESSION:0.1 'ros2 run ngg listener' C-m

# セッションにアタッチ
tmux attach-session -t $SESSION
