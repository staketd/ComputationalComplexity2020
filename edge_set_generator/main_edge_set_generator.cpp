
#include "main_edge_set_generator.h"
#include <unordered_set>

std::optional<PathSet> MainEdgeSetGenerator::Find(
        size_t v,
        const EdgeSet& A,
        EdgeSet& C,
        const Graph& graph,
        std::vector<size_t>& chosen_degree) {
    if (C.Size() > 21) {
        return {};
    }
    if (Common::IsImprovement(A, C, graph.Size())) {
        return PathSet(Common::SymmetricalDifference(A, C), graph.Size());
    }
    if (v >= graph.Size()) {
        return {};
    }
    // can choose no more than 4 edges adjacent to each vertex
    // choosing 0
    auto result = Find(v + 1, A, C, graph, chosen_degree);

    if (result.has_value()) {
        return result;
    }
    EdgeSet adjacentEdges = graph.GetAdjacentEdges(v);
    // choosing one

    for (const Edge& e : adjacentEdges) {
        if (C.Contains(e)) {
            continue;
        }
//        if (chosen_degree[e.from] == 4 || chosen_degree[e.to] == 4) {
//            continue;
//        }
        C.AddEdge(e);
        chosen_degree[e.from]++;
        chosen_degree[e.to]++;
        auto res = Find(v + 1, A, C, graph, chosen_degree);
        if (res.has_value()) {
            return res;
        }
        chosen_degree[e.from]--;
        chosen_degree[e.to]--;
        C.RemoveEdge(e);
    }

    // choosing two

    auto res = AddTwo(v, A, C, graph, chosen_degree);
    if (res.has_value()) {
        return res;
    }

    // Choosing 3 or 4 edges can be optimized
    // we can choose 3 only if vertex v has at least one adjacent edge in A and we need to add one of these edges to C
    // we can choose 4 only if vertex v has two adjacent edges in A

    // choosing 3

    EdgeSet adjacent_edges_in_A = A.GetAdjacentEdges(v);

    if (adjacent_edges_in_A.Size() < 1) {
        return {};
    }


    for (const auto& e1 : adjacent_edges_in_A) {
        if (C.Contains(e1)) {
            continue;
        }
        C.AddEdge(e1);
        // choosing two more

        res = AddTwo(v, A, C, graph, chosen_degree);
        if (res.has_value()) {
            return res;
        }

        C.RemoveEdge(e1);
    }

    if (adjacent_edges_in_A.Size() < 2) {
        return {};
    }

    if (adjacent_edges_in_A.Size() != 2) {
        throw std::runtime_error("A should be 2-matching!");
    }

    C.AddAll(adjacent_edges_in_A);

    res = AddTwo(v, A, C, graph, chosen_degree);

    for (const auto& edge : adjacent_edges_in_A) {
        C.RemoveEdge(edge);
    }


    return res;
}

std::optional<PathSet> MainEdgeSetGenerator::AddTwo(size_t vertex, const EdgeSet& A, EdgeSet& C, const Graph& graph,
                                                    std::vector<size_t>& chosen_degree) {
    const auto& adjacentEdges = graph.GetAdjacentEdges(vertex);
    for (size_t i = 0; i < adjacentEdges.Size(); ++i) {
        Edge e1 = adjacentEdges.GetEdge(i);
        if (C.Contains(e1)) {
            continue;
        }
        C.AddEdge(e1);
        for (size_t j = i + 1; j < adjacentEdges.Size(); ++j) {
            Edge e2 = adjacentEdges.GetEdge(j);
            if (C.Contains(e2)) {
                continue;
            }
            C.AddEdge(e2);
            auto res = Find(vertex + 1, A, C, graph, chosen_degree);
            if (res.has_value()) {
                return res;
            }
            C.RemoveEdge(e2);
        }
        C.RemoveEdge(e1);
    }
    return {};
}

std::optional<PathSet> MainEdgeSetGenerator::FindImprovement(const EdgeSet& now, const Graph& graph) {
    EdgeSet C;
    std::vector<size_t> chosen_degree(graph.Size());
    return Find(0, now, C, graph, chosen_degree);
}
