#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <unordered_map>


using Coordinates = std::tuple<int, int>;

std::vector<Coordinates > getNeighbours(int N, Coordinates v) {
    int start_x = std::get<0>(v);
    int start_y = std::get<1>(v);
    std::vector<Coordinates > neighbours;
    for (int y = -2; y <= 2; ++y) {
        for (int x = -2; x <= 2; ++x) {
            if (start_x + x >= 1 && start_x + x <= N && start_y + y >= 1 && start_y + y <= N && abs(x) + abs(y) == 2) {
                neighbours.emplace_back(start_x + x, start_y + y);
            }
        }
    }
    return neighbours;
}
std::vector<Coordinates > GetShortestPath(int N, Coordinates from, Coordinates to) {
    std::queue<Coordinates > q;
    std::unordered_map<Coordinates , int> distance;
    std::unordered_map<Coordinates , Coordinates > parent;
    distance[from] = 0;
    q.push(from);

    while (!q.empty()) {
        Coordinates v = q.front();
        q.pop();
        const std::vector<Coordinates > neighbours = getNeighbours(N, v);
        for (auto u: neighbours) {
            if (distance.find(u) == distance.end()) {
                q.push(u);
                distance[u] = distance[v] + 1;
//                parent[u];
                parent[u] = v;
            }
        }
    }

    std::vector<Coordinates > path;
//    if (distance.find(to) == distance.end()) {
//        path.push_back(-1);
//        return path;
//    }
    while (to != from) {
        path.push_back(to);
        to = parent[to];
    }
    path.push_back(from);
    return {path.rbegin(), path.rend()};
}


int main() {
    int N;
    int x_from, y_from;
    int x_to, y_to;
    std::cin >> N >> x_from >> y_from >> x_to >> y_to;
    std::vector<Coordinates > path  = GetShortestPath(N, std::make_tuple(x_from, y_from), std::make_tuple(x_to, y_to));
    std::cout << path.size() - 1 << '\n';
    for (auto x: path) {
        std::cout << std::get<0>(x) << ' ' << std::get<1>(x) << '\n';
    }
    return 0;
}
