#include <iostream>
#include <vector>
#include <iomanip>

void Print(std::vector<std::vector<std::pair<uint32_t, uint32_t >>>& vec) {
    for (auto line: vec) {
        for (auto [hight, cnt]: line) {
            std::cout << "(" << hight << ", "  << cnt  << ")    ";
        }
        std::cout << '\n';
    }
}

std::pair<uint32_t, uint32_t>GetLowerPow2(uint32_t n) {
    uint32_t k = 0;
    uint32_t res = 1;
    while (res * 2 < n) {
        res *= 2;
        ++k;
    }
    return {k, res};
}


struct Max {
    uint32_t operator()(const uint32_t& a, const uint32_t& b) {
        return std::max(a, b);
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
            std::vector<T> operation_values_pow(cnt_solders);
            for (uint32_t j = 0; j < cnt_solders - cur_len; ++j) {
                operation_values_pow[j] = operation(operation_values.back()[j], operation_values.back()[j + cur_len]);
            }
            operation_values.push_back(operation_values_pow);
            cur_len *= 2;
        }
//        std::cout << '\n';
//        Print(operation_values);
    }
    std::pair<T, uint32_t> operator()(uint32_t left_ind, uint32_t right_ind) {
        auto [pow, len] = GetLowerPow2(right_ind - left_ind + 1);
//        operation(operation_values[pow][left_ind], operation_values[pow][right_ind - len + 1]);
        auto first = operation_values[pow][left_ind];
        auto second = operation_values[pow][right_ind - len + 1];
        auto res = operation(first, second);
        uint32_t cnt = 0;
        for (uint32_t i = left_ind; i <= right_ind; ++i) {
            if (operation_values[0][i] == res) {
                ++cnt;
            }
        }
        return {res, cnt};
    }
};


int main() {
    uint32_t cnt_solders;
    std::cin >> cnt_solders;
    std::vector<uint32_t> awards(cnt_solders);
    for (uint32_t i =0; i < cnt_solders; ++i) {
        std::cin >> awards[i];
    }
    SparseTable<uint32_t, Max> sparse_table(std::move(awards));

    uint32_t cnt_requests;
    std::cin >> cnt_requests;

    uint32_t left_ind, right_ind;
    for (uint32_t i = 0; i < cnt_requests; ++i) {
        std::cin >> left_ind >> right_ind;
        auto [hight, cnt] = sparse_table(left_ind - 1, right_ind - 1);
        std::cout << hight << ' ' << cnt << '\n';
    }
    return 0;
}