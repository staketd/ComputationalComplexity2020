
#include "path.h"

#include <utility>

void Path::AddToPath(size_t vertex) {
    vertexes_.push_back(vertex);
}

size_t Path::GetLast() const {
    return vertexes_.back();
}

size_t Path::GetFirst() const {
    return vertexes_.front();
}

void Path::RemoveLast() {
    vertexes_.pop_back();
}

size_t Path::GetVertex(size_t index) const {
    return vertexes_[index];
}

size_t Path::Size() const {
    return vertexes_.size();
}

void Path::addAll(const Path& path) {
    for (auto vertex : path.vertexes_) {
        vertexes_.push_back(vertex);
    }
}

Path::Path(std::vector<size_t>  vertexes) : vertexes_(std::move(vertexes)) {
}

EdgeSet Path::ToEdgeSet() const {
    EdgeSet ans;
    if (vertexes_.size() == 2 && GetFirst() == GetLast()) {
        return ans;
    }
    for (int i = 0; i < (int)vertexes_.size() - 1; ++i) {
        ans.AddEdge({vertexes_[i], vertexes_[i + 1]});
    }
    return ans;
}

std::vector<size_t>::const_iterator Path::begin() const {
    return vertexes_.cbegin();
}

std::vector<size_t>::const_iterator Path::end() const {
    return vertexes_.cend();
}
