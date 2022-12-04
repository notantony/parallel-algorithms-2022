#include <iostream>
#include <vector>

int int_cmp(const void *a, const void *b) { return *(int *)a - *(int *)b; }


std::vector<int> generate_ints(int mod = 1000000, int seed = 42){
    std::ios::sync_with_stdio(false);

    std::vector<int> data;
    srand(seed);

    for (uint32_t i = 0; i < 100000000; ++i) {
        data.push_back(random() % mod);
    }

    return data;
}

std::vector<int> read_ints() {
    std::ios::sync_with_stdio(false);

    std::vector<int> data;

    int x;
    while (std::cin >> x) {
        data.push_back(x);
    }

    return data;
}


void dump_vector(std::vector<int> v) {
    for (const auto &elem : v) {
        std::cerr << elem << ' ';
    }
    std::cerr << std::endl;
}