#!/usr/bin/bash
set -e

cmake -B./build -DCMAKE_BUILD_TYPE:STRING=Release
cmake --build ./build --config Release --target all


for ALGO in "io_bench" "par" "seq" "std"
do
    echo "Running $ALGO"

    TARGET_FILE="./results/$ALGO.csv"
    echo "Results will be written to $TARGET_FILE"
    rm "$TARGET_FILE" || true

    for VALUES_CAP in "100" "10000" "1000000" "100000000"
    do
        echo "Values in [0, $VALUES_CAP]"
        IO_DATA=()
        for i in $(seq 1 5)
        do
            echo "Iteration #$i"
            IO_MS_BEFORE=$(echo $(($(date +%s%N)/1000000)))
            ./build/$ALGO "$VALUES_CAP" "$VALUES_CAP"
            IO_MS_AFTER=$(echo $(($(date +%s%N)/1000000)))
            IO_MS=$(expr $IO_MS_AFTER - $IO_MS_BEFORE)
            echo "$IO_MS"
            IO_DATA+=("$IO_MS")
        done

        echo "data_$VALUES_CAP ${IO_DATA[@]}">>"$TARGET_FILE"
    done
done

python ./scripts/process_results.py
