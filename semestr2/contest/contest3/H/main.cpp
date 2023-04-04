#include <iostream>
#include <unordered_map>
#include <exception>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    std::cin >> n;
    std::unordered_map<std::string, int> bank;
    int operation;
    for (int i = 0; i < n; ++i) {
        std::string name;
        std::cin >> operation >> name;
        if (operation == 1) {
            int money;
            std::cin >> money;
            bank[name] += money;
        } else if (operation == 2) {
            try {
                std::cout << bank.at(name) << '\n';
            } catch (std::exception) {
                std::cout << "ERROR\n";
            }
        }
    }
    return 0;
}