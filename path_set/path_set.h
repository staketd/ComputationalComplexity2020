#pragma once
#include <path/path.h>
#include <edge_set.h>
#include <graph.h>

class PathSet {
public:
    PathSet() = default;
    PathSet(const EdgeSet& edge_set, size_t graph_size);

    void AddPath(const Path& path);

    size_t Size() const ;
    size_t GetVertexesInCycles();

    const Path& operator[](size_t index) const;
    EdgeSet ToEdgeSet() const;

    std::vector<Path>::const_iterator begin() const;
    std::vector<Path>::const_iterator end() const;

    std::vector<Path>::iterator begin();
    std::vector<Path>::iterator end();

private:
    std::vector<Path> paths_;
};

