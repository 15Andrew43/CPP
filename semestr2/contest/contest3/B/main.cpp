#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int n;
    std::cin >> n;
    std::vector<size_t > v;
    v.reserve(n);
    for (int i = 0; i < n; ++i) {
        size_t colour;
        std::cin >> colour;
        v.push_back(colour);
    }
    int m;
    std::cin >> m;
    for (int i = 0; i < m; ++i) {
        size_t colour;
        std::cin >> colour;
        std::cout << std::upper_bound(v.begin(), v.end(), colour) - std::lower_bound(v.begin(), v.end(), colour) << '\n';
    }
    return 0;
}