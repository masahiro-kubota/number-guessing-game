```
make build
make run
rosdep install -i -y --from-paths src --rosdistro $ROS_DISTRO
colcon build --symlink-install --package-select ngg
. install/setup.zsh
ros2 run ngg talker 
```

# Test
colcon test
