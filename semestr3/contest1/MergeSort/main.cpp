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

template <typename Iterator, typename Cmp = std::less<typename std::iterator_traits<Iterator>::value_type>>
void MergeSort(Iterator beg, Iterator end, Iterator res, Cmp cmp = Cmp()) {
    if (end - beg == 1) {
        return;
    }
    int size = end - beg;
//    std::vector<typename std::iterator_traits<Iterator>::value_type> tmp_buf; // можно сделать глобальным(или на уровень выше)
//    tmp_buf.reserve(size); // хочется resize, но вдруг нет конструктора по умолчанию
    MergeSort(beg, beg + size/2, res, cmp);
    MergeSort(beg + size/2, end, res + size/2, cmp);
    Merge(std::make_move_iterator(beg), std::make_move_iterator(beg + size/2),
          std::make_move_iterator(beg + size/2), std::make_move_iterator(end),
          res, cmp);
//    std::copy(tmp_buf.begin(), tmp_buf.end(), beg);
    std::move(res, res + size, beg);
}
//
template <typename Iterator, typename Cmp = std::less<typename std::iterator_traits<Iterator>::value_type>>
void MergeSortImpl(Iterator beg, Iterator end, Cmp cmp = Cmp()) {
    if (end - beg <= 1) return;
    std::vector<typename std::iterator_traits<Iterator>::value_type> tmp_buf(end - beg);
    MergeSort(beg, end, tmp_buf.begin(), cmp);
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    int n=20;
//    std::cin >> n;
    std::vector<int> v;
    for (int i = 0; i < n; ++i) {
        int d = rand() % 20;
//        std::cin >> d;
        v.push_back(d);
    }
    MergeSortImpl(v.begin(), v.end());

    for (auto i: v) {
        std::cout << i << ' ';
    }

    return 0;
}