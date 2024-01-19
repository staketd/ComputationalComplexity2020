#pragma once
#include <unordered_map>
#include <vector>
#include <Edge.h>
#include <edge_set/edge_set.h>

using Weight = long long;

class Graph {
public:
    explicit Graph(size_t size);

    Weight GetWeight(Edge e) const;
    void AddEdge(const Edge& e, Weight weight);

    const EdgeSet& GetAdjacentEdges(size_t vertex) const;
    size_t Size() const;

    std::vector<std::vector<size_t>> GetComponents() const;
    std::vector<size_t> GetComponent(size_t vertex) const;

private:
    void ComponentDfs(size_t v, std::vector<int>& used, std::vector<size_t>& components) const;
private:
    size_t size_;
    std::unordered_map<Edge, Weight> edges_weights_;
    std::vector<EdgeSet> adjacent_edges_;
};

