#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

#include "tbb/parallel_invoke.h"


std::pair<size_t, size_t> partition(int *data, size_t len) {
    static thread_local std::mt19937 generator;
    std::uniform_int_distribution<size_t> distribution(0, len - 1);
    size_t rand_idx = distribution(generator);

    std::swap(data[0], data[rand_idx]);

    size_t eq_r = 0 + 1;
    size_t smaller_r = 0 + 1;
    size_t greater_l = len;
    while (smaller_r < greater_l) {
        if (data[smaller_r] == data[0]) {
            std::swap(data[eq_r++], data[smaller_r++]);
        } else if (data[smaller_r] < data[0]) {
            ++smaller_r;
        } else {
            std::swap(data[smaller_r], data[--greater_l]);
        }
    }

    size_t n_smaller = smaller_r - eq_r;
    size_t n_transport = std::min(eq_r, n_smaller);
    for (size_t i = 0; i < n_transport; ++i) {
        std::swap(data[i], data[smaller_r - i - 1]);
    }

    size_t n_eq = eq_r;
    return {n_smaller, n_eq};
}

namespace seq {
void qsort_impl(int *data, size_t len) {
    if (len <= 1) {
        return;
    }

    std::pair<size_t, size_t> p_sizes = partition(data, len);
    
    qsort_impl(data, p_sizes.first);
    qsort_impl(data + p_sizes.first + p_sizes.second, len - (p_sizes.first + p_sizes.second));
}


void qsort(std::vector<int> &v) {
    qsort_impl(v.data(), v.size());
}

}  // namespace seq

namespace par {
    const size_t MIN_SPLIT_THRESHOLD = 200;

void qsort_impl(int *data, size_t len) {
    if (len <= 1) { 
        return;
    }

    std::pair<size_t, size_t> p_sizes = partition(data, len);

    size_t size1 = p_sizes.first;
    size_t size2 = len - (p_sizes.first + p_sizes.second);
    
    if (size1 >= MIN_SPLIT_THRESHOLD && size2 >= MIN_SPLIT_THRESHOLD) {
        oneapi::tbb::parallel_invoke(
            [=] { qsort_impl(data, size1); },
            [=] {
                qsort_impl(data + p_sizes.first + p_sizes.second, size2);
        });
    } else {
        qsort_impl(data, size1);
        qsort_impl(data + p_sizes.first + p_sizes.second, size2);
    }
}

void qsort(std::vector<int> &v) {
    qsort_impl(v.data(), v.size());
}

}  // namespace par