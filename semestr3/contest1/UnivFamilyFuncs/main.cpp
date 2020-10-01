#include <iostream>
#include <unordered_set>
#include <string>
#include <random>
#include <utility>

class Hash {
    size_t a;
    size_t b;
    const size_t p = 433494437;
    const size_t m = 1000000;
public:
    Hash(): a(rand() % 1000 + 1), b(rand() % 1000 + 1) {}
    size_t operator()(size_t x) const {
        return ( (a * x + b) % p ) % m;
    }
};

template <typename T, typename Hash>
class DataBase {
    std::unordered_set<T, Hash> set;
public:
    void Add(const T& value) {
        set.insert(value);
    }
    void Delete(const T& value) {
        typename std::unordered_set<T, Hash>::iterator it = set.find(value);
        if (it != set.end()) {
            set.erase(it);
        }
    }
    std::string Contain(const T& value) {
        if (set.find(value) != set.end()) {
            return "YES";
        }
        return "NO";
    }
};

int main() {
    int n;
    std::cin >> n;
    DataBase<size_t, Hash> data;
    for (int i = 0; i < n; ++i) {
        char comand;
        size_t value;
        std::cin >> comand >> value;
        switch(comand) {
            case '+':
                data.Add(value);
                break;
            case '-':
                data.Delete(value);
                break;
            case '?':
                std::cout << data.Contain(value) << '\n';
                break;
        }
    }
    return 0;
}
