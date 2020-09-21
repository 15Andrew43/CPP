#include <iostream>
#include <vector>
#include <string>
#include <tuple>

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

bool Comp(const std::tuple<std::string, int>& first, const std::tuple<std::string, int>& second) {
        return std::get<1>(first) > std::get<1>(second);
}

int main() {
    int n;
    std::cin >> n;
    std::vector<std::tuple<std::string, int>> abiturs;

    for (int i = 0; i < n; ++i) {
        std::string name;
        std::string surname;
        int info_points, math_points, rus_points;
        std::cin >> surname >> name >> info_points >> math_points >> rus_points;
        abiturs.push_back(std::make_tuple(surname + ' ' + name, info_points + math_points + rus_points));
    }

    for (int i = 0; i < n; ++i) {
        std::cout << std::get<0>(abiturs[i]) << ' ' << std::get<1>(abiturs[i]) << '\n';
    }

    MergeSortImpl(abiturs.begin(), abiturs.end(), Comp);


    for (int i = 0; i < n; ++i) {
        std::cout << std::get<0>(abiturs[i]) << '\n';
    }

    return 0;
}