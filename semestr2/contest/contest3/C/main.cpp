#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int n;
    std::cin >> n;
    std::vector<int> v;
    v.reserve(n);
    for (int i = 0; i < n; ++i) {
        int x;
        std::cin >> x;
        v.push_back(x);
    }
    int x;
    std::cin >> x;
    std::cout << std::count(v.begin(), v.end(), x);
    return 0;
}