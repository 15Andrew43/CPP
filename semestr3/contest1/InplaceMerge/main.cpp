#include <iostream>
#include <vector>
#include <algorithm>

template <typename Iterator, typename Cmp = std::less<typename std::iterator_traits<Iterator>::value_type>>
void InplaceMerge(Iterator a_beg, Iterator b_beg, Iterator b_end, Cmp cmp = Cmp()) {
    Iterator a_end = b_beg;

    size_t size_a = a_end - a_beg;
    size_t size_b = b_end - b_beg;
    if (size_a == 0 || size_b == 0) {
        return;
    } else if (size_a == 1 && size_b == 1) {
        if (cmp(*b_beg, *a_beg)) {
            std::swap(*a_beg, *b_beg);
        }
        return;
    }
    if (size_a >= size_b) {
        Iterator m = a_beg + size_a/2;
        Iterator n = std::lower_bound(b_beg, b_end, *m);
//        std::rotate(m, b_beg, n);
//        a_end = m + (n - b_beg);
        a_end = std::rotate(m, b_beg, n);;
        b_beg = a_end;
        InplaceMerge(a_beg, m, a_end);
        InplaceMerge(b_beg, n, b_end);
    } else if (size_a < size_b) {
        Iterator m = b_beg + size_b/2;
        Iterator n = std::upper_bound(a_beg, a_end, *m);
//        std::rotate(n, b_beg, m);
//        a_end = n + (m - b_beg);
        a_end = std::rotate(n, b_beg, m);
        b_beg = a_end;
        InplaceMerge(a_beg, n, a_end);
        InplaceMerge(b_beg, m, b_end);
    }
}


int main() {
    int n;
    std::cin >> n;
    std::vector<int> v;
    for (int i = 0; i < n; ++i) {
        int d;
        std::cin >> d;
        v.push_back(d);
    }
    int m;
    std::cin >> m;
    for (int i = 0; i < m; ++i) {
        int d;
        std::cin >> d;
        v.push_back(d);
    }

    auto a_beg = v.begin();
    auto a_end = v.begin() + n;
    auto b_beg = a_end;
    auto b_end = v.end();
    InplaceMerge(a_beg, b_beg, b_end);

    for (auto x: v) {
        std::cout << x << ' ';
    }
    return 0;
}