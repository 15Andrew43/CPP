#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <utility>


std::vector<int> GetPossibleNumbers(int N) {
    std::vector<int> possible_numbers;
    if (N / 1000 != 9) {
        possible_numbers.push_back((N / 1000 + 1) * 1000 + N % 1000);
    }
    if (N % 10 != 1) {
        possible_numbers.push_back(N - 1);
    }
    int rotate_left = N % 1000 * 10 + N / 1000;
    int rotate_right = N / 10 + N % 10 * 1000;
    possible_numbers.push_back(rotate_left);
    possible_numbers.push_back(rotate_right);
    return possible_numbers;
}
std::vector<int> GetShortestPath(int start, int end) {
    std::queue<int> q;
    std::unordered_map<int, int> distance;
    std::unordered_map<int, int> parent;
    distance[start] = 0;
    q.push(start);

    while (!q.empty()) {
        int v = q.front();
        q.pop();
        std::vector<int> possible_numbers = GetPossibleNumbers(v);
        for (auto u: possible_numbers) {
            if (distance.find(u) == distance.end()) {
                q.push(u);
                distance[u] = distance[v] + 1;
                parent[u] = v;
            }
        }
    }

    std::vector<int> path;
    while (end != start) {
        path.push_back(end);
        end = parent[end];
    }
    path.push_back(start);

    return {path.rbegin(), path.rend()};
}


int main() {
//    auto v = GetPossibleNumbers(1234);
//    for (auto x: v) {
//        std::cout << x << ' ';
//    }

    int start, end;
    std::cin >> start >> end;

    std::vector<int> path  = GetShortestPath(start, end);
    std::cout << path.size() << '\n';
    for (auto x: path) {
        std::cout << x << '\n';
    }
    return 0;
}
