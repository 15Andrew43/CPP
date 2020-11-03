#include <iostream>
#include <vector>

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

bool InConnectedComponent(size_t n_island, const DSU& dsu) {
    for (size_t i = 0; i < n_island; ++i) {
        if (dsu.FindSet(i) != dsu.FindSet(0)) {
            return false;
        }
    }
    return true;
}

int main() {
    size_t n_island;
    size_t n_brigges;
    std::cin >> n_island >> n_brigges;

    DSU dsu(n_island);

    for (size_t i = 0; i < n_brigges; ++i) {
        size_t from, to;
        std::cin >> from >> to;
        dsu.Union(from, to);
        if (InConnectedComponent(n_island, dsu)) {
            std::cout << i + 1;
            break;
        }
    }
    return 0;
}