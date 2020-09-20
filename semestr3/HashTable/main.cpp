#include <iostream>
#include <vector>
#include <list>

template<class T, class Hash = std::hash<T>, class Equal = std::equal<T>>
class HashTable {
    std::vector<std::list<T>> buckets_;
    size_t size_;
    Hash hash_;
    Equal eq_; // x == y <=> eq(x, y)
    Insert();
    Erase();
    bool Find();
};


int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}