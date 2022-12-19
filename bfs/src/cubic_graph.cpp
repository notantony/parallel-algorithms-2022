#include <vector>
#include <cstdint>


namespace CubicGraph {

struct Coord {
    uint32_t x, y, z;

    Coord(uint32_t x, uint32_t y, uint32_t z) : x(x), y(y), z(z) {}

    Coord(uint32_t side, size_t idx) :
        x(idx / side / side),
        y(idx / side - this->x * side),
        z(idx % side) {}

    static inline size_t to_index(uint32_t side, const Coord& coord) {
        return static_cast<size_t>(coord.x) * side * side +
            static_cast<size_t> (coord.y) * side +
            coord.z;
    }
};

std::vector<size_t> _get_neighbours(uint32_t side, Coord coord) {
    std::vector<size_t> nodes;

    uint32_t* dims[3] = {&coord.x, &coord.y, &coord.z};
    for (uint32_t* dim : dims) {
        if (*dim > 0) {
            --(*dim);
            nodes.push_back(Coord::to_index(side, coord));
            ++(*dim);
        }
        if ((*dim) + 1 < side) {
            ++(*dim);
            nodes.push_back(Coord::to_index(side, coord));
            --(*dim);
        }
    }
    return nodes;
}

std::vector<size_t> get_neighbours(uint32_t side, size_t idx) {
    return _get_neighbours(side, Coord(side, idx));
}

size_t get_neighbours_sizes(uint32_t side, size_t idx) {
    Coord coord(side, idx);
    int borders = (coord.x > 0 && coord.x + 1 < side) + (coord.y > 0 && coord.y + 1 < side) + (coord.z > 0 && coord.z + 1 < side);
    return 3 + borders;
}

}  // namespace CubicGraph