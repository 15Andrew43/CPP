#include <iostream>
#include <vector>

using Graph = std::vector<std::vector<int>>;

std::vector<std::vector<int>> Floyd(const Graph& graph) {
    auto distances = graph;
    int len = graph.size();
    for (int k = 0; k < len; ++k) {
        for (int x = 0; x < len; ++x) {
            for (int y = 0; y < len; ++y) {
                distances[x][y] = std::min(distances[x][y], distances[x][k] + distances[k][y]);
            }
        }
    }
    return distances;
}

int main() {
    int cnt_vertexes;
    std::cin >> cnt_vertexes;
    Graph graph(cnt_vertexes, std::vector<int>(cnt_vertexes));
    for (int i = 0; i < cnt_vertexes; ++i) {
        for (int j = 0; j < cnt_vertexes; ++j) {
            std::cin >> graph[i][j];
        }
    }

    auto distances = Floyd(graph);

    for (int i = 0; i < cnt_vertexes; ++i) {
        for (int j = 0; j < cnt_vertexes; ++j) {
            std::cout << distances[i][j] << ' ';
        }
        std::cout << '\n';
    }
    return 0;
}
/*
6
0 6 8 1000000 1000000 1000000
5 0 5 1000000 1000000 1000000
1 7 0 1000000 1000000 1000000
1000000 1000000 1000000 0 6 1000000
1000000 1000000 1000000 1000000 0 3
1000000 1000000 1000000 2 1000000 0
*/