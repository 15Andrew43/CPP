#include <iostream>
#include <vector>

std::pair<int64_t, int64_t>GetNotLowerPow2(int64_t n) {
    int64_t k = 0;
    int64_t res = 1;
    while (res < n) {
        res *= 2;
        ++k;
    }
    return {k, res};
}


int64_t Left(int64_t number) {
    return number * 2 + 1;
}
int64_t Right(int64_t number) {
    return number * 2 + 2;
}


class SegmentTree {
    int64_t cnt_elements_;

    void Push(int64_t node) {
        promise[Left(node)] += promise[node];
        promise[Right(node)] += promise[node];
        promise[node] = 0;
    }
    void Query(int64_t node, int64_t ind, int64_t left_board, int64_t right_board) {
        if (ind < left_board || ind > right_board) { // no intersection
            return;
        }
        if (ind >= left_board && ind <= right_board) {
            if (node < cnt_elements_ - 1) {
                if (promise[node] != 0) {
                    Push(node);
                }
                Query(Left(node), ind, left_board, left_board + (right_board + 1 - left_board) / 2 - 1);
                Query(Right(node), ind, left_board + (right_board + 1 - left_board) / 2, right_board);
            }
        }
    }
    void UpdatePromise(int64_t node, int64_t left_ind, int64_t right_ind, int64_t value, int64_t left_board, int64_t right_board) {
        if (left_ind > right_board || right_ind < left_board) { // no intersection
            return;
        }
        if (left_ind <= left_board && right_board <= right_ind) { // inside
            promise[node] += value;
        }
        else { // itersection
            if (node < cnt_elements_ - 1) {
                if (promise[node] != 0) {
                    Push(node);
                }
                UpdatePromise(Left(node), left_ind, right_ind, value, left_board,
                        left_board + (right_board + 1 - left_board) / 2 - 1);
                UpdatePromise(Right(node), left_ind, right_ind, value,
                        left_board + (right_board + 1 - left_board) / 2, right_board);
            }
        }
    }
public:
    std::vector<int64_t> promise;

    SegmentTree(std::vector<int64_t>& array) {
        promise = array;
        cnt_elements_ = (array.size() + 1) / 2;
    }

    void Update(int64_t left_ind, int64_t right_ind, int64_t value) {
        UpdatePromise(0, left_ind + cnt_elements_ - 1, right_ind + cnt_elements_ - 1, value, cnt_elements_ - 1, 2 * cnt_elements_ - 2);
    }
    int64_t operator()(int64_t ind) {
        Query(0, ind + (cnt_elements_ - 1), cnt_elements_ - 1, 2 * cnt_elements_ - 2);
        return promise[ind + cnt_elements_ - 1];
    }
};

int main() {
    int64_t cnt_solders;
    std::cin >> cnt_solders;
    int64_t k = GetNotLowerPow2(cnt_solders).second;
    std::vector<int64_t> awards(2 * k - 1, 0);
    for (int64_t i = k - 1; i < k - 1 + cnt_solders; ++i) {
        std::cin >> awards[i];
    }

    SegmentTree tree(awards);

    int64_t cnt_requests;
    std::cin >> cnt_requests;

    for (int64_t i = 0; i < cnt_requests; ++i) {
        char operation;
        std::cin >> operation;
        if (operation == 'g') {
            int64_t ind;
            std::cin >> ind;
            std::cout << tree(ind - 1) << '\n';
        } else if (operation == 'a') {
            int64_t left_ind, right_ind, value;
            std::cin >> left_ind >> right_ind >> value;
            tree.Update(left_ind - 1, right_ind - 1, value);
        }
    }
    return 0;
}