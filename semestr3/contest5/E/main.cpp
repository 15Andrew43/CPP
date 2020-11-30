#include <iostream>
#include <vector>


std::pair<uint32_t, uint32_t>GetLowerPow2(uint32_t n) {
    uint32_t k = 0;
    uint32_t res = 1;
    while (res * 2 < n) {
        res *= 2;
        ++k;
    }
    return {k, res};
}

uint32_t gcd(uint32_t a, uint32_t b) {
    while (b) {
        a = a % b;
        std::swap(a, b);
    }
    return a;
}

struct GCD {
    uint32_t operator()(uint32_t a, uint32_t b) {
        return gcd(a, b);
    }
};

template <class T, class Operation>
class SparseTable {
    std::vector<std::vector<T>> operation_values;
    Operation operation;
public:
    SparseTable(std::vector<T>&& values) : operation_values(1) {
        auto cnt_solders = values.size();
        operation_values[0] = values;
        auto pow = GetLowerPow2(values.size()).first;
        uint32_t cur_len = 1;
        for (uint32_t i = 1; i < pow + 1; ++i) {
            std::vector<uint32_t> operation_values_pow(cnt_solders);
            for (uint32_t j = 0; j < cnt_solders - cur_len; ++j) {
                operation_values_pow[j] = operation(operation_values.back()[j], operation_values.back()[j + cur_len]);
            }
            operation_values.push_back(operation_values_pow);
            cur_len *= 2;
        }
    }
    T operator()(uint32_t left_ind, uint32_t right_ind) {
        auto [pow, len] = GetLowerPow2(right_ind - left_ind + 1);
        return operation(operation_values[pow][left_ind], operation_values[pow][right_ind - len + 1]);
    }
};


int main() {
    uint32_t cnt_solders;
    std::cin >> cnt_solders;
    std::vector<uint32_t> awards(cnt_solders);
    for (uint32_t i =0; i < cnt_solders; ++i) {
        std::cin >> awards[i];
    }
    SparseTable<uint32_t, GCD> sparse_table(std::move(awards));

    uint32_t cnt_requests;
    std::cin >> cnt_requests;

    uint32_t left_ind, right_ind;
    for (uint32_t i = 0; i < cnt_requests; ++i) {
        std::cin >> left_ind >> right_ind;
        std::cout << sparse_table(left_ind - 1, right_ind - 1) << '\n';
    }
    return 0;
}