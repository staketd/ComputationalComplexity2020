#pragma once

#include <iostream>
#include <edge_set.h>
#include <graph.h>

template<typename EdgeSetGenerator>
class TLSApproximation {
public:
    explicit TLSApproximation(size_t graph_size) : depleted_graph_(graph_size), main_graph_(graph_size),
                                                   size_(graph_size) {
    }

    void ReadAndInit() {
        for (size_t from = 0; from < size_; ++from) {
            size_t k;
            std::cin >> k;
            size_t last_small_edge_vertex = 0;
            for (size_t j = 0; j < k; ++j) {
                size_t to;
                std::cin >> to;
                --to;
                main_graph_.AddEdge({from, to}, 2);
                while (last_small_edge_vertex < to) {
                    main_graph_.AddEdge({from, last_small_edge_vertex}, 1);
                    depleted_graph_.AddEdge({from, last_small_edge_vertex++}, 1);
                }
                last_small_edge_vertex = to + 1;
            }
            while (last_small_edge_vertex < size_) {
                main_graph_.AddEdge({from, last_small_edge_vertex}, 1);
                depleted_graph_.AddEdge({from, last_small_edge_vertex++}, 1);
            }
        }
    }

    EdgeSet getSolution() {
        return EdgeSet();
    }

private:
    EdgeSet findPathCoverApproximation() {
        return EdgeSet();
    }

private:
    using EdgeWeight = long long;
    Graph main_graph_;
    Graph depleted_graph_;
    size_t size_;
};
