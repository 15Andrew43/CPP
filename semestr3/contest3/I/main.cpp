#include <iostream>
#include <vector>

using vertex_t = size_t;

class DSU {
    using elem_t = size_t;
    mutable std::vector<elem_t> predecessors_;
    std::vector<size_t> ranks_;
    std::vector<size_t> weight_;
public:
    DSU(size_t n_sets) : predecessors_(n_sets), ranks_(n_sets, 0), weight_(n_sets, 0) {
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
    void Union(elem_t elem0, elem_t elem1, size_t weight) {
        elem0 = FindSet(elem0);
        elem1 = FindSet(elem1);
        if (ranks_[elem0] < ranks_[elem1]) {
            predecessors_[elem0] = elem1;
            weight_[elem1] += (weight + weight_[elem0]);
        } else if (ranks_[elem0] > ranks_[elem1]) {
            predecessors_[elem1] = elem0;
            weight_[elem0] += (weight + weight_[elem1]);
        } else {
            if (elem0 != elem1) {
                ++ranks_[elem0];
                predecessors_[elem1] = elem0;
                weight_[elem0] += (weight + weight_[elem1]);
            } else {
                weight_[elem0] += weight;
            }

        }
    }
    size_t GetWeight(elem_t elem) {
        return weight_[FindSet(elem)];
    }
};

enum Operation {
    kAdd = 1,
    kAskWeight = 2
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    size_t n_vertex, n_operation;
    std::cin >> n_vertex >> n_operation;

    DSU dsu(n_vertex);

    for (int i = 0; i < n_operation; ++i) {
        int operation;
        std::cin >> operation;
        if (operation == kAdd) {
            size_t from, to;
            size_t weight;
            std::cin >> from >> to >> weight;
            --from, --to;
            dsu.Union(from, to, weight);
        } else if (operation == kAskWeight) {
            size_t vertex;
            std::cin >> vertex;
            --vertex;
            std::cout << dsu.GetWeight(vertex) << '\n';
        }
    }
    return 0;
}