
#include "path_set.h"
#include <stdexcept>
#include <graph.h>

size_t PathSet::Size() const {
    return paths_.size();
}

size_t PathSet::GetVertexesInCycles() {
    size_t ans = 0;
    for (auto& path : paths_) {
        if (path.GetFirst() == path.GetLast()) {
            ans += path.Size();
        }
    }
    return ans;
}

std::vector<Path>::const_iterator PathSet::begin() const {
    return paths_.begin();
}


std::vector<Path>::const_iterator PathSet::end() const {
    return paths_.cend();
}

PathSet::PathSet(const EdgeSet& edge_set, size_t graph_size) : paths_() {
    if (!edge_set.IsTwoMatching()) {
        throw std::runtime_error("Unable to convert edge set to path set");
    }
    Graph graph(graph_size);
    for (const Edge& edge : edge_set) {
        graph.AddEdge(edge, 1);
    }

    auto components = graph.GetComponents();

    // Finding paths and cycles;

    for (const auto& component : components) {
        bool found_init_vertex = false;
        for (size_t vertex : component) {
            if (graph.GetAdjacentEdges(vertex).Size() == 1) {
                //It is a simple path
                paths_.emplace_back(graph.GetComponent(vertex));
                found_init_vertex = true;
                break;
            }
        }
        if (found_init_vertex) {
            continue;
        }
        // It is a cycle
        paths_.emplace_back(graph.GetComponent(component.front()));
        paths_.back().AddToPath(paths_.back().GetFirst());
    }
}

const Path& PathSet::operator[](size_t index) const {
    return paths_[index];
}

EdgeSet PathSet::ToEdgeSet() const {
    EdgeSet ans;
    for (auto& path : paths_) {
        ans.AddAll(path.ToEdgeSet());
    }
    return ans;
}

std::vector<Path>::iterator PathSet::begin() {
    return paths_.begin();
}

std::vector<Path>::iterator PathSet::end() {
    return paths_.end();
}

void PathSet::AddPath(const Path& path) {
    paths_.push_back(path);
}
