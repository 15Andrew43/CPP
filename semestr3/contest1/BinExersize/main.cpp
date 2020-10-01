#include <iostream>
#include <vector>
#include <algorithm>

bool Check(size_t delta, int student_cnt, const std::vector<size_t>& coordinates) {
    int setStudents = 1;
    auto start = coordinates.begin();
    while (setStudents < student_cnt) {
        auto iter = std::lower_bound(start, coordinates.end(), delta + *start);
        if (iter == coordinates.end()) {
            return false;
        }
        ++setStudents;
        start = iter;
    }
    return true;
}

size_t getMaxMinDist(int student_cnt, const std::vector<size_t>& coordinates) {
    int size = coordinates.size();
    size_t delta = coordinates[size-1] - coordinates[0];
    size_t l = 0;
    size_t r = delta+1;
    while (r - l > 1) {
        size_t m = (l + r) / 2;
        if (Check(m, student_cnt, coordinates)) {
            l = m;
        } else {
            r = m;
        }
    }
    return l;
}

int main() {
    int n;
    std::cin >> n;
    int k;
    std::cin >> k;
    std::vector<size_t> coordinates(n);
    for (int i = 0; i < n; ++i) {
        size_t x;
        std::cin >> x;
        coordinates[i] = x;
    }
    std::cout << getMaxMinDist(k, coordinates);
    return 0;
}
