#include <iostream>
#include <vector>
#include <string>
#include <tuple>

template <typename Iterator, typename InsertIterator, typename Cmp = std::less<typename std::iterator_traits<Iterator>::value_type>>
InsertIterator Merge(Iterator A1, Iterator A2, Iterator B1, Iterator B2, InsertIterator C, Cmp cmp = Cmp()) {
    while (A1 != A2 && B1 != B2) {
        if (!cmp(*B1, *A1)) { // A <= B
            *C = *A1; // = std::move(*A1)
            ++C;
            ++A1;
        } else {
            *C = *B1;
            ++C;
            ++B1;
        }
    }
    C = std::copy(A1, A2, C);
    C = std::copy(B1, B2, C);
    return C;
}

template <typename Iterator, typename Cmp = std::less<typename std::iterator_traits<Iterator>::value_type>>
void MergeSort(Iterator beg, Iterator end, Cmp cmp = Cmp()) {
    if (end - beg == 1) {
        return;
    }
    int size = end - beg;
    std::vector<typename std::iterator_traits<Iterator>::value_type> tmp_buf; // можно сделать глобальным(или на уровень выше)
    tmp_buf.reserve(size); // хочется resize, но вдруг нет конструктора по умолчанию
    MergeSort(beg, beg + size/2, cmp);
    MergeSort(beg + size/2, end, cmp);
    Merge(std::make_move_iterator(beg), std::make_move_iterator(beg + size/2),
          std::make_move_iterator(beg + size/2), std::make_move_iterator(end),
          std::back_inserter(tmp_buf), cmp);
    std::move(tmp_buf.begin(), tmp_buf.end(), beg);
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

    MergeSort(abiturs.begin(), abiturs.end(), Comp);


    for (int i = 0; i < n; ++i) {
        std::cout << std::get<0>(abiturs[i]) << '\n';
    }

    return 0;
}