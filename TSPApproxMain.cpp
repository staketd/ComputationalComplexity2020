#include <tsp_approximation/TSPApproximation.h>

int main() {
    auto main_graph = Common::ReadAndInitGraph();
    TSPApproximation<MainEdgeSetGenerator> tsp(main_graph);
    auto ans = tsp.getSolution();
    std::cout << ans.weight << "\n";
    for (auto v : ans.cycle) {
        std::cout << v << " ";
    }
    std::cout << "\n";
    return 0;
}
