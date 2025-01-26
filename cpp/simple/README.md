```
# core dumpを有効にする
ulimit -c unlimited
# coredumpの出力先をカレントディレクトリにする
sudo sysctl -w kernel.core_pattern=core.%e.%p
```
int main()のクラッシュさせる関数のコメントアウトを外す。

```
# docker
make build
make run
```
```
# install glog, gdb
apt install -y libgoogle-glog-dev gdb

# build C++
mkdir build 
cd build
cmake ..
cmake --build . #make
./main

# analyze coredump
gdb main core.main.<PID>
```




