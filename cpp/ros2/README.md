```
colcon build --symlink-install
. install/setup.zsh
ros2 run ngg talker
```
```
. install/setup.zsh
ros2 run ngg listener
```
```
# Test
# 詳細なログありtest
colcon test --event-handlers console_direct+
```

ROS2はmsgがinterfaceになっていて、pub/sub間の依存関係が分離されている。




