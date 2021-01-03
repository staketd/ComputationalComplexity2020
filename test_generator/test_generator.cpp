
#include "test_generator.hpp"
#include <random>
#include <iostream>

void TestGenerator::PrintTest() {
    std::random_device dev;
    std::mt19937 gen(dev());
    std::uniform_int_distribution<int> vertex_distr(3, 6);
    size_t vertex_count = vertex_distr(gen);
    size_t max_number = 1 << (vertex_count * (vertex_count - 1) / 2);
    std::uniform_int_distribution<size_t> mask_dist(0, max_number);
    size_t edges_mask = mask_dist((gen));
    std::cout << vertex_count << "\n";
    for (size_t i = 0; i < vertex_count; ++i) {
        std::vector<size_t> edges;
        for (size_t j = 0; j < vertex_count; ++j) {
            if (j == i) {
                continue;
            }
            size_t ii = i;
            size_t jj = j;
            if (ii > jj) {
                std::swap(ii, jj);
            }
            size_t index = jj - ii - 1 + ii * vertex_count - ii * (ii + 1) / 2;
            if ((edges_mask >> index) & 1) {
                edges.push_back(j + 1);
            }
        }
        std::cout << edges.size() << ' ';
        for (auto x: edges) {
            std::cout << x << ' ';
        }
        std::cout << '\n';
    }
}
