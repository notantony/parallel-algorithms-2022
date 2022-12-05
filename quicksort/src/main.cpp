#include <cstdlib>
#include <functional>
#include <iostream>
#include <vector>

#include "tbb/blocked_range.h"
#include "tbb/parallel_reduce.h"
#include "tbb/global_control.h"

#include "qsort.cpp"
#include "utils.h"


int main(int argc, char **argv) {
    tbb::global_control(tbb::global_control::max_allowed_parallelism, 4);
    if (argc != 3) {
        std::cout << "Usage: benchmark <values_cap> <seed>" << std::endl;
        return 1;
    }
    int mod = atoi(argv[1]);
    int seed = atoi(argv[2]);
    std::vector<int> data = generate_ints(mod, seed);

#ifdef IO_BENCH
    // do nothing
#else
    #ifdef ALGO_STD
        std::qsort(data.data(), data.size(), sizeof(int), int_cmp);
    #endif

    #ifdef ALGO_SEQ
        seq::qsort(data);
    #endif

    #ifdef ALGO_PAR
        par::qsort(data);
    #endif
#endif
    return 0;
}
