#include <iostream>
#include <vector>
#include <iterator>

template <typename Iterator, typename IteratorC, typename Cmp = std::less<typename std::iterator_traits<Iterator>::value_type>>
IteratorC Merge(Iterator a_beg, Iterator a_end, Iterator b_beg, Iterator b_end, IteratorC c, Cmp cmp = Cmp()) {
    while (a_beg != a_end && b_beg != b_end) {
        if (!cmp(*b_beg, *a_beg)) { // A <= B
            *c = *a_beg; // = std::move(*a_beg)
            ++c;
            ++a_beg;
        } else {
            *c = *b_beg;
            ++c;
            ++b_beg;
        }
    }
    c = std::copy(a_beg, a_end, c);
    c = std::copy(b_beg, b_end, c);
    return c;
}


int main() {
    int n;
    std::cin >> n;
    std::vector<long long int> v1;
    for (int i = 0; i < n; ++i) {
        long long int d;
        std::cin >> d;
        v1.push_back(d);
    }
    int m;
    std::cin >> m;
    std::vector<long long int> v2;
    for (int i = 0; i < m; ++i) {
        long long int d;
        std::cin >> d;
        v2.push_back(d);
    }
//    std::vector<long long int> res;
//    res.resize(n+m);
//    Merge(v1.begin(), v1.end(), v2.begin(), v2.end(), res.begin());
    Merge(v1.begin(), v1.end(), v2.begin(), v2.end(), std::ostream_iterator<int>(std::cout, " "));
//    for (auto i: res) {
//        std::cout << i << ' ';
//    }
    return 0;
}