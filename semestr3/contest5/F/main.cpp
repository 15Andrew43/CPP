#include <iostream>
#include <vector>
#include <algorithm>

struct Leaf {
    uint32_t value;
    uint32_t cnt_values;
};
bool operator<(const Leaf& a, const Leaf& b) {
    return a.value < b.value;
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

struct Max {
    Leaf operator()(const Leaf& a, const Leaf& b) {
        if (a.value == b.value) {
            return {a.value, a.cnt_values + b.cnt_values};
        }
        return std::max(a, b);
    }
};

uint32_t Left(uint32_t number) {
    return number * 2 + 1;
}
uint32_t Right(uint32_t number) {
    return number * 2 + 2;
}
uint32_t Parent(uint32_t number) {
    return (number - 1) / 2;
}


template <class T, class Operation>
class SegmentTree {
    std::vector<Leaf> tree;
    Operation operation;
    uint32_t cnt_elements_;
    T normal_element_;
public:
    SegmentTree(std::vector<T>& array, T normal_element) {
        uint32_t cnt_elements = array.size();
        for (uint32_t i = 0; i < GetNotLowerPow2(cnt_elements).second - cnt_elements; ++i) {
            array.push_back(normal_element);
        }
        cnt_elements = array.size();
        tree.resize(cnt_elements * 2 - 1);
        std::copy(array.begin(), array.end(), tree.begin() + cnt_elements - 1);
        for (int32_t i = cnt_elements - 2; i >= 0; --i) {
            tree[i] = operation(tree[Left(i)], tree[Right(i)]);
        }

        cnt_elements_ = cnt_elements;
        normal_element_ = normal_element;
    }
    Leaf operator()(uint32_t left_ind, uint32_t right_ind) {
        left_ind += (cnt_elements_ - 1);
        right_ind += (cnt_elements_ - 1);
        if (left_ind == right_ind) {
            return tree[left_ind];
        }
        Leaf left_res(normal_element_);
        Leaf right_res(normal_element_);
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
                left_res = operation(left_res, tree[left_ind]);
            }
        }
        return operation(left_res, right_res);
    }
};


int main() {
    uint32_t cnt_solders;
    std::cin >> cnt_solders;
    std::vector<Leaf> awards(cnt_solders);
    for (uint32_t i = 0; i < cnt_solders; ++i) {
        std::cin >> awards[i].value;
        awards[i].cnt_values = 1;
    }

    SegmentTree<Leaf, Max> tree(awards, {0, 1});

    uint32_t cnt_requests;
    std::cin >> cnt_requests;

    uint32_t left_ind, right_ind;
    for (uint32_t i = 0; i < cnt_requests; ++i) {
        std::cin >> left_ind >> right_ind;
        auto [max, cnt] = tree(left_ind - 1, right_ind - 1);
        std::cout << max << ' ' << cnt << '\n';
    }

    return 0;
}