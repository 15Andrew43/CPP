#include <iostream>
#include <vector>

template <typename Iterator, typename Cmp = std::less<typename std::iterator_traits<Iterator>::value_type>>
Iterator Merge(Iterator A1, Iterator A2, Iterator B1, Iterator B2, Iterator C, Cmp cmp = Cmp()) {
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
    std::vector<long long int> res;
    res.resize(n+m);
    Merge(v1.begin(), v1.end(), v2.begin(), v2.end(), res.begin());
    for (auto i: res) {
        std::cout << i << ' ';
    }
    return 0;
}