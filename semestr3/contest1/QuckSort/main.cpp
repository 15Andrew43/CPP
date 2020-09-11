#include <iostream>
#include <vector>

template<typename Iterator>
Iterator RandomizedPartition(Iterator begin, Iterator end) {
    Iterator i = rand() % (end - begin) + begin;
    std::swap(*i, *std::prev(end));
    typename std::iterator_traits<Iterator>::value_type x = *std::prev(end);
    i = std::prev(begin);
    for (Iterator j = begin; j < std::prev(end); ++j) {
        if (*j <= x) {
            ++i;
            std::swap(*i, *j);
        }
    }
    std::swap(*(i+1), *std::prev(end));
    return i+1;
}

template<class Iterator>
void QuickSort(Iterator begin, Iterator end) {
    Iterator pirot;
    if (begin < end) {
        pirot = RandomizedPartition<Iterator>(begin, end);
        QuickSort<Iterator>(begin, pirot);
        QuickSort<Iterator>(pirot+1, end);
    }
}

int main() {
    int n;
    std::cin >> n;
    std::vector<long long int> v;
    for (int i = 0; i < n; ++i) {
        long long int d;
        std::cin >> d;
        v.push_back(d);
    }
    QuickSort(v.begin(), v.end());
    for (auto i: v) {
        std::cout << i << ' ';
    }
    return 0;
}