#include <iostream>
#include <unordered_map>
#include <exception>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    std::cin >> n;
    std::unordered_map<std::string, std::string> map;
    map.reserve(n);
    for (int i = 0; i < n; ++i) {
        std::string name1, name2;
        std::cin >> name1 >> name2;
        map[name1] = name2;
        map[name2] = name1;
    }

    int q;
    std::cin >> q;
    for (int i = 0; i < q; ++i) {
        std::string name;
        std::cin >> name;
        std::cout << map.at(name) << '\n';
    }
    return 0;
}