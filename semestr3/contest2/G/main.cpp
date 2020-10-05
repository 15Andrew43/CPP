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

std::vector<Coordinates > getNeighbours(int N, Coordinates v) {
    int start_x = std::get<0>(v);
    int start_y = std::get<1>(v);
    std::vector<Coordinates > neighbours;
    for (int y = -2; y <= 2; ++y) {
        for (int x = -2; x <= 2; ++x) {
            if (start_x + x >= 1 && start_x + x <= N && start_y + y >= 1 && start_y + y <= N && abs(x) + abs(y) == 3) {
                neighbours.emplace_back(start_x + x, start_y + y);
            }
        }
    }
    return neighbours;
}
std::vector<Coordinates> BFS(int N, Coordinates from, Coordinates to) {
    std::queue<Coordinates> q;
    std::unordered_map<Coordinates, int, MyHash> distance;
    std::unordered_map<Coordinates, Coordinates, MyHash> parent;
    distance[from] = 0;
    q.push(from);

    while (!q.empty()) {
        Coordinates v = q.front();
        q.pop();
        std::vector<Coordinates> neighbours = getNeighbours(N, v);
        for (auto u: neighbours) {
            if (distance.find(u) == distance.end()) {
                q.push(u);
                distance[u] = distance[v] + 1;
                parent[u] = v;
            }
        }
    }

    std::vector<Coordinates > path;
    while (to != from) {
        path.push_back(to);
        to = parent[to];
    }
    path.push_back(from);

    return {path.rbegin(), path.rend()};
}


int main() {
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<int>> map;
    for (int i = 0; i < n; ++i) {
        std::vector<int> line;
        for (int j = 0; j < m; ++j) {
            int hight;
            std::cin >> hight;
            line.push_back(hight);
        }
        map.push_back(line);
    }

    std::cout << BFS(map);
    return 0;
}
