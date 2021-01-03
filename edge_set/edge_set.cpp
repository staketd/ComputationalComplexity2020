#include "edge_set.h"
#include <unordered_map>

void EdgeSet::AddEdge(Edge e) {
    if (!edges_hash_set_.contains(e)) {
        edges_.push_back(e);
        edges_hash_set_.insert(e);
    }
}

std::vector<Edge>::const_iterator EdgeSet::begin() const {
    return edges_.cbegin();
}

std::vector<Edge>::const_iterator EdgeSet::end() const {
    return edges_.cend();
}

bool EdgeSet::IsTwoMatching() const {
    std::unordered_map<size_t, size_t> vertex_degree;
    for (auto edge: edges_) {
        if (!vertex_degree.contains(edge.from)) {
            vertex_degree[edge.from] = 0;
        }
        if (!vertex_degree.contains(edge.to)) {
            vertex_degree[edge.to] = 0;
        }
        vertex_degree[edge.from]++;
        vertex_degree[edge.to]++;
        if (vertex_degree[edge.from] > 2 || vertex_degree[edge.to] > 2) {
            return false;
        }
    }
    return true;
}

size_t EdgeSet::Size() const {
    return edges_.size();
}

bool EdgeSet::Contains(const Edge& e) const {
    return edges_hash_set_.contains(e);
}

void EdgeSet::RemoveEdge(const Edge& e) {
    edges_hash_set_.erase(e);
    auto it = std::find(edges_.begin(), edges_.end(), e);
    if (it != edges_.end()) {
        edges_.erase(it);
    }
}

const Edge& EdgeSet::GetEdge(size_t index) const {
    return edges_[index];
}

EdgeSet EdgeSet::GetAdjacentEdges(size_t vertex) const {
    EdgeSet ans;
    for (const auto& edge : edges_) {
        if (edge.from == vertex || edge.to == vertex) {
            ans.AddEdge(edge.from != vertex ? edge.GetReversed() : edge);
        }
    }
    return ans;
}

void EdgeSet::AddAll(const EdgeSet& set) {
    for (const auto& e : set) {
        AddEdge(e);
    }
}
