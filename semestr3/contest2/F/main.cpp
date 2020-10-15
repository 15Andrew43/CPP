#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>

int infinity = 1000000;

using Coordinates = std::pair<int, int>;



struct Operation {
    int sighn;
    char axis;
};

int getLengthToBarrier (int x, int y, Operation operation, const std::vector<std::vector<int>>& map) {
    int delta = 0;
    while (map[y][x] != 1) {
        if (operation.sighn == -1) {
            if (operation.axis == 'y') {
                --y;
            } else if (operation.axis == 'x') {
                --x;
            }
        } else if (operation.sighn == 1) {
            if (operation.axis == 'y') {
                ++y;
            } else if (operation.axis == 'x') {
                ++x;
            }
        }
        ++delta;
    }
    return delta;
}


std::vector<Coordinates> getPossibleMoves(const std::vector<std::vector<int>>& map, std::pair<int, int> v) {
    std::vector<Coordinates> possible_moves;
    int y = v.first;
    int x = v.second;
    int delta = 0;
    // --y
    delta = getLengthToBarrier(x, y, {-1, 'y'}, map);
    if (v.first - delta/2 != v.first)
        possible_moves.push_back(std::make_pair(v.first - delta/2, x));
    // ++y
    delta = getLengthToBarrier(x, y, {1, 'y'}, map);
    if (v.first + delta/2 != v.first)
        possible_moves.push_back(std::make_pair(v.first + delta/2, x));
    delta = getLengthToBarrier(x, y, {-1, 'x'}, map);
    if (v.second - delta/2 != v.second)
        possible_moves.push_back(std::make_pair(y, v.second - delta/2));
    delta = getLengthToBarrier(x, y, {1, 'x'}, map);
    if (v.second + delta/2 != v.second)
        possible_moves.push_back(std::make_pair(y, v.second + delta/2));
    return possible_moves;
}

int GetShortestPath(const std::vector<std::vector<int>>& map, Coordinates from, Coordinates to) {
    std::queue<Coordinates> q;
    std::vector<std::vector<int>> distance(map.size(), std::vector<int>(map[0].size(), infinity));
    distance[from.first][from.second] = 0;
    q.push(from);

    while (!q.empty()) {
        Coordinates v = q.front();
        q.pop();
        std::vector<Coordinates> possible_moves = getPossibleMoves(map, v);
        for (auto u: possible_moves) {
            if (distance[u.first][u.second] > distance[v.first][v.second] + 1) {
                q.push(u);
                distance[u.first][u.second] = distance[v.first][v.second] + 1;
            }
        }
    }
    if (distance[to.first][to.second] == infinity) {
        return -1;
    }
    return distance[to.first][to.second];
}


int main() {
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<int>> map;
    std::pair<int, int> start, finish;

    map.push_back(std::vector<int>(m+2, 1));
    for (int i = 0; i < n; ++i) {
        std::string str_line;
        std::cin >> str_line;
        std::vector<int> int_line;
        int_line.push_back(1);
        for (int j = 0; j < str_line.size(); ++j) {
            switch (str_line[j]) {
                case '.':
                    int_line.push_back(0);
                    break;
                case '#':
                    int_line.push_back(1);
                    break;
                case 'S':
                    int_line.push_back(0);
                    start = std::make_pair(i+1, j+1);
                    break;
                case 'T':
                    int_line.push_back(0);
                    finish = std::make_pair(i+1, j+1);
            }
        }
        int_line.push_back(1);
        map.push_back(int_line);
    }
    map.push_back(std::vector<int>(m+2, 1));

    std::cout << GetShortestPath(map, start, finish);

    return 0;
}