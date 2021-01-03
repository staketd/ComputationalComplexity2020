#pragma once

#include <iostream>
#include <edge_set.h>
#include <graph.h>
#include <path/path.h>
#include <path_set/path_set.h>
#include <AlgorithmAnswer.h>
#include <edge_set_generator/main_edge_set_generator.h>

template<typename EdgeSetGenerator>
class TLSApproximation {
public:
    explicit TLSApproximation(Graph graph) : size_(graph.Size()), depleted_graph_(graph.Size()),
                                             main_graph_(std::move(graph)) {
        for (size_t i = 0; i < size_; ++i) {
            for (const auto& edge : main_graph_.GetAdjacentEdges(i)) {
                if (main_graph_.GetWeight(edge) == 1) {
                    depleted_graph_.AddEdge(edge, 1);
                }
            }
        }
    }

    AlgorithmAnswer getSolution() {
        Path answer;
        PathSet path_cover = findPathCoverApproximation();
        std::vector<int> covered(main_graph_.Size(), false);
        for (Path& path : path_cover) {
            for (auto vertex : path) {
                covered[vertex] = true;
            }
            if (path.GetLast() == path.GetFirst()) {
                path.RemoveLast();
            }
        }
        for (size_t i = 0; i < main_graph_.Size(); ++i) {
            if (!covered[i]) {
                path_cover.AddPath(Path({i}));
            }
        }
        for (size_t i = 0; i < path_cover.Size(); ++i) {
            answer.addAll(path_cover[i]);
        }
        answer.AddToPath(path_cover[0].GetFirst());
        int64_t ans_weight = 0;
        for (size_t i = 0; i < answer.Size(); ++i) {
            size_t next = (i + 1) % answer.Size();
            ans_weight += main_graph_.GetWeight({answer.GetVertex(i), answer.GetVertex(next)});
        }
        return {answer, ans_weight};
    }

private:
    PathSet findPathCoverApproximation() {
        EdgeSet now;
        PathSet result;
        while (true) {
            auto next = EdgeSetGenerator::FindImprovement(now, depleted_graph_);
            if (!next.has_value()) {
                break;
            }
            result = next.value();
            now = result.ToEdgeSet();
        }
        return result;
    }


private:
    using EdgeWeight = long long;
    size_t size_;
    Graph main_graph_;
    Graph depleted_graph_;
};
