#include <iostream>
#include <vector>
#include <stack>

using vertex_t = size_t;

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

enum Name {
    kCut = 0,
    kAsk = 1
};

struct Operation {
    Name name;
    vertex_t vertex0;
    vertex_t vertex1;
};


enum Answer {
    NO = 0,
    YES = 1
};
int main() {
    vertex_t n_vertex;
    int n_edge, n_operation;
    std::cin >> n_vertex >> n_edge >> n_operation;

    for (int i = 0; i < n_edge; ++i) {
        int from, to;
        std::cin >> from >> to;
    }

    std::stack<Operation> operations;
    for (int i = 0; i < n_operation; ++i) {
        std::string operation;
        vertex_t vertex0, vertex1;
        std::cin >> operation >> vertex0 >> vertex1;
        --vertex0, --vertex1;
        if (operation == "cut") {
            operations.push({kCut, vertex0, vertex1});
        } else if (operation == "ask") {
            operations.push({kAsk, vertex0, vertex1});
        }
    }

    DSU dsu(n_vertex);
    std::vector<Answer> answers;
    while (!operations.empty()) {
        auto operation = operations.top();
        operations.pop();
        if (operation.name == kCut) {
            dsu.Union(operation.vertex0, operation.vertex1);
        } else if(operation.name == kAsk){
            if (dsu.FindSet(operation.vertex0) == dsu.FindSet(operation.vertex1)) {
                answers.push_back(YES);
            } else {
                answers.push_back(NO);
            }
        }
    }

    for (auto it = answers.rbegin(); it != answers.rend(); ++it) {
        if (*it == YES) {
            std::cout << "YES\n";
        } else {
            std::cout << "NO\n";
        }
    }

    return 0;
}