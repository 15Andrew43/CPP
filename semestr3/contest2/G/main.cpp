#include <iostream>
#include <vector>
#include <queue>
#include <utility>


using Coordinates = std::pair<int, int>;

std::vector<Coordinates> GetPossibleMoves(const std::vector<std::vector<int>>& map, const Coordinates& start,
                                          const std::vector<std::vector<bool>>& checked) {
    std::vector<Coordinates> possible_moves;
    int y = start.first;
    int x = start.second;

    if (!(checked[y-1][x]) && map[y-1][x] == map[y][x]) {
        possible_moves.emplace_back(y-1, x);
    }
    if (!(checked[y+1][x]) && map[y+1][x] == map[y][x]) {
        possible_moves.emplace_back(y+1, x);
    }
    if (!(checked[y][x-1]) && map[y][x-1] == map[y][x]) {
        possible_moves.emplace_back(y, x-1);
    }
    if (!(checked[y][x+1]) && map[y][x+1] == map[y][x]) {
        possible_moves.emplace_back(y, x+1);
    }
    return possible_moves;
}

int BFS(const std::vector<std::vector<int>>& map) {
    int drain_cnt = 0;
    std::vector<std::vector<bool>> checked(map.size(), std::vector<bool>(map[0].size(), false));

    for (int i = 1; i < map.size()-1; ++i) {
        for (int j = 1; j < map[0].size()-1; ++j) {
            if (checked[i][j]) {
                continue;
            }
            std::queue<Coordinates> q;
            q.push(std::make_pair(i, j));
            bool is_deapest = true;
            while (not q.empty()) {
                Coordinates v = q.front();
                checked[v.first][v.second] = true;
                q.pop();
                int y = v.first;
                int x = v.second;

                std::vector<Coordinates> possible_moves = GetPossibleMoves(map, v, checked);

                if (is_deapest && (map[y-1][x] < map[y][x] || map[y+1][x] < map[y][x] || map[y][x-1] < map[y][x] || map[y][x+1] < map[y][x])) {
                    is_deapest = false;
                }
                for (auto u: possible_moves) {
                    checked[u.first][u.second] = true;
                    q.push(u);
                }
            }
            if (is_deapest) {
                ++drain_cnt;
            }
        }
    }
    return drain_cnt;
}

int main() {
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<int>> map;

    map.emplace_back(m + 2, 10001);
    for (int i = 0; i < n; ++i) {
        std::vector<int> line;
        line.push_back(10001);
        for (int j = 0; j < m; ++j) {
            int hight;
            std::cin >> hight;
            line.push_back(hight);
        }
        line.push_back(10001);
        map.push_back(line);
    }
    map.emplace_back(m + 2, 10001);

    std::cout << BFS(map);
    return 0;
}
