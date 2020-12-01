#include <iostream>
#include <vector>
#include <algorithm>

template <class T>
struct Leaf {
    T value;
    uint32_t cnt_values;
    uint32_t ind;
};

std::pair<uint32_t, uint32_t>GetNotLowerPow2(uint32_t n) {
    uint32_t k = 0;
    uint32_t res = 1;
    while (res < n) {
        res *= 2;
        ++k;
    }
    return {k, res};
}

template <class T>
struct Max {
    Leaf<T> operator()(const Leaf<T>& a, const Leaf<T>& b) {
        if (a.first == b.first && a.ind != b.ind) {
            return {a.first, a.second + b.second, };
        }
        return std::max(a, b);
    }
};

template <class T>
T Left(T number) {
    return number * 2 + 1;
}
template <class T>
T Right(T number) {
    return number * 2 + 2;
}
template <class T>
T Parent(T number) {
    return (number - 1) / 2;
}

template <class T, class Operation>
class SegmentTree {
    std::vector<std::pair<T, uint32_t>> tree;
    Operation operation;
    uint32_t cnt_elements_;
    T normal_element_;
public:
    SegmentTree(std::vector<std::pair<T, uint32_t >>& array, T normal_element) {
        uint32_t cnt_elements = array.size();
        for (uint32_t i = 0; i < GetNotLowerPow2(cnt_elements).second - cnt_elements; ++i) {
            array.push_back({normal_element, 1});
        }
        cnt_elements = array.size();
        tree.reserve(cnt_elements * 2 - 1);
        std::copy(array.begin(), array.end(), tree.begin() + cnt_elements - 1);
        for (uint32_t i = cnt_elements - 2; i >= 0; --i) {
            tree[i] = operation(tree[Left(i)], Left(i), tree[Right(i)], Right(i));
        }
        cnt_elements_ = cnt_elements;
        normal_element_ = normal_element;
    }
    std::pair<T, uint32_t> operator()(uint32_t left_ind, uint32_t right_ind) {
        left_ind += (cnt_elements_ - 1);
        right_ind += (cnt_elements_ - 1);
        std::pair<T, uint32_t> left_res({normal_element_, 1});
        std::pair<T, uint32_t> right_res({normal_element_, 1});
        while (left_ind < right_ind) {
            if (left_ind == Right(Parent(left_ind))) {
                left_res = operation(left_res, tree[left_ind]);
            }
            left_ind = Parent(left_ind + 1);
            if (right_ind == Left(Parent(right_ind))) {
                right_res = operation(right_res, tree[right_ind]);
            }
            right_ind = Parent(right_ind - 1);
            if (left_ind == right_ind) {
                left_res = operation(left_res, tree[left_ind]); // ??????????????????????????
            }
        }
        return operation(left_res, right_res);
    }
};


int main() {
    uint32_t cnt_solders;
    std::cin >> cnt_solders;
    std::vector<std::pair<uint32_t, uint32_t>> awards(cnt_solders);
    for (uint32_t i = 0; i < cnt_solders; ++i) {
        std::cin >> awards[i].first;
        awards[i].second = 1;
    }

    SegmentTree<uint32_t, Max> tree(awards, 0);

    std::cout << "Hello, World!" << std::endl;
    return 0;
}