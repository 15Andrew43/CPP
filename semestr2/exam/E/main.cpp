#include <iostream>
#include <cmath>
#include <vector>

struct Point {
    int x_;
    int y_;
};


size_t GetDist(const Point& lhs, const Point& rhs) {
    return (lhs.x_ - rhs.x_)*(lhs.x_ - rhs.x_) + (lhs.y_ - rhs.y_)*(lhs.y_ - rhs.y_);
}

size_t C_n_2(size_t n) {
    return n * (n-1) / 2;
}

int main() {
    int n;
    std::cin >> n;

    std::vector<Point> v;
    v.reserve(n);

    for (int i = 0; i < n; ++i) {
        Point p;
        std::cin >> p.x_ >> p.y_;
        v.push_back(p);
    }

    size_t answer = 0;

    for (int i = 0; i < n - 1; ++i) {
        int cnt = 0;
        for (int j = i; j < n; ++j) {
            size_t dist = GetDist(v[i], v[j]);
            for (int k = 0; k < )
            if (dist == GetDist(v[i], v[j])) {
                ++cnt;
            }
        }
        answer += C_n_2(cnt);
    }

    std::cout << answer;

    return 0;
}