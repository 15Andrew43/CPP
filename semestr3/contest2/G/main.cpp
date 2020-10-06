#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <utility>


using Coordinates = std::pair<int, int>;

enum Color {
    undiscovered = 0,
    discovered = 1,
    processed = 2,
};

std::vector<Coordinates> getPossibleMoves(const std::vector<std::vector<int>>& map, const Coordinates& start,
                                                std::vector<std::vector<Color>>& colors) {
    std::vector<Coordinates> possible_moves;
    int start_y = start.first;
    int start_x = start.second;
    std::vector<Coordinates> moves = {std::make_pair(start_y - 1, start_x),
                                      std::make_pair(start_y + 1, start_x),
                                      std::make_pair(start_y, start_x - 1),
                                      std::make_pair(start_y, start_x + 1)};
    for (auto move: moves) {
        if (map[move.first][move.second] <= map[start_y][start_x] && colors[move.first][move.second] == undiscovered) {
            possible_moves.push_back(move);
        }
    }
    return possible_moves;
}

int DFSVisit(const std::vector<std::vector<int>>& map,
            const Coordinates& start, std::vector<std::vector<Color>>& colors, bool& is_deapest, int& drain_cnt) {
    colors[start.first][start.second] = discovered;
    std::vector<Coordinates> possible_moves = getPossibleMoves(map, start, colors);
    if (possible_moves.size() == 0) {
//        return map[start.first][start.second];
        is_deapest = true;
    }
    for (auto u: possible_moves) {
        if (is_deapest) {
            if (DFSVisit(map, u, colors, is_deapest, drain_cnt) != map[start.first][start.second]) {
                is_deapest = false;
                ++drain_cnt;
                std:: cout << u.first << ' ' << u.second << '\n';
                std::cout << "pep\n";
            }
        } else {
            DFSVisit(map, u, colors, is_deapest, drain_cnt);
        }
    }
    colors[start.first][start.second] = processed;
    return map[start.first][start.second];
}

int DFS(const std::vector<std::vector<int>>& map, const Coordinates& start) {
    bool is_deapest = false;
    int drain_cnt = 0;
    std::vector<std::vector<Color>> colors(map.size(), std::vector<Color>(map[0].size(), undiscovered));
    DFSVisit(map, start, colors, is_deapest, drain_cnt);
    return drain_cnt;
}

int main() {
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<int>> map;
    Coordinates max_hight_coord;
    int max_hight = 0;

    map.push_back(std::vector<int>(m + 2, 10001));
    for (int i = 0; i < n; ++i) {
        std::vector<int> line;
        line.push_back(10001);
        for (int j = 0; j < m; ++j) {
            int hight;
            std::cin >> hight;
            if (hight > max_hight) {
                max_hight = hight;
                max_hight_coord = std::make_pair(i + 1, j + 1);
            }
            line.push_back(hight);
        }
        line.push_back(10001);
        map.push_back(line);
    }
    map.push_back(std::vector<int>(m + 2, 10001));

//    for (auto line: map) {
//        for (auto high: line) {
//            std::cout << high << ' ';
//        }
//        std::cout << '\n';
//    }
//    std::cout << max_hight_coord.first << ' ' << max_hight_coord.second << '\n';
    std::cout << DFS(map, max_hight_coord);
    return 0;
}
