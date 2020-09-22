#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <tuple>
#include <iterator>



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
        Iterator n = std::lower_bound(b_beg, b_end, *m, cmp);
        std::rotate(m, b_beg, n);
        a_end = m + (n - b_beg);
//        a_end = std::rotate(m, b_beg, n);
        b_beg = a_end;
        InplaceMerge(a_beg, m, a_end, cmp);
        InplaceMerge(b_beg, n, b_end, cmp);
    } else if (size_a < size_b) {
        Iterator m = b_beg + size_b/2;
        Iterator n = std::upper_bound(a_beg, a_end, *m, cmp);
        std::rotate(n, b_beg, m);
        a_end = n + (m - b_beg);
//        a_end = std::rotate(n, b_beg, m);
        b_beg = a_end;
        InplaceMerge(a_beg, n, a_end, cmp);
        InplaceMerge(b_beg, m, b_end, cmp);
    }
}

template <typename Iterator, typename Cmp = std::less<typename std::iterator_traits<Iterator>::value_type>>
void InplaceMergeSort(Iterator beg, Iterator end, Cmp cmp = Cmp()) {
    size_t size = end - beg;
    if (size <= 1) {
        return;
    }
    InplaceMergeSort(beg, beg + size/2, cmp);
    InplaceMergeSort(beg + size/2, end, cmp);

    InplaceMerge(beg, beg + size/2, end, cmp);
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

//    for (int i = 0; i < n; ++i) {
//        std::cout << std::get<0>(abiturs[i]) << ' ' << std::get<1>(abiturs[i]) << '\n';
//    }

    InplaceMergeSort(abiturs.begin(), abiturs.end(), Comp);


//    for (int i = n-1; i >= 0; --i) {
//        std::cout << std::get<0>(abiturs[i]) << '\n';
//    }
    for (int i = 0; i < n; ++i) {
        std::cout << std::get<0>(abiturs[i]) << '\n';
    }
    return 0;
}