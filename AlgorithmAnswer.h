#pragma once
#include <path/path.h>

#include <utility>

struct AlgorithmAnswer {
    AlgorithmAnswer(Path cycle, long long weight) : cycle(std::move(cycle)), weight(weight) {}
    Path cycle;
    long long weight;
};