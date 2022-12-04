#!/usr/bin/bash
set -e

cmake -B./build -DCMAKE_BUILD_TYPE:STRING=Debug
cmake --build ./build --config Debug --target valid

for INPUT_FILE in $(ls ./tests)
do
    INPUT_PATH="./tests/$INPUT_FILE"
    echo "$INPUT_PATH"
    ./build/valid <"$INPUT_PATH" >/dev/null
done