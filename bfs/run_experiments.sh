#!/usr/bin/bash
set -e

cmake -B./build -DCMAKE_BUILD_TYPE:STRING=Release
cmake --build ./build --config Release --target all


for ALGO in "par" "seq" 
do
    echo "Running $ALGO"

    TARGET_FILE="./results/$ALGO.csv"
    rm "$TARGET_FILE" || true
    echo "Results will be written to $TARGET_FILE"

    IO_DATA=()
    for i in $(seq 1 5)
    do
        echo "Iteration #$i"
        TIME=$(./build/$ALGO 500)
        echo "$TIME"
        IO_DATA+=("$TIME")
    done
    
    echo "${IO_DATA[@]}">>"$TARGET_FILE"

done

python ./scripts/process_results.py
