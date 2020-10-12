#include <iostream>
#include <vector>

enum Color {
    undiscovered = 0,
    discovered = 1,
    processed = 2,
};

using Graph = std::vector<std::vector<int>>;


bool DFSVisit(const Graph& graph, int source, std::vector<Color>& colors, std::vector<int>& path, int& number_end) {
    colors[source] = discovered;
    for (auto u: graph[source]) {
        if (colors[u] == undiscovered) {
            if (DFSVisit(graph, u, colors, path, number_end)) {
                if (number_end != -1) {
                    path.push_back(u);
                }
                if (number_end == u) {
                    number_end = -1;
                }
                return true;
            }
        } else if (colors[u] == discovered) {
            number_end = u;
            return true;
        }
    }
    colors[source] = processed;
    return false;
}

std::vector<int> FindCircle(const Graph& graph) {
    std::vector<Color> colors(graph.size(), undiscovered);
    std::vector<int> path;
    for (int i = 0; i < graph.size(); ++i) {
        int number_end = -1;
        if (colors[i] == undiscovered) {
            if (DFSVisit(graph, i, colors, path, number_end)) {
                if (number_end == i) {
                    path.push_back(number_end);
                }
                return {path.rbegin(), path.rend()};
            }
        }
    }
    return path;
}

int main() {
    int v_cnt, e_cnt;
    std::cin >> v_cnt >> e_cnt;

    Graph graph(v_cnt, std::vector<int>());

    for (int i = 0; i < e_cnt; ++i) {
        int from, to;
        std::cin >> from >> to;
        --from, --to;
        graph[from].push_back(to);
    }

    auto path = FindCircle(graph);
    if (path.size()) {
        std::cout << "YES\n";
        for (auto vertex: path) {
            std::cout << vertex+1 << ' ';
        }
    } else {
        std::cout << "NO\n";
    }
    return 0;
}