#include <Common.h>
#include <AlgorithmAnswer.h>

AlgorithmAnswer ReadAnswer(size_t graph_size) {
    long long weight;
    std::cin >> weight;
    Path path;
    for (size_t i = 0; i < graph_size + 1; ++i) {
        size_t vert;
        std::cin >> vert;
        path.AddToPath(vert);
    }
    return {path, weight};
}

bool CheckCorrectWeight(const AlgorithmAnswer& answer, const Graph& graph) {
    std::vector<size_t> visit_times(graph.Size(), 0);
    long long path_weight = 0;
    for (size_t i = 0; i < graph.Size(); ++i) {
        if (++visit_times[answer.cycle.GetVertex(i)] == 2) {
            return false;
        }
        path_weight += graph.GetWeight({answer.cycle.GetVertex(i), answer.cycle.GetVertex(i + 1)});
    }
    return path_weight == answer.weight;
}

int main() {
    Graph graph = Common::ReadAndInitGraph();
    AlgorithmAnswer correct = ReadAnswer(graph.Size());
    AlgorithmAnswer tsp = ReadAnswer(graph.Size());
    if (!CheckCorrectWeight(correct, graph)) {
        std::cout << "DP algo is WRONG\n";
        return 1;
    }
    if (!CheckCorrectWeight(tsp, graph)) {
        std::cout << "TSP algo is WRONG\n";
        return 1;
    }
    return tsp.weight * 7 <= correct.weight * 8 ? 0 : 1;
}
