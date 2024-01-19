#pragma once

#include <graph.h>
#include <AlgorithmAnswer.h>

class SlowCorrectAlgorithm {
public:

    explicit SlowCorrectAlgorithm(Graph graph) : graph_(std::move(graph)) {}

    AlgorithmAnswer GetSolution() {
        size_t N = (1 << graph_.Size());
        std::vector<std::vector<long long>> dp(N, std::vector<long long> (graph_.Size(), INF));
        std::vector<std::vector<int>> p(N, std::vector<int> (graph_.Size(), -1));
        dp[1][0] = 0;
        for (size_t mask = 0; mask < N; ++mask) {
            for (size_t i = 0; i < graph_.Size(); ++i) {
                if (dp[mask][i] == INF) {
                    continue;
                }
                for (size_t j = 0; j < graph_.Size(); ++j) {
                    if (i == j) {
                        continue;
                    }
                    if ((mask >> j) & 1) {
                        continue;
                    }
                    size_t new_mask = mask | (1 << j);
                    if (dp[new_mask][j] > dp[mask][i] + graph_.GetWeight({i, j})) {
                        dp[new_mask][j] = dp[mask][i] + graph_.GetWeight({i, j});
                        p[new_mask][j] = i;
                    }
                }
            }
        }
        long long ans = INF;
        size_t last_vert = 0;
        for (size_t i = 1; i < graph_.Size(); ++i) {
            if (ans > dp[N - 1][i] + graph_.GetWeight({i, 0})) {
                ans = dp[N - 1][i] + graph_.GetWeight({i, 0});
                last_vert = i;
            }
        }

        std::vector<size_t> path(1, last_vert);
        size_t p_mask = N - 1;
        while (last_vert != 0) {
            size_t pp = last_vert;
            last_vert = p[p_mask][last_vert];
            p_mask = p_mask ^ (1 << pp);
            path.push_back(last_vert);
        }
        std::reverse(path.begin(), path.end());
        path.push_back(0);
        return {Path(path), ans};
    }
private:
    static const size_t INF = 1e18;
    Graph graph_;
};
