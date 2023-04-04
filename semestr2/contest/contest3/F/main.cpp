#include <iostream>
#include <set>


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    const size_t kModule = 1000000000;
    size_t n;
    std::cin >> n;
    std::set<size_t> Set;
    size_t res;
    bool after_question = false;
    for (size_t j = 0; j < n; ++j) {
        char operation;
        size_t elem;
        std::cin >> operation >> elem;
        if (after_question && operation == '+') {
            Set.insert((elem + res) % kModule);
            after_question = false;
        } else if (operation == '+') {
            Set.insert(elem);
        } else {
            auto it = Set.lower_bound(elem);
            if (it != Set.end()) {
                res = *it;
                std::cout << res << '\n';
            } else {
                res = 0;
                std::cout << -1 << '\n';
            }
            after_question = true;
        }
    }
    return 0;
}