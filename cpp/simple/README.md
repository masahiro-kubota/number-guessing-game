```
# docker
make build
make run
```
```
# build C++
mkdir build 
cd build
cmake ..
cmake --build . #make
./main
```

macだとCMakeLists.txtを使うときにg++がうまく見つけられない。Makeだと問題ない。docker使えばCmakeもOK。
