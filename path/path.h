#pragma once

#include <vector>
#include <edge_set.h>

class Path {
public:
    Path() = default;

    explicit Path(std::vector<size_t> vertexes);

    void AddToPath(size_t vertex);

    size_t GetLast() const;

    size_t GetFirst() const;

    void RemoveLast();

    size_t GetVertex(size_t index) const;

    size_t Size() const;

    void addAll(const Path& path);

    EdgeSet ToEdgeSet() const;

    std::vector<size_t>::const_iterator begin() const;

    std::vector<size_t>::const_iterator end() const;


private:
    std::vector<size_t> vertexes_;
};

