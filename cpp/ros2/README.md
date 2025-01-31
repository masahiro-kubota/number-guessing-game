
### In the root directory create a docker container and work inside it.
```
# Test
# 詳細なログありtest
colcon test --event-handlers console_direct+
```
```
colcon build --symlink-install
. install/setup.zsh
ros2 run ngg talker
```
```
# terminal 1
. install/setup.zsh
ros2 run ngg listener
```
```
# terminal 2
make exec # work inside the container
. install/setup.zsh
ros2 run ngg listener
```






