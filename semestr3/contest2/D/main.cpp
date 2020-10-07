#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>


std::vector<int> GetPossibleNumbers(int number) {
    std::vector<int> possible_numbers;
    if (number / 1000 != 9) {
        possible_numbers.push_back((number / 1000 + 1) * 1000 + number % 1000);
    }
    if (number % 10 != 1) {
        possible_numbers.push_back(number - 1);
    }
    int rotate_left = number % 1000 * 10 + number / 1000;
    int rotate_right = number / 10 + number % 10 * 1000;
    possible_numbers.push_back(rotate_left);
    possible_numbers.push_back(rotate_right);
    return possible_numbers;
}
std::vector<int> GetShortestPath(int start, int end) {
    std::queue<int> queue;
    std::unordered_map<int, int> distance;
    std::unordered_map<int, int> parent;
    distance[start] = 0;
    queue.push(start);

    while (!queue.empty()) {
        int v = queue.front();
        queue.pop();
        std::vector<int> possible_numbers = GetPossibleNumbers(v);
        for (auto possible_move: possible_numbers) {
            if (distance.find(possible_move) == distance.end()) {
                queue.push(possible_move);
                distance[possible_move] = distance[v] + 1;
                parent[possible_move] = v;
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
    int start, end;
    std::cin >> start >> end;

    std::vector<int> path  = GetShortestPath(start, end);
    std::cout << path.size() << '\n';
    for (auto next_number: path) {
        std::cout << next_number << '\n';
    }
    return 0;
}
