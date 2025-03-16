# samd21g-midi-tool-software
[![linux](https://github.com/newdigate/samd21g-midi-tool-software/actions/workflows/linux.yml/badge.svg)](https://github.com/newdigate/samd21g-midi-tool-software/actions/workflows/linux.yml)
[![teensy](https://github.com/newdigate/samd21g-midi-tool-software/actions/workflows/teensy.yml/badge.svg)](https://github.com/newdigate/samd21g-midi-tool-software/actions/workflows/teensy.yml)

```shell
$ git clone https://github.com/newdigate/samd21g-midi-tool-software.git
$ cd samd21g-midi-tool-software
```
* build for teensy
```shell
$ mkdir cmake-build-teensy
$ cd cmake-build-teensy
$ cmake .. -DCMAKE_BUILD_TYPE=Debug -DCMAKE_TOOLCHAIN_FILE=../cmake/toolchains/teensy41.cmake
$ cmake --build .
```

* build for macos / linux
```shell
$ mkdir cmake-build-debug
$ cd cmake-build-debug
$ cmake .. -DCMAKE_BUILD_TYPE=Debug
$ cmake --build .
$ ./MyExample
```