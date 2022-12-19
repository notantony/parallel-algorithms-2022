#pragma once

#include <functional>
#include <vector>

#include "tbb/parallel_for.h"
#include "tbb/parallel_scan.h"

namespace my_tbb {
// size_t DEFAULT_GRAIN_SIZE = std::numeric_limits<size_t>::max();
// size_t DEFAULT_GRAIN_SIZE = 5000;
size_t DEFAULT_GRAIN_SIZE = 1;

template <class I, class O>
std::vector<O> parallel_map(const std::vector<I> &input,
                            std::function<O(I)> fun) {
    const I *input_ptr = input.data();
    std::vector<O> output(input.size());
    O *output_ptr = output.data();

    tbb::parallel_for(
        tbb::blocked_range<size_t>(0, input.size(), DEFAULT_GRAIN_SIZE),
        [=](const tbb::blocked_range<size_t> &r) {
            for (size_t i = r.begin(); i != r.end(); ++i) {
                output_ptr[i] = fun(input_ptr[i]);
            }
        }
        );

    return output;
}

template <class T>
void apply_sum_scan(std::vector<T> &v, bool add_first = true) {
    T* data = v.data();
    tbb::parallel_scan(
        tbb::blocked_range<size_t>(0, v.size(), DEFAULT_GRAIN_SIZE), 
        0,
        [=] (const tbb::blocked_range<size_t>& r, T sum, bool is_final_scan) {
            T tmp = sum;

            if (add_first) {
                for (size_t i = r.begin(); i != r.end(); ++i) {
                    tmp += data[i];
                    if (is_final_scan) {
                        data[i] = tmp;
                    }
                }
            } else {
                for (size_t i = r.begin(); i != r.end(); ++i) {
                    tmp += data[i];
                    if (is_final_scan) {
                        data[i] = tmp - data[i];
                    }
                }
            }
            return tmp;
        },
        [] (T l, T r) {
            return l + r;
        }
    );
}

template <class T>
std::vector<T> parallel_filter(const std::vector<T> &input, std::function<uint8_t(T)> pred) {
    const T *input_ptr = input.data();
    if (input.size() == 0) {
        return input;
    }

    std::vector<size_t> flags = parallel_map<T, size_t>(input,
        [&pred] (T item) -> size_t {
            return pred(item) ? 1 : 0;
        }
    );
    apply_sum_scan(flags, true);
    size_t *flags_ptr = flags.data();
    
    std::vector<T> output(flags.back());
    T* output_ptr = output.data();

    if (flags[0] == 1) {
        output[0] = input[0];
    }

    tbb::parallel_for(
        tbb::blocked_range<size_t>(1, input.size(), DEFAULT_GRAIN_SIZE),
        [=](const tbb::blocked_range<size_t> &r) {
            for (size_t i = r.begin(); i != r.end(); ++i) {
                if (flags_ptr[i] != flags_ptr[i - 1]) {
                    output_ptr[flags_ptr[i - 1]] = input_ptr[i];
                }
            }
        });
    return output;
}

}  // namespace my_tbb