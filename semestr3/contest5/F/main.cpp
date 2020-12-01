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
    std::pair<uint32_t, uint32_t> operator()(const std::pair<uint32_t, uint32_t>& a, const std::pair<uint32_t, uint32_t>& b) {
        return std::max(a, b);
    }
};

template <class T, class Operation>
class SparseTable {
    std::vector<std::vector<std::pair<T, uint32_t>>> operation_values;
    Operation operation;
    uint32_t GetIntersection(uint32_t pow, uint32_t left, uint32_t right, uint32_t len, T res) {
        std::cout << pow << " " << left << ' ' << right << ' ' << len << ' ' << res << '\n';
        if (left + len - 1 < right - len + 1 || len == 1) {
            return 0;
        }
        if (operation_values[pow][left].first != res || operation_values[pow][right - len + 1].first != res) {
            return 0;
        }

        auto [new_pow, new_len] = GetLowerPow2((left + len - 1) - (right - len + 1));
        return operation_values[pow][left].second
                + operation_values[pow][right - len + 1].second
                - GetIntersection(new_pow, right - len + 1, left + len - 1, new_len, res);
    }
public:
    SparseTable(std::vector<std::pair<T, uint32_t>>&& values) : operation_values(1) {
        auto cnt_solders = values.size();
        operation_values[0] = values;
        auto pow = GetLowerPow2(values.size()).first;
        uint32_t cur_len = 1;
        for (uint32_t i = 1; i < pow + 1; ++i) {
            std::vector<std::pair<T, uint32_t>> operation_values_pow(cnt_solders);
            for (uint32_t j = 0; j < cnt_solders - cur_len; ++j) {
                operation_values_pow[j] = operation(operation_values.back()[j], operation_values.back()[j + cur_len]);
                if (operation_values.back()[j].first == operation_values.back()[j + cur_len].first) {
                    operation_values_pow[j].second = operation_values.back()[j].second + operation_values.back()[j + cur_len].second;
                }
            }
            operation_values.push_back(operation_values_pow);
            cur_len *= 2;
        }
        std::cout << '\n';
        Print(operation_values);
    }
    std::pair<T, uint32_t> operator()(uint32_t left_ind, uint32_t right_ind) {
        auto [pow, len] = GetLowerPow2(right_ind - left_ind + 1);
//        operation(operation_values[pow][left_ind], operation_values[pow][right_ind - len + 1]);
        auto first = operation_values[pow][left_ind];
        auto second = operation_values[pow][right_ind - len + 1];
        if (first.first != second.first) {
            return operation(first, second);
        } else {
            return {first.first, operation_values[pow][left_ind].second
                         + operation_values[pow][right_ind - len + 1].second
                         - GetIntersection(pow, left_ind, right_ind, len, first.first)};
        }
    }
};


int main() {
    uint32_t cnt_solders;
    std::cin >> cnt_solders;
    std::vector<std::pair<uint32_t, uint32_t>> awards(cnt_solders);
    for (uint32_t i =0; i < cnt_solders; ++i) {
        std::cin >> awards[i].first;
        awards[i].second = 1;
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