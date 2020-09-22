#include <iostream>
#include <vector>
#include <unordered_set>
#include <iterator>
#include <algorithm>

template <typename T, typename IteratorC, typename Cmp = std::less<T>>
IteratorC Merge(std::vector<std::vector<T>>& vec, IteratorC c, Cmp cmp = Cmp()) {
    std::unordered_set<std::tuple<int, typename std::vector<T>::iterator>> iters;
    for (int i = 0; i < vec.size(); ++i) {
        iters.insert(std::make_tuple(i, vec[i].begin()));
    }

    while (!iters.empty()) {
        auto first = iters.begin();
        for (auto it = iters.begin(); it != iters.end(); ++it) {
            if (!cmp(std::get<1>(*it), std::get<1>(*first))) continue;
            std::get<1>(*first) = std::get<1>(*it);
        }
        *c = std::get<1>(*first);
        ++c;
        ++std::get<1>(*first);
        if (std::get<1>(*first) == vec[std::get<0>(*first)].end()) {
            iters.erase(first);
        }
    }
    return c;
}

int main() {
    int k;
    std::cin >> k;
    std::vector<std::vector<int>> vec(k);
    for (int i = 0; i < k; ++i) {
        int n;
        std::cin >> n;
        for (int j = 0; j < n; ++j) {
            int d;
            std::cin >> d;
            vec[i].push_back(d);
        }
    }

    Merge(vec, std::ostream_iterator<int>(std::cout, " "));
    return 0;
}