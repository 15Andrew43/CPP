#include <iostream>
#include <vector>

std::vector<int> v;

template <typename Iterator, typename Cmp = std::less<typename std::iterator_traits<Iterator>::value_type>>
void InplaceMerge(Iterator a_beg, Iterator a_end, Iterator b_beg, Iterator b_end, Cmp cmp = Cmp()) {
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
        std::rotate(m, b_beg, n);
        a_end = m + (n - b_beg);
        b_beg = a_end;
        InplaceMerge(a_beg, m, m, a_end);
        InplaceMerge(b_beg, n, n, b_end);
    } else if (size_a < size_b) {
        Iterator m = b_beg + size_b/2;
        Iterator n = std::lower_bound(a_beg, a_end, *m);
        std::rotate(n, b_beg, m);
        a_end = n + (m - b_beg);
        b_beg = a_end;
        InplaceMerge(a_beg, n, n, a_end);
        InplaceMerge(b_beg, m, m, b_end);
    }
}


int main() {
    v = {1, 5, 6, 8, 12, 14, 9, 11, 12};
    for (auto i = 0; i < v.size(); ++i) {
        std::cout << v[i] << ' ';
    }
    std::cout << '\n';
//    for (auto i = n; i < n+m; ++i) {
//        cout << v[i] << ' ';
//    }
//    cout << '\n';

    auto a_beg = v.begin();
    auto a_end  = v.begin() + 6;
    auto b_beg = a_end;
    auto b_end = v.end();
    InplaceMerge(a_beg, a_end, b_beg, b_end);

    for (auto x: v) {
        std::cout << x << ' ';
    }
    std::cout << '\n';

    std::cout << "Hello, World!" << std::endl;
    return 0;
}