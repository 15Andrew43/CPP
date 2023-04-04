#include <iostream>
#include <queue>

using T = int;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    const double percent = 0.05;
    int n;
    std::cin >> n;
    std::priority_queue<T, std::vector<T>, std::greater<T>> numbers;
    double fpmi_coin = 0;
    for (int i = 0; i < n; ++i) {
        int m;
        std::cin >> m;
        numbers.push(m);
    }

    while (numbers.size() > 1) {
        int min_number = numbers.top();
        numbers.pop();
        int before_min_number = numbers.top();
        numbers.pop();
        fpmi_coin += (min_number + before_min_number) * percent;
        numbers.push(min_number + before_min_number);
    }

    std::cout << fpmi_coin;
    return 0;
}