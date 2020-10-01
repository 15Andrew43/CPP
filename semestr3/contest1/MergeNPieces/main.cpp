#include <iostream>
#include <vector>
#include <iterator>
#include <set>
#include <tuple>

template <typename T, typename IteratorC, typename Cmp = std::less<T>>
IteratorC Merge(std::vector<std::vector<T>>& vec, IteratorC c, Cmp cmp = Cmp()) {
    std::set<std::tuple<T, int, typename std::vector<T>::iterator>> set;
    for (int i = 0; i < vec.size(); ++i) {
        set.insert(std::make_tuple(vec[i][0], i, vec[i].begin()));
    }
    while (!set.empty()) {
        *c = std::get<0>(*set.begin());
        ++c;
        int ind = std::get<1>(*set.begin());
        auto iter = std::get<2>(*set.begin());
        set.erase(set.begin());
        if (vec[ind].end() != ++iter) {
            set.insert(std::make_tuple(*iter, ind, iter));
        }
    }
    return c;
}

int main() {
    int k;
    std::cin >> k;
    std::vector<std::vector<int>> vec;
    for (int i = 0; i < k; ++i) {
        int n;
        std::cin >> n;
        std::vector<int> v;
        for (int j = 0; j < n; ++j) {
            int d;
            std::cin >> d;
            v.push_back(d);
        }
        vec.push_back(v);
    }

    Merge(vec, std::ostream_iterator<int>(std::cout, " "));
    return 0;
}