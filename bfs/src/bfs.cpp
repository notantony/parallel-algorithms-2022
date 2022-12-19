#include <algorithm>
#include <atomic>
#include <functional>
#include <queue>
#include <vector>

#include "my_tbb.cpp"
#include "tbb/parallel_for.h"
#include "tbb/parallel_reduce.h"
#include "tbb/parallel_scan.h"


namespace seq {
const size_t STUB_VALUE = std::numeric_limits<size_t>::max();

std::vector<size_t> bfs(
    size_t nodes_total, size_t start_idx,
    std::function<std::vector<size_t>(size_t)> get_neighbours) {
    std::queue<size_t> q;
    std::vector<size_t> distances(nodes_total, STUB_VALUE);

    distances[start_idx] = 0;
    q.push(start_idx);

    while (q.size() > 0) {
        size_t cur = q.front();
        q.pop();
        for (size_t other : get_neighbours(cur)) {
            if (distances[other] == STUB_VALUE) {
                distances[other] = distances[cur] + 1;
                q.push(other);
            }
        }
    }
    return distances;
}

}  // namespace seq


namespace par {
const size_t STUB_VALUE = std::numeric_limits<size_t>::max();

std::vector<size_t> bfs(
    size_t nodes_total, size_t start_idx,
    std::function<std::vector<size_t>(size_t)> get_neighbours,
    std::function<size_t(size_t)> get_neighbours_sizes) {
    std::vector<size_t> frontier = {start_idx};
    std::vector<std::atomic_uint8_t> flags(nodes_total);
    std::atomic_uint8_t *flags_ptr = flags.data();
    std::vector<size_t> distances(nodes_total, STUB_VALUE);
    flags[start_idx] = true;
    distances[start_idx] = 0;

    size_t *distances_ptr = distances.data();

    size_t cur_dist = 0;
    while (frontier.size() > 0) {
        ++cur_dist;

        size_t *frontier_ptr = frontier.data();

        std::vector<size_t> positions = my_tbb::parallel_map<size_t, size_t>(frontier,
            [=, &get_neighbours](size_t i) {
                return get_neighbours_sizes(i); 
            });
        my_tbb::apply_sum_scan(positions, false);

        size_t *positions_ptr = positions.data();

        std::vector<size_t> next_frontier(
            positions.back() + get_neighbours(frontier.back()).size(),
            STUB_VALUE);
        size_t *next_frontier_ptr = next_frontier.data();

        tbb::parallel_for(
            tbb::blocked_range<size_t>(0, frontier.size(), my_tbb::DEFAULT_GRAIN_SIZE),
            [=, &get_neighbours](const tbb::blocked_range<size_t> &r) {
                for (size_t i = r.begin(); i != r.end(); ++i) {
                    size_t cur = frontier_ptr[i];
                    std::vector<size_t> neighbours = get_neighbours(cur);
                    // TODO: pfor?
                    for (size_t j = 0; j < neighbours.size(); ++j) {
                        size_t other = neighbours[j];
                        uint8_t expected = false;
                        if (flags_ptr[other].compare_exchange_strong(expected,
                                                                     true)) {
                            next_frontier_ptr[positions_ptr[i] + j] = other;
                            distances_ptr[other] = cur_dist;
                        }
                    }
                }
            });

        frontier = my_tbb::parallel_filter<size_t>(
            next_frontier,
            [](size_t val) -> uint8_t { return (val ^ STUB_VALUE); });
    }

    return distances;
}

}  // namespace par