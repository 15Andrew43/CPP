#include <iostream>
#include <vector>
#include <iomanip>

struct Platoon {
    uint32_t left_ind;
    uint32_t right_ind;
    uint32_t min_hight;
};

std::pair<uint32_t, uint32_t>GetLowerPow2(uint32_t n) {
    uint32_t k = 0;
    uint32_t res = 1;
    while (res * 2 < n) {
        res *= 2;
        ++k;
    }
    return {k, res};
}

template <class T>
class SparseTable {
    std::vector<std::vector<T>> min_values;
public:
    SparseTable(std::vector<T>&& values) : min_values(1) {
        auto cnt_solders = values.size();
        min_values[0] = values;
        auto pow = GetLowerPow2(values.size()).first;
        uint32_t cur_len = 1;
        for (uint32_t i = 1; i < pow + 1; ++i) {
            std::vector<uint32_t> min_values_pow(cnt_solders);
            for (uint32_t j = 0; j < cnt_solders - cur_len; ++j) {
                min_values_pow[j] = std::min(min_values.back()[j], min_values.back()[j + cur_len]);
            }
            min_values.push_back(min_values_pow);
            cur_len *= 2;
        }
    }
    T operator()(uint32_t left_ind, uint32_t right_ind) {
        auto [pow, len] = GetLowerPow2(right_ind - left_ind + 1);
        return std::min(min_values[pow][left_ind], min_values[pow][right_ind - len + 1]);
    }
};


uint32_t NextHight(uint32_t cur_hight) {
    return (23 * cur_hight + 21563) % 16714589;
}
uint32_t NextLeftInd(uint32_t cur_left_ind, uint32_t cur_answer, uint32_t ind, uint32_t cnt_solders) {
    return (17 * cur_left_ind + 751 + cur_answer + 2 * ind) % cnt_solders + 1;
}
uint32_t NextRightInd(uint32_t cur_right_ind, uint32_t cur_answer, uint32_t ind, uint32_t cnt_solders) {
    return (13 * cur_right_ind + 593 + cur_answer + 5 * ind) % cnt_solders + 1;
}


std::vector<uint32_t> GetHights(uint32_t cnt_solders, uint32_t first_height) {
    std::vector<uint32_t> hights(cnt_solders);
    hights[0] = first_height;
    for (uint32_t i = 1; i < cnt_solders; ++i) {
        hights[i] = NextHight(hights[i-1]);
    }
    return hights;
}



Platoon DoRequests(uint32_t cnt_solders, uint32_t cnt_requests, uint32_t first_height, uint32_t left_ind, uint32_t right_ind) {
    auto hights = GetHights(cnt_solders, first_height);
    SparseTable<uint32_t> sparse_table(std::move(hights));
    auto min = sparse_table(std::min(left_ind, right_ind) - 1, std::max(left_ind, right_ind) - 1);
    for (uint32_t i = 1; i < cnt_requests; ++i) {
        left_ind = NextLeftInd(left_ind, min, i, cnt_solders);
        right_ind = NextRightInd(right_ind, min, i, cnt_solders);
        min = sparse_table(std::min(left_ind, right_ind) - 1, std::max(left_ind, right_ind) - 1);
    }
    return {left_ind, right_ind, min};
}


int main() {
    uint32_t cnt_solders, cnt_requests, first_height;
    std::cin >> cnt_solders >> cnt_requests >> first_height;
    uint32_t left_ind, right_ind;
    std::cin >> left_ind >> right_ind;
    auto [left, right, ans] = DoRequests(cnt_solders, cnt_requests, first_height, left_ind, right_ind);
    std::cout << left << ' ' << right << ' ' << ans;
    return 0;
}