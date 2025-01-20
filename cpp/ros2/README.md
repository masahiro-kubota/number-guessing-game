```
make build
make run
colcon build --symlink-install
. install/setup.zsh
ros2 run ngg  

# Test
colcon test
```

ROS2はmsgがinterfaceになっていて、pub/sub間の依存関係が分離されている。




