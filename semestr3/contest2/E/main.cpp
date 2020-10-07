#include <iostream>
#include <vector>
#include <queue>

size_t infinity = 1000000;

using Coordinate = std::pair<int, int>;

std::vector<Coordinate> GetPossibleMoves(int y_size, int x_size, Coordinate coordinate) {
    int cur_y = coordinate.first;
    int cur_x = coordinate.second;
    std::vector<Coordinate > possible_moves;
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (cur_x + j >= 0 && cur_x + j < x_size && cur_y + i >= 0 && cur_y + i < y_size && abs(i) + abs(j) == 1) {
                possible_moves.emplace_back(cur_y + i, cur_x + j);
            }
        }
    }
    return possible_moves;
}
std::vector<std::vector<int>> GetShortestPath(const std::vector<std::vector<int>>& map) {
    std::vector<std::vector<int>> distance_map;
    for (int i = 0; i < map.size(); ++i) {
        std::vector<int> line;
        for (int j = 0; j < map[0].size(); ++j) {
            line.push_back(infinity);
        }
        distance_map.push_back(line);
    }
    for (int i = 0; i < map.size(); ++i) {
        for (int j = 0; j < map[0].size(); ++j) {
            if (map[i][j] == 1) {
                std::queue<Coordinate > queue;
                distance_map[i][j] = 0;
                queue.push(std::make_pair(i, j));
                while (!queue.empty()) {
                    Coordinate cur_coordinate = queue.front();
                    queue.pop();
                    std::vector<Coordinate > possible_moves = GetPossibleMoves(map.size(), map[0].size(), cur_coordinate);
                    for (auto move: possible_moves) {
                        int y = move.first;
                        int x = move.second;
                        if (distance_map[y][x] > distance_map[cur_coordinate.first][cur_coordinate.second] + 1) {
                            queue.push(move);
                            distance_map[y][x] = distance_map[cur_coordinate.first][cur_coordinate.second] + 1;
                        }
                    }
                }
            }
        }
    }
    return distance_map;
}


int main() {
    int y_size, x_size;
    std::cin >> y_size >> x_size;

    std::vector<std::vector<int>> map;
    for (int i = 0; i < y_size; ++i) {
        std::vector<int> line;
        for (int j = 0; j < x_size; ++j) {
            int sub;
            std::cin >> sub;
            line.push_back(sub);
        }
        map.push_back(line);
    }

    std::vector<std::vector<int>> distance_map = GetShortestPath(map);

    for (auto line: distance_map) {
        for (auto dist_to_sub: line) {
            std::cout << dist_to_sub << ' ';
        }
        std::cout << '\n';
    }
    return 0;
}
