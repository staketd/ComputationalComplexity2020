#pragma once
#include <unordered_map>
#include <vector>
#include <Edge.h>
#include <edge_set/edge_set.h>

using Weight = long long;

class Graph {
public:
    explicit Graph(size_t size);

    Weight GetWeight(Edge e);
    void AddEdge(Edge e, Weight weight);

    EdgeSet& GetAdjacentEdges(size_t vertex);

private:
    std::unordered_map<Edge, Weight> edges_weights_;
    std::vector<EdgeSet> adjacent_edges_;
};

