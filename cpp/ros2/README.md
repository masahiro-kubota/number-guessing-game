<details>

<summary>Setting Network Configuration</summary>

- [DDS settings for ROS 2 and Autoware](https://autowarefoundation.github.io/autoware-documentation/main/installation/additional-settings-for-developers/network-configuration/dds-settings/)
- [Enable `multicast` on `lo`](https://autowarefoundation.github.io/autoware-documentation/main/installation/additional-settings-for-developers/network-configuration/enable-multicast-for-lo/)

</details>

### In the root directory create a docker container and work inside it

```
# Test
# テスト結果をリアルタイムでコンソールに出力するオプション
colcon test --event-handlers console_direct+
colcon test-result --verbose
```

```
colcon build --symlink-install
./ros2_tmux.sh
```
