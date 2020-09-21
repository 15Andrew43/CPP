#include <iostream>
#include <vector>

template <typename Iterator>
void hoarasort(Iterator begin, Iterator end) {
    if (begin >= end) {
        return;
    }
    Iterator i = begin;
    Iterator j = std::prev(end);
    typename std::iterator_traits<Iterator>::value_type x = *(begin + (end - begin) / 2);

    do {
        while (*i < x) {
            i++;
        }
        while (*j > x) {
            j--;
        }

        if (i <= j) {
            if (i < j) {
                std::swap(*i, *j);
            }
            ++i;
            --j;
        }
    } while (i <= j);

    if (i < end-1) {
        hoarasort(i, end);
    }
    if (begin < j) {
        hoarasort(begin, j + 1);
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
    hoarasort(v.begin(), v.end());
    for (auto i: v) {
        std::cout << i << ' ';
    }
}