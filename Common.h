#pragma once

#include <edge_set.h>
#include <graph.h>
#include <unordered_set>
#include <path_set/path_set.h>
#include <iostream>

class Common {
public:
    static bool IsImprovement(const EdgeSet& A, const EdgeSet& C, size_t graph_size) {
        if (A.Size() == 0 && C.Size() != 0 && C.IsTwoMatching()) {
            return true;
        }
        if (!A.IsTwoMatching()) {
            throw std::runtime_error("Set A must be 2-matching!");
        }
        EdgeSet change = SymmetricalDifference(A, C);

        if (!change.IsTwoMatching()) {
            return false;
        }
        PathSet old_paths(A, graph_size);
        PathSet paths(change, graph_size);
        return old_paths.Size() > paths.Size() ||
               (old_paths.Size() == paths.Size() && old_paths.GetVertexesInCycles() < paths.GetVertexesInCycles());
    }

    static EdgeSet SymmetricalDifference(const EdgeSet& A, const EdgeSet& C) {
        std::unordered_set<Edge> set_A;
        std::unordered_set<Edge> symm_diff;
        for (const Edge& e : A) {
            set_A.insert(e);
            symm_diff.insert(e);
        }

        for (const Edge& e : C) {
            if (set_A.contains(e)) {
                symm_diff.erase(e);
            } else {
                symm_diff.insert(e);
            }
        }
        EdgeSet change;
        for (const auto& entry : symm_diff) {
            change.AddEdge(entry);
        }
        return change;
    }

    static Graph ReadAndInitGraph() {
        size_t size;
        std::cin >> size;
        Graph main_graph(size);
        for (size_t from = 0; from < size; ++from) {
            size_t k;
            std::cin >> k;
            size_t last_small_edge_vertex = 0;
            for (size_t j = 0; j < k; ++j) {
                size_t to;
                std::cin >> to;
                --to;
                main_graph.AddEdge({from, to}, 2);
                while (last_small_edge_vertex < to) {
                    if (last_small_edge_vertex == from) {
                        last_small_edge_vertex++;
                        continue;
                    }
                    main_graph.AddEdge({from, last_small_edge_vertex++}, 1);
                }
                last_small_edge_vertex = to + 1;
            }
            while (last_small_edge_vertex < size) {
                if (last_small_edge_vertex == from) {
                    last_small_edge_vertex++;
                    continue;
                }
                main_graph.AddEdge({from, last_small_edge_vertex++}, 1);
            }
        }
        return main_graph;
    }
};