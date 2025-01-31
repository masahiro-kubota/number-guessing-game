
### In the root directory create a docker container and work inside it.
```
# Test
# 詳細なログありtest
colcon test --event-handlers console_direct+
```
```
# terminal 1
colcon build --symlink-install
. install/setup.zsh
ros2 run ngg talker
```
```
# terminal 2
# In the root directory
make exec # work inside the container
cd cpp/ros2
. install/setup.zsh
ros2 run ngg listener
```







