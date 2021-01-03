#include "edge_set.h"

void EdgeSet::addEdge(Edge e) {
    edges_.push_back(e);
}

auto EdgeSet::cbegin() {
    return edges_.cbegin();
}

auto EdgeSet::begin() {
    return edges_.begin();
}

auto EdgeSet::cend() {
    return edges_.cend();
}

auto EdgeSet::end() {
    return edges_.end();
}
