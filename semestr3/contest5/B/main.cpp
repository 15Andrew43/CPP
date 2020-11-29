#include <iostream>
#include <vector>

struct Boarders {
    size_t left;
    size_t right;
    int sum;
};

std::vector<int> BuildPartialSumArray(size_t cnt_solders, const std::vector<int>& awards) {
    std::vector<int> partial_sum_array(cnt_solders+1);
    partial_sum_array[0] = 0;
    for (size_t i = 1; i < cnt_solders + 1; ++i) {
        partial_sum_array[i] = awards[i-1] + partial_sum_array[i-1];
    }
    return partial_sum_array;
}

Boarders GetMaxSumInRow(const std::vector<int>& awards) {
    auto partial_sum_array = BuildPartialSumArray(awards.size(), awards);
    int sum = -1000000000;
    size_t left_ind, right_ind;
    int cur_sum;
    int max = -1000000000;
    int min = 1000000000;
    size_t cur_left_ind, cur_right_ind;
    for (int i = 0; i < partial_sum_array.size() - 1; ++i) {
        if (partial_sum_array[i] < min) {
            min = partial_sum_array[i];
            cur_left_ind = i;
            max = partial_sum_array[i + 1];
            cur_right_ind = i + 1;
        }
        int j = i + 1;
        while (j < partial_sum_array.size() && partial_sum_array[j] >= min) {
            if (partial_sum_array[j] > max) {
                max = partial_sum_array[j];
                cur_right_ind = j;
            }
            ++j;
        }
        i = j - 1;
        cur_sum = max - min;
        if (cur_sum > sum) {
            sum = cur_sum;
            left_ind = cur_left_ind;
            right_ind = cur_right_ind;
        }
    }
    return {left_ind, right_ind, sum};
}

int main() {
    size_t cnt_solders;
    std::cin >> cnt_solders;
    std::vector<int> awards;
    for (size_t i = 0; i < cnt_solders; ++i) {
        int award;
        std::cin >> award;
        awards.push_back(award);
    }


    auto [left_ind, right_ind, sum] = GetMaxSumInRow(awards);

    if (left_ind + 1 != right_ind) {
        std::cout << left_ind + 1 << ' ' << right_ind << ' ' << sum;
    } else {
        std::cout << right_ind << ' ' << right_ind << ' ' << sum;
    }
    return 0;
}