#include <iostream>
#include <vector>

struct Boarders {
    size_t left;
    size_t right;
    long long int sum;
};

std::vector<long long int> BuildPartialSumArray(size_t cnt_solders, const std::vector<long long int>& awards) {
    std::vector<long long int> partial_sum_array(cnt_solders+1);
    partial_sum_array[0] = 0;
    for (size_t i = 1; i < cnt_solders + 1; ++i) {
        partial_sum_array[i] = awards[i-1] + partial_sum_array[i-1];
    }
    return partial_sum_array;
}

void Print(std::vector<long long int>& v) {
    for (auto& x: v) {
        std::cout << x << ' ';
    }
    std::cout << '\n';
}

Boarders GetMaxSumInRow(const std::vector<long long int>& awards) {
    auto partial_sum_array = BuildPartialSumArray(awards.size(), awards);
    Print(partial_sum_array);
    size_t ind_min = 1, ind_max = 1;
    long long int max = -1000000000;
    long long int min = 1000000000;
    long long int sum = -1000000000;
    for (size_t i = 0; i < partial_sum_array.size(); ++i) {
        if (partial_sum_array[i] < min) {
            min = partial_sum_array[i];
            ind_min = i;
            max = -1000000000;
        }
        if (partial_sum_array[i] > max) {
            max = partial_sum_array[i];
            ind_max = i;
            if (i == 0) {
                continue;
            }
            if (ind_max != ind_min && max - min > sum) {
                sum = max - min;
            } else if (ind_max == ind_min && min > sum) {
                sum = partial_sum_array[i] - partial_sum_array[i-1];
            }
        }
    }
    max = -1000000000;
    min = 1000000000;
    for (size_t i = 0; i < partial_sum_array.size(); ++i) {
        if (partial_sum_array[i] < min) {
            min = partial_sum_array[i];
            ind_min = i;
            max = -1000000000;
        }
        if (partial_sum_array[i] > max) {
            max = partial_sum_array[i];
            ind_max = i;
            if (ind_max != ind_min && max - min == sum) {
                break;
            } else if (ind_max == ind_min && partial_sum_array[i] - partial_sum_array[i-1] == sum) {
                break;
            }
        }
    }
    return {ind_min, ind_max, sum};
}

int main() {
    size_t cnt_solders;
    std::cin >> cnt_solders;
    std::vector<long long int> awards;
    for (size_t i = 0; i < cnt_solders; ++i) {
        long long int award;
        std::cin >> award;
        awards.push_back(award);
    }


    auto [left, right, sum] = GetMaxSumInRow(awards);
    if (left + 1 < right) {
        std::cout << left + 1 << ' ' << right << ' ' << sum;
    } else {
        std::cout << right << ' ' << right << ' ' << sum;
    }
    return 0;
}