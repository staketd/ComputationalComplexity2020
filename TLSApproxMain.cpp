#include <tls_approximation/TLSApproximation.h>

int main() {
    auto main_graph = Common::ReadAndInitGraph();
    TLSApproximation<MainEdgeSetGenerator> tls(main_graph);
    auto ans = tls.getSolution();
    std::cout << ans.weight << "\n";
    for (auto v : ans.cycle) {
        std::cout << v << " ";
    }
    std::cout << "\n";
    return 0;
}
