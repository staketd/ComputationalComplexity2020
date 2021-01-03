#pragma once
#include <vector>
#include <Edge.h>

class EdgeSet {
public:
    void addEdge(Edge e);

    auto cbegin();
    auto begin();
    auto cend();
    auto end();

private:
    std::vector<Edge> edges_;
};
