#include <iostream>
#include <unordered_set>
#include <algorithm>


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::unordered_set<std::string> v;
    std::string str;
    char operation = '0';
    while (operation != '#') {
        std::cin >> operation;
        switch (operation) {
            case '+':
                std::cin >> str;
                v.insert(str);
                break;
            case '-':
                std::cin >> str;
                v.erase(str);
                break;
            case '?':
                std::cin >> str;
                std::cout << (v.count(str) > 0 ? "YES\n" : "NO\n");
                break;
        }
    }
    return 0;
}