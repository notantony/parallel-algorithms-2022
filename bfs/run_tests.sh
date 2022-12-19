#!/usr/bin/bash
set -e

cmake -B./build -DCMAKE_BUILD_TYPE:STRING=Debug
cmake --build ./build --config Debug --target valid

./build/valid
