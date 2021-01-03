#include <tls_approximation/TLSApproximation.h>

int main() {
    Graph graph(5);
    graph.AddEdge({0, 0}, 1);
    std::cout << graph.GetWeight({0, 0});
}
