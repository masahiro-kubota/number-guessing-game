```
make build
make run
rosdep install -i -y --from-paths src --rosdistro $ROS_DISTRO
colcon build --symlink-install --packages-select ngg
. install/setup.zsh
ros2 run ngg talker 
```
