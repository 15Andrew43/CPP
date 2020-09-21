#include <iostream>
#include <vector>
#include <algorithm>
//#include <iterator>


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

template <typename Iterator, typename Cmp = std::less<typename std::iterator_traits<Iterator>::value_type>>
void MergeSort(Iterator beg, Iterator end, Cmp cmp = Cmp()) {
    size_t size = end - beg;
    if (size == 1) {
        return;
    }
    MergeSort(beg, beg + size/2, cmp);
    MergeSort(beg + size/2, end, cmp);

    InplaceMerge(beg, beg + size/2, beg + size/2, end, cmp);
}


int main() {
    int n=10;
    std::vector<int> v;
    for (int i = 0; i < n; ++i) {
        int d = rand() % 20;
        v.push_back(d);
    }
    for (auto i: v) {
        std::cout << i << ' ';
    }
    std::cout << '\n';

    MergeSort(v.begin(), v.end());

    for (auto i: v) {
        std::cout << i << ' ';
    }

    return 0;
}