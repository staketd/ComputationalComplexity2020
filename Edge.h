#pragma once

class Edge {
public:
    Edge getReversed() {
        return {to, from};
    }

    bool operator==(const Edge& edge) const {
        return from == edge.from && to == edge.to;
    }

public:
    size_t from;
    size_t to;
};

namespace std
{
    template<>
    struct hash<Edge> {
        size_t operator()(const Edge& e) const {
            return hash<size_t>{}(e.from) ^ hash<size_t>{}(e.to);
        }
    };
}
