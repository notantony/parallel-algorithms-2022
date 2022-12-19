#include <cstdlib>
#include <functional>
#include <iostream>
#include <vector>

#include "tbb/blocked_range.h"
#include "tbb/parallel_reduce.h"
#include "tbb/global_control.h"

#include "bfs.cpp"
#include "cubic_graph.cpp"
#include "utils.h"


int main(int argc, char **argv) {
    tbb::global_control(tbb::global_control::max_allowed_parallelism, 4);
    
    if (argc != 2) {
        std::cout << "Usage: benchmark <size>" << std::endl;
        return 1;
    }
    int size = atoi(argv[1]);
    size_t nodes_total = static_cast<uint64_t> (size) * size * size;

    const auto get_neighbours = std::bind(CubicGraph::get_neighbours, size, std::placeholders::_1);
    const auto get_sizes = std::bind(CubicGraph::get_neighbours_sizes, size, std::placeholders::_1);

    auto start = std::chrono::high_resolution_clock::now();

#ifdef ALGO_SEQ
    std::vector<size_t> results = seq::bfs(nodes_total, 0, get_neighbours);
#endif

#ifdef ALGO_PAR
    std::vector<size_t> results = par::bfs(nodes_total, 0, get_neighbours, get_sizes);
#endif

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;
    std::cout << diff.count();

    return 0;
}
