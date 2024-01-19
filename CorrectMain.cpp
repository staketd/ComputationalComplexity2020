#include <correct/slow_correct_algorithm.hpp>
#include <Common.h>
#include <iostream>

int main() {
    Graph main_graph = Common::ReadAndInitGraph();
    SlowCorrectAlgorithm algo(main_graph);
    auto result = algo.GetSolution();
    std::cout << result.weight << "\n";
    for (const auto& x: result.cycle) {
        std::cout << x << " ";
    }
    std::cout << '\n';
    return 0;
}
