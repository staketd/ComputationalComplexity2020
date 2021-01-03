#include "graph.h"

Weight Graph::GetWeight(Edge e) const {
    if (e.from == e.to) {
        return 0;
    }
    if (edges_weights_.find(e) != edges_weights_.end()) {
        return edges_weights_.at(e);
    } else if (edges_weights_.find(e.GetReversed()) != edges_weights_.end()) {
        return edges_weights_.at(e.GetReversed());
    }
    throw std::runtime_error("No such edge");
}

void Graph::AddEdge(const Edge& e, Weight weight) {
    edges_weights_[e] = weight;
    adjacent_edges_[e.from].AddEdge(e);
    adjacent_edges_[e.to].AddEdge(e.GetReversed());
}

const EdgeSet& Graph::GetAdjacentEdges(size_t vertex) const {
    return adjacent_edges_[vertex];
}

Graph::Graph(size_t size) : edges_weights_(), adjacent_edges_(size), size_(size) {
}

std::vector<std::vector<size_t>> Graph::GetComponents() const {
    std::vector<std::vector<size_t>> answer;
    std::vector<int> used(size_, 0);
    for (size_t i = 0; i < size_; ++i) {
        if (!used[i]) {
            answer.emplace_back();
            ComponentDfs(i, used, answer.back());
        }
    }
    return answer;
}

void Graph::ComponentDfs(size_t v, std::vector<int>& used, std::vector<size_t>& component) const {
    used[v] = true;
    component.push_back(v);
    for (const Edge& e : GetAdjacentEdges(v)) {
        if (!used[e.to]) {
            ComponentDfs(e.to, used, component);
        }
    }
}

std::vector<size_t> Graph::GetComponent(size_t vertex) const {
    std::vector<size_t> component;
    std::vector<int> used(size_, false);
    ComponentDfs(vertex, used, component);
    return component;
}

size_t Graph::Size() const {
    return size_;
}

