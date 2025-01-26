```
make build
make run
colcon build --symlink-install
. install/setup.zsh
./build/ngg/main <io_type> # cli, ros
```
```
# ros
make exec
. install/setup.zsh
ros2 topic pub /topic_input std_msgs/msg/String "{data: 43}" --once
```

ゲームロジックのコードを変えずに任意のIO実装でき、実行ファイルの引数でそのIOを変更できる。
C#ではロジックからの任意のタイミングで出力ができなかったが、IIoHandler::output_data(std::string data)をoverrideすることで出力できる。

ROS 2のテンプレートはint main()にinitやspinを書いているが、rclcpp::init()をするまでrclcpp::Node()が使えないので、IOの起動用の関数でinitやspinを実行する。
IOから呼び出すロジック側の関数のコールバック登録は、最初のDIで実行したいのでrclcpp::Nodeを継承するクラス（RosIoCore）とコールバックの登録などをするクラス(RosIo)は分けられていて、後からRosIoからRosIoCoreが起動される