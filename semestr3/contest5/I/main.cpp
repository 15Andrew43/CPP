#include <iostream>
#include <vector>
#include <algorithm>


std::pair<int64_t, int64_t>GetNotLowerPow2(int64_t n) {
    int64_t k = 0;
    int64_t res = 1;
    while (res < n) {
        res *= 2;
        ++k;
    }
    return {k, res};
}

template <class T>
struct Add {
    T operator()(const T& a, const T& b) {
        return a + b;
    }
};

int64_t Left(int64_t number) {
    return number * 2 + 1;
}
int64_t Right(int64_t number) {
    return number * 2 + 2;
}
int64_t Parent(int64_t number) {
    return (number - 1) / 2;
}


template <class T, class Operation>
class SegmentTree {
    std::vector<T> tree;
    Operation operation;
    int64_t cnt_elements_;
    T normal_element_;

    void SiftUp(int64_t ind) {
        do {
            ind = Parent(ind);
            tree[ind] = operation(tree[Left(ind)], tree[Right(ind)]);
        } while (ind > 0);
    }
public:
    SegmentTree(std::vector<T>& array, T normal_element) {
        int64_t cnt_elements = array.size();
        for (int64_t i = 0; i < GetNotLowerPow2(cnt_elements).second - cnt_elements; ++i) {
            array.push_back(normal_element);
        }
        cnt_elements = array.size();
        tree.resize(cnt_elements * 2 - 1);
        std::copy(array.begin(), array.end(), tree.begin() + cnt_elements - 1);
        for (int64_t i = cnt_elements - 2; i >= 0; --i) {
            tree[i] = operation(tree[Left(i)], tree[Right(i)]);
        }

        cnt_elements_ = cnt_elements;
        normal_element_ = normal_element;
    }
    T operator()(int64_t left_ind, int64_t right_ind) {
        left_ind += (cnt_elements_ - 1);
        right_ind += (cnt_elements_ - 1);
        if (left_ind == right_ind) {
            return tree[left_ind];
        }
        T left_res(normal_element_);
        T right_res(normal_element_);
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
    void SetPower(int64_t ind, T power) {
        ind += (cnt_elements_ - 1);
        tree[ind] = power;
        SiftUp(ind);
    }
};


int main() {
    int64_t cnt_solders;
    std::cin >> cnt_solders;
    std::vector<int64_t > powers(cnt_solders);
    for (int64_t i = 0; i < cnt_solders; ++i) {
        std::cin >> powers[i];
    }

    SegmentTree<int64_t, Add<int64_t>> tree(powers, 0);

    int64_t cnt_requests;
    std::cin >> cnt_requests;
    for (int64_t i = 0; i < cnt_requests; ++i) {
        char operation;
        std::cin >> operation;
        if (operation == 's') {
            int64_t left_ind, right_ind;
            std::cin >> left_ind >> right_ind;
            std::cout << tree(left_ind - 1, right_ind - 1) << ' ';
        }
        else if (operation == 'u') {
            int64_t ind, power;
            std::cin >> ind >> power;
            tree.SetPower(ind - 1, power);
        }
    }
    return 0;
}