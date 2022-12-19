#pragma once

#include <iostream>
#include <vector>

template <class T>
void dump_vector(std::vector<T> v, std::string name="") {
    if (name.size() > 0) {
        std::cerr << name << '\n';
    }
    for (const auto &elem : v) {
        std::cerr << elem << ' ';
    }
    std::cerr << std::endl;
}

template <class T>
void dump_cubic(std::vector<T> v, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        for (size_t j = 0; j < size; ++j) {
            for (size_t k = 0; k < size; ++k) {
                std::cerr << v[i * size * size + j * size + k] << ' ';
            }
            std::cerr << '\n';
        }
        std::cerr << '\n';
    }
    std::cerr << std::endl;
}