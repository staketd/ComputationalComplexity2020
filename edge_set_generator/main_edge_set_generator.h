#pragma once

#include <optional>
#include <Common.h>
#include <path_set/path_set.h>


class MainEdgeSetGenerator {
public:
    static std::optional<PathSet> FindImprovement(const EdgeSet& now, const Graph&);

private:
    static std::optional<PathSet>
    Find(size_t vertex, const EdgeSet& A, EdgeSet& C, const Graph& graph, std::vector<size_t>& degr);

    static std::optional<PathSet>
    AddTwo(size_t vertex, const EdgeSet& A, EdgeSet& C, const Graph& graph, std::vector<size_t>& degr);
};
