#pragma once
#include <vector>
#include <Edge.h>
#include <unordered_set>

class EdgeSet {
public:
    void AddEdge(Edge e);

    std::vector<Edge>::const_iterator begin() const;
    std::vector<Edge>::const_iterator end() const;

    bool IsTwoMatching() const;
    bool Contains(const Edge& e) const;

    size_t Size() const;
    void RemoveEdge(const Edge& e);

    const Edge& GetEdge(size_t index) const;
    EdgeSet GetAdjacentEdges(size_t vertex) const;

    void AddAll(const EdgeSet& e);

private:
    std::vector<Edge> edges_;
    std::unordered_set<Edge> edges_hash_set_;
};
