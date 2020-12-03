#include <iostream>
#include <vector>

void Print(std::vector<uint32_t >& vec) {
    for (auto elem: vec) {
        std::cout << elem << ' ';
    }
    std::cout << '\n';
}

std::pair<uint32_t, uint32_t>GetNotLowerPow2(uint32_t n) {
    uint32_t k = 0;
    uint32_t res = 1;
    while (res < n) {
        res *= 2;
        ++k;
    }
    return {k, res};
}
std::pair<uint32_t, uint32_t>GetNotHigherPow2(uint32_t n) {
    uint32_t k = 0;
    uint32_t res = 1;
    while (res * 2 < n) {
        res *= 2;
        ++k;
    }
    return {k, res};
}


uint32_t Left(uint32_t number) {
    return number * 2 + 1;
}
uint32_t Right(uint32_t number) {
    return number * 2 + 2;
}
uint32_t Parent(uint32_t number) {
    return (number - 1) / 2;
}


template <class T>
class SegmentTree {
    uint32_t cnt_elements_;
    T normal_element_;

    void Push(uint32_t node) {
        std::cout << "push = " << promise[node] << '\n';
        promise[Left(node)] += promise[node];
        promise[Right(node)] += promise[node];
        promise[node] = 0;
    }
    std::pair<uint32_t, uint32_t> GetBoarders(uint32_t node) {
        auto [pow, res] = GetNotHigherPow2(node);
        uint32_t cnt_group_elements = cnt_elements_ / res;
        uint32_t left_board = cnt_elements_ + (node - res) * cnt_group_elements;
        uint32_t right_board = left_board + cnt_group_elements - 1;
        return {left_board, right_board};
    }
    void Query(uint32_t node, uint32_t ind) {
        auto [left_board, right_board] = GetBoarders(node); // ?????????????????????
//        left_board += (cnt_elements_ - 1);
//        right_board += (cnt_elements_ - 1);
        std::cout << left_board << ' ' << ind << ' ' << right_board << '\n';
        if (ind < left_board || ind > right_board) {
            return;
        }
        if (ind >= left_board && ind <= right_board) {
            Push(node);
            Query(Left(node), ind);
            Query(Right(node), ind);
        }
    }

public:
    std::vector<T> promise;

    SegmentTree(std::vector<T>& array, T normal_element) {
        uint32_t cnt_elements = array.size();
        for (uint32_t i = 0; i < GetNotLowerPow2(cnt_elements).second - cnt_elements; ++i) {
            array.push_back(normal_element);
        }
        cnt_elements = array.size();
        promise.resize(cnt_elements * 2 - 1);
        std::copy(array.begin(), array.end(), promise.begin() + cnt_elements - 1);
        cnt_elements_ = cnt_elements;
        normal_element_ = normal_element;
        Print(promise);
        std::cout << "cnt_elem = " << cnt_elements_ << '\n';
    }
    void Update(uint32_t node, uint32_t left_ind, uint32_t right_ind, T value) {
        auto [left_board, right_board] = GetBoarders(node);
        if (left_ind > right_board || right_ind < left_board) { // no intersection
            return;
        }
        if (left_ind <= left_board && right_board <= right_ind) { // inside
            promise[node] += value;
        }
        else { // itersection
            Push(node);
            Update(Left(node), left_ind, right_ind, value);
            Update(Right(node), left_ind, right_ind, value);
        }
    }
    T operator()(uint32_t ind) {
        std::cout << "pep\n";
        Query(0, ind + (cnt_elements_ - 1));
        return promise[ind + cnt_elements_];
    }
};

int main() {
    uint32_t cnt_solders;
    std::cin >> cnt_solders;
    std::vector<uint32_t> awards(cnt_solders);
    for (uint32_t i = 0; i < cnt_solders; ++i) {
        std::cin >> awards[i];
    }

    SegmentTree<uint32_t> tree(awards, 0);

    uint32_t cnt_requests;
    std::cin >> cnt_requests;

    for (uint32_t i = 0; i < cnt_requests; ++i) {
        char operation;
        std::cin >> operation;
        if (operation == 'g') {
            uint32_t ind;
            std::cin >> ind;
            std::cout << tree(ind - 1) << '\n';
        } else if (operation == 'a') {
            uint32_t left_ind, right_ind, value;
            std::cin >> left_ind >> right_ind >> value;
            tree.Update(0, left_ind - 1, right_ind - 1, value);
            Print(tree.promise);
        }
    }
    return 0;
}