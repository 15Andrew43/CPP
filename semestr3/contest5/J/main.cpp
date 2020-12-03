#include <iostream>
#include <vector>

template <class T>
class FenwickTree {
    std::vector<std::vector<T>> tree;
public:
    FenwickTree(int len_x, int len_y)
            : tree(len_x, std::vector<T>(len_y, 0)) {
    }
    void Update(int ind_x, int ind_y, T delta) {
        for (int x = ind_x; x < tree.size(); x = (x | (x + 1))) {
            for (int y = ind_y; y < tree[0].size(); y = (y | (y + 1))) {
                tree[x][y] += delta;
            }
        }
    }
    T Query(int x0, int y0) {
        T res = 0;
        for (int x = x0; x >= 0; x = ((x & (x + 1)) - 1)) {
            for (int y = y0; y >= 0; y = ((y & (y + 1)) - 1)) {
                res += tree[x][y];
            }
        }
        return res;
    }
    T Sum(int x0, int y0, int x1, int y1) {
        T res00 = Query(x0 - 1, y0 - 1);
        T res11 = Query(x1, y1);
        T res01 = Query(x0 - 1, y1);
        T res10 = Query(x1, y0 - 1);
        return res11 - res01 - res10 + res00;
    }
};

int main() {
    int len_x, len_y;
    std::cin >> len_x >> len_y;
    std::vector<std::vector<int>> awards(len_x, std::vector<int>(len_y));

    FenwickTree<int> tree(len_x, len_y);

    int cnt_requests;
    std::cin >> cnt_requests;

    for (int i = 0; i < cnt_requests; ++i) {
        short operation;
        std::cin >> operation;
        if (operation == 1) {
            int x, y;
            int64_t delta;
            std::cin >> x >> y >> delta;
            tree.Update(x - 1, y - 1, delta);
        } else if (operation == 2) {
            int x0, y0, x1, y1;
            std::cin >> x0 >> y0 >> x1 >> y1;
            std::cout << tree.Sum(x0-1, y0-1, x1-1, y1-1) << '\n';
        }
    }

    return 0;
}