#include <algorithm>
#include <cassert>
#include <functional>
#include <vector>

#include "bfs.cpp"
#include "cubic_graph.cpp"
#include "my_tbb.cpp"
#include "utils.h"


int main(int argc, char **argv) {
    int size = 100;
    size_t nodes_total = static_cast<uint64_t> (size) * size * size;

    std::vector<uint32_t> v = {1, 2, 4, 5, 6, 8, 4, 2, 2, 1};
    dump_vector(my_tbb::parallel_filter<uint32_t>(v, [](uint32_t x) {return static_cast<uint8_t>(x > 2);}));

    v = {1, 2, 4, 5, 6, 8, 4, 2, 2, 1};
    my_tbb::apply_sum_scan(v, false);
    dump_vector(v);
    
    v = {1, 2, 4, 5, 6, 8, 4, 2, 2, 1};
    my_tbb::apply_sum_scan(v, true);
    dump_vector(v);

    const auto get_neighbours = std::bind(CubicGraph::get_neighbours, size, std::placeholders::_1);
    const auto get_sizes = std::bind(CubicGraph::get_neighbours_sizes, size, std::placeholders::_1);

    std::vector<size_t> seq_distances = seq::bfs(nodes_total, 0, get_neighbours);
    std::vector<size_t> par_distances = par::bfs(nodes_total, 0, get_neighbours, get_sizes);

    // dump_cubic(seq_distances, size);
    // dump_cubic(par_distances, size);
    // dump_vector(par_distances);

    assert(par_distances == seq_distances);
    // TODO: some actual tests?

    return 0;
}