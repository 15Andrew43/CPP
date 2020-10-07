#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <utility>


using Coordinates = std::pair<int, int>;

struct MyHash {
    size_t operator()(const Coordinates& value) const noexcept {
        return std::hash<int>{}(value.first) ^ std::hash<int>{}(value.second);
    }
};

std::vector<Coordinates> getNeighbours(int chess_field_size, Coordinates coordinate) {
    int start_x = std::get<0>(coordinate);
    int start_y = std::get<1>(coordinate);
    std::vector<Coordinates > neighbours;
    for (int y = -2; y <= 2; ++y) {
        for (int x = -2; x <= 2; ++x) {
            if (start_x + x >= 1 && start_x + x <= chess_field_size && start_y + y >= 1
                        && start_y + y <= chess_field_size && abs(x) + abs(y) == 3) {
                neighbours.emplace_back(start_x + x, start_y + y);
            }
        }
    }
    return neighbours;
}
std::vector<Coordinates> GetShortestPath(int chess_field_size, Coordinates from, Coordinates to) {
    std::queue<Coordinates> queue;
    std::unordered_map<Coordinates, int, MyHash> distance;
    std::unordered_map<Coordinates, Coordinates, MyHash> parent;
    distance[from] = 0;
    queue.push(from);

    while (!queue.empty()) {
        Coordinates v = queue.front();
        queue.pop();
        std::vector<Coordinates> neighbours = getNeighbours(chess_field_size, v);
        for (auto neighbour: neighbours) {
            if (distance.find(neighbour) == distance.end()) {
                queue.push(neighbour);
                distance[neighbour] = distance[v] + 1;
                parent[neighbour] = v;
            }
        }
    }

    std::vector<Coordinates> path;
    while (to != from) {
        path.push_back(to);
        to = parent[to];
    }
    path.push_back(from);

    return {path.rbegin(), path.rend()};
}


int main() {
    int chess_field_size;
    int x_from, y_from;
    int x_to, y_to;
    std::cin >> chess_field_size >> x_from >> y_from >> x_to >> y_to;

    std::vector<Coordinates> path  = GetShortestPath(chess_field_size, std::make_pair(x_from, y_from), std::make_pair(x_to, y_to));
    std::cout << path.size() - 1 << '\n';
    for (auto x: path) {
        std::cout << std::get<0>(x) << ' ' << std::get<1>(x) << '\n';
    }
    return 0;
}
