#include <iostream>
#include <vector>

unsigned int nextRand(uint32_t& cur, uint32_t a, uint32_t b) {
    cur = cur * a + b;
    return cur >> 8;
}

void GiveAwardToPlatoon(uint32_t& cur, uint32_t a, uint32_t b, std::vector<int64_t>& cur_awards) {
    uint32_t left_board_ind, right_board_ind;
    auto add = nextRand(cur, a, b);
    left_board_ind = nextRand(cur, a, b);
    right_board_ind = nextRand(cur, a, b);
    if (left_board_ind > right_board_ind) {
        std::swap(left_board_ind, right_board_ind);
    }
    cur_awards[left_board_ind] += add;
    cur_awards[right_board_ind + 1] -= add;
}

void GetTrueAwards(std::vector<int64_t>& cur_awards) {
    int64_t add = 0;
    for (uint32_t i = 0; i < cur_awards.size(); ++i) {
        add += cur_awards[i];
        cur_awards[i] = add;
    }
}

void BuildPartialSumArray(uint32_t cnt_solders, std::vector<int64_t>& awards) {
    int64_t cur_elem = awards[0];
    int64_t next_cur_elem;
    awards[0] = 0;
    for (uint32_t i = 1; i < cnt_solders + 1; ++i) {
        next_cur_elem = awards[i];
        awards[i] = awards[i - 1] + cur_elem;
        cur_elem = next_cur_elem;
    }
}

uint64_t GetSumInPlatoon(uint32_t& cur, uint32_t a, uint32_t b, std::vector<int64_t>& partial_sum_array) {
    uint32_t left_board_ind, right_board_ind;
    left_board_ind = nextRand(cur, a, b);
    right_board_ind = nextRand(cur, a, b);
    if (left_board_ind > right_board_ind) {
        std::swap(left_board_ind, right_board_ind);
    }
    return partial_sum_array[right_board_ind + 1] - partial_sum_array[left_board_ind];
}

uint32_t GetSumAwardsInRequests(uint32_t cnt_awards, uint32_t cnt_requests, uint32_t a, uint32_t b) {
    const uint32_t cnt_solders = 16777216;
    std::vector<int64_t> awards(cnt_solders + 1, 0);
    uint32_t cur = 0;

    for (uint32_t i = 0; i < cnt_awards; ++i) {
        GiveAwardToPlatoon(cur, a, b, awards);
    }

    GetTrueAwards(awards);
    BuildPartialSumArray(cnt_solders, awards);

    uint64_t sum_awards_in_requests = 0;
    for (uint32_t i = 0; i < cnt_requests; ++i) {
        sum_awards_in_requests += GetSumInPlatoon(cur, a, b, awards);
    }
    return sum_awards_in_requests;
}

int main() {
    uint32_t cnt_awards, cnt_requests;
    uint32_t a, b;
    std::cin >> cnt_awards >> cnt_requests
             >> a >> b;

    std::cout << GetSumAwardsInRequests(cnt_awards, cnt_requests, a, b);
    return 0;
}
