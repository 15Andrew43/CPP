#include <iostream>
#include <vector>

struct Edge {
    size_t weight;
    size_t from;
    size_t to;
    Edge(size_t weight, size_t from, size_t to) : weight(weight), from(from), to(to) {
    }
};

using Graph = std::vector<std::vector<Edge>>;

class DSU {
    using elem_t = int;
    mutable std::vector<elem_t> predecessors_;
    std::vector<size_t> ranks_;
public:
    DSU(size_t n_sets) : predecessors_(n_sets), ranks_(n_sets, 0) {
        for (elem_t i = 0; i < n_sets; ++i) {
            predecessors_[i] = i;
        }
    }
    elem_t MakeSet() {
        predecessors_.push_back(predecessors_.size());
        ranks_.push_back(0);
        return predecessors_.size() - 1;
    }
    elem_t FindSet(elem_t elem) const {
        if (predecessors_[elem] == elem) {
            return elem;
        }
        predecessors_[elem] = FindSet(predecessors_[elem]);
        return predecessors_[elem];
    }
    void Union(elem_t elem0, elem_t elem1) {
        elem0 = FindSet(elem0);
        elem1 = FindSet(elem1);
        if (ranks_[elem0] < ranks_[elem1]) {
            predecessors_[elem0] = elem1;
        } else if (ranks_[elem0] > ranks_[elem1]) {
            predecessors_[elem1] = elem0;
        } else {
            ++ranks_[elem0];
            predecessors_[elem1] = elem0;
        }
    }
};


size_t Kruskal(size_t n_cities, std::vector<Edge>& edges) {
//    std::sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
//                                                return a.weight < b.weight;
//                                            });
    DSU dsu(n_cities);

    size_t length = 0;

    for (auto edge: edges) {
        if (dsu.FindSet(edge.from) != dsu.FindSet(edge.to)) {
            length += edge.weight;
            dsu.Union(edge.from, edge.to);
        }
    }
    return length;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    size_t n_vertex, n_edge;
    std::cin >> n_vertex >> n_edge;

    std::vector<Edge> edges;

    for (size_t i = 0; i < n_edge; ++i) {
        size_t from, to;
        size_t weight;
        std::cin >> from >> to >> weight;
        --from, --to;
        edges.emplace_back(weight, from, to);
    }

    std::cout << Kruskal(n_vertex, edges);
    return 0;
}