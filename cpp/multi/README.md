```
make build
make run
colcon build --symlink-install
. install/setup.zsh
./build/ngg/main
```
```
make exec
. install/setup.zsh
ros2 topic pub /topic_input std_msgs/msg/String "{data: 43}" --once
```



