#include <iostream>
#include <vector>

struct Board {
    long long int sum;
    long long int left;
    long long int right;
};

std::vector<long long int> BuildPartialSumArray(long long int cnt_solders, std::vector<Board>& row) {
    std::vector<long long int> partial_sum_array(cnt_solders+1);
    partial_sum_array[0] = 0;
    for (long long int i = 1; i < cnt_solders + 1; ++i) {
        long long int award;
        std::cin >> award;
        row.push_back({award, i-1, i-1});
        partial_sum_array[i] = award + partial_sum_array[i-1];
    }
    return partial_sum_array;
}

long long int GetNextPow2(long long int cnt_solders) {
    long long int n = 1;
    while (n < cnt_solders) {
        n *= 2;
    }
    return n;
}

long long int Left(long long int i) {
    return 2 * i + 1;
}
long long int Right(long long int i) {
    return 2 * i + 2;
}
long long int Parent(long long int i) {
    return (i-1) / 2;
}

long long int GetRightIndex(long long int ind, long long int next_pow2) {
    return ind + 2 - next_pow2;
}
//long long int GetNotRight(long long int ind, long long int next_pow2) {
//    return ind - 1 + next_pow2;
//}

Board GetMaxBoard(const std::vector<long long int>& partial_sum_array, const std::vector<Board>& tree_max_sum_in_row, long long int left, long long int right, long long int next_pow2) {
    const Board& left_board = tree_max_sum_in_row[left];
    const Board& right_board = tree_max_sum_in_row[right];
    long long int sum_between = partial_sum_array[right_board.left] - partial_sum_array[left_board.right+1];
//    std::cout << "between " << sum_between << '\n';
//    std::cout << "left_bpard : " << left_board.left << ' ' << left_board.right << ' ' <<  left_board.sum << '\n';
//    std::cout << "right_bpard : " << right_board.left << ' ' << right_board.right << ' ' << right_board.sum << '\n';
    long long int all_sum = sum_between + left_board.sum + right_board.sum;
    if (all_sum > left_board.sum && all_sum > right_board.sum) { // ?????????
        return {all_sum, left_board.left, right_board.right};
    } else if (left_board.sum >= right_board.sum) { // ???????
        return left_board;
    } else if (left_board.sum < right_board.sum) { // ???????
        return right_board;
    }
}

void Print(std::vector<Board>& v) {
    for (long long int i = 0; i < v.size(); ++i) {
        std::cout << "    ind: " << i <<  ", l: " << v[i].left << ", " << "r: " << v[i].right << ", sum= " << v[i].sum << "; ";
    }
    std::cout << '\n';
}
void Print(std::vector<long long int>& v) {
    for (auto& x: v) {
        std::cout << x << ' ';
    }
    std::cout << '\n';
}

Board GetMaxSumRow(long long int cnt_solders) {
    std::vector<Board> row;
    auto partial_sum_array = BuildPartialSumArray(cnt_solders, row);
    long long int next_pow2 = GetNextPow2(cnt_solders);
    long long int delta_to_pow2 = next_pow2 - cnt_solders;
    long long int sum_row = partial_sum_array.back();
    for (long long int i = 0; i < delta_to_pow2; ++i) {
        partial_sum_array.push_back(sum_row);
        row.push_back({0, cnt_solders + i, cnt_solders+ + i});
    }

    std::vector<Board> tree_max_sum_in_row(2*next_pow2 - 1);
    std::copy(row.begin(), row.end(), tree_max_sum_in_row.begin() + next_pow2-1);

    std::cout << "partia l sum\n";
    Print(partial_sum_array);
    std::cout << "row\n";
    Print(row);
    std::cout << "tree max sum row\n";
    Print(tree_max_sum_in_row);

    long long int ind = next_pow2 - 1;
    do {
        ind = Parent(ind);
        for (long long int i = ind; i < ind * 2 + 1; ++i) {
            tree_max_sum_in_row[i] = GetMaxBoard(partial_sum_array, tree_max_sum_in_row, Left(i), Right(i), next_pow2);
        }
        std::cout << "\n\ntree max sum row\n";
        Print(tree_max_sum_in_row);
    } while (ind);
    return tree_max_sum_in_row[0];
}

int main() {
    long long int cnt_solders;
    std::cin >> cnt_solders;

    auto board = GetMaxSumRow(cnt_solders);
    std::cout << board.left + 1 << ' ' <<  board.right + 1 << ' ' << board.sum;
    return 0;
}