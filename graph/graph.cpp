#include "graph.h"

Weight Graph::GetWeight(Edge e) {
    if (edges_weights_.find(e) != edges_weights_.end()) {
        return edges_weights_[e];
    } else if (edges_weights_.find(e.getReversed()) != edges_weights_.end()) {
        return edges_weights_[e.getReversed()];
    }
    throw std::runtime_error("No such edge");
}

void Graph::AddEdge(Edge e, Weight weight) {
    edges_weights_[e] = weight;
    adjacent_edges_[e.from].addEdge(e);
}

EdgeSet& Graph::GetAdjacentEdges(size_t vertex) {
    return adjacent_edges_[vertex];
}

Graph::Graph(size_t size) : edges_weights_(), adjacent_edges_(size) {
}

