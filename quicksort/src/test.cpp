#include <algorithm>
#include <cassert>
#include <vector>

#include "qsort.cpp"
#include "utils.h"


int main(int argc, char **argv) {
    std::vector<int> data = read_ints();

    std::vector<int> par_copy(data);
    std::vector<int> seq_copy(data);

    std::sort(data.begin(), data.end());
    par::qsort(par_copy);
    seq::qsort(seq_copy);

    // dump_vector(seq_copy);
    // dump_vector(par_copy);

    assert(data == par_copy);
    assert(data == seq_copy);

    return 0;
}