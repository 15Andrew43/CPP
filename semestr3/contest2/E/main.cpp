#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <utility>


std::vector<std::pair<int, int>> GetPossibleMoves(int n, int m, std::pair<int, int> v) {
    int y = v.first;
    int x = v.second;
    std::vector<std::pair<int, int>> possible_moves;
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (x + j >= 0 && x + j < m && y + i >= 0 && y + i < n && abs(i) + abs(j) == 1) {
                possible_moves.push_back(std::make_pair(y + i, x + j));
            }
        }
    }
    return possible_moves;
}
void GetShortestPath(const std::vector<std::vector<int>>& map, std::vector<std::vector<int>>& distance_map) {
    for (int i = 0; i < map.size(); ++i) {
        for (int j = 0; j < map[0].size(); ++j) {
            if (map[i][j] == 1) {
                std::queue<std::pair<int, int>> q;
                distance_map[i][j] = 0;
                q.push(std::make_pair(i, j));
                while (!q.empty()) {
                    std::pair<int, int> v = q.front();
                    q.pop();
                    std::vector<std::pair<int, int>> possible_moves = GetPossibleMoves(map.size(), map[0].size(), v);
                    for (auto u: possible_moves) {
                        int y = u.first;
                        int x = u.second;
                        if (distance_map[y][x] < distance_map[v.first][v.second]) {
                            q.push(u);
                            distance_map[y][x] = distance_map[v.first][v.second];
                        }
                    }
                }
            }
        }
    }

}


int main() {
    auto v = GetPossibleMoves(3, 4, std::make_pair(1, 1));
    for (auto x: v) {
        std::cout << x.first << ' ' << x.second << '\n';
    }
    size_t infinity = 1000000;
    int N, M;
    std::cin >> N >> M;
    std::vector<std::vector<int>> map;
    for (int i = 0; i < N; ++i) {
        std::vector<int> line;
        for (int j = 0; j < M; ++j) {
            int sub;
            std::cin >> sub;
            line.push_back(sub);
        }
        map.push_back(line);
    }
    std::vector<std::vector<int>> distance_map;
    for (int i = 0; i < N; ++i) {
        std::vector<int> line;
        for (int j = 0; j < M; ++j) {
            line.push_back(infinity);
        }
        map.push_back(line);
    }
    std::cout << "pep\n";

    GetShortestPath(map, distance_map);
    for (auto line: distance_map) {
        for (auto dist_to_sub: line) {
            std::cout << dist_to_sub << ' ';
        }
        std::cout << '\n';
    }
    return 0;
}
