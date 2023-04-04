#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>

struct Word {
    std::string name_;
    int cnt_;
};

bool comp(const Word& lhs, const Word& rhs) {
    if (lhs.cnt_ > rhs.cnt_) {
        return true;
    } else if (lhs.cnt_ < rhs.cnt_) {
        return false;
    }
    if (lhs.name_ < rhs.name_) {
        return true;
    } else if (lhs.name_ > rhs.name_) {
        return false;
    }
    return false;
}


int main() {
    std::unordered_map<std::string, int> words;
    std::string name;
    while (std::cin >> name) {
        words[name] += 1;
    }

//    std::cout << "bruh\n";

    std::vector<Word> v;
    v.reserve(words.size());
    for (const auto& [key, value] : words) {
//        std::cout << key << " : " << value << '\n';
        v.push_back({key, value});
    }

    std::sort(v.begin(), v.end(), comp);

    for (const auto& [name, cnt] : v) {
        std::cout << name << '\n';
    }
    return 0;
}