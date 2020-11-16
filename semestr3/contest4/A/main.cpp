#include <iostream>
#include <vector>

struct Edge {
    size_t from;
    size_t to;
    int weight;
};


std::vector<int> FordBellman(const std::vector<Edge>& edges, size_t n_vertexes, size_t start) {
    const int infinity = 30000;
    std::vector<int> distance(n_vertexes, infinity);
    distance[start] = 0;
    for (size_t i = 0; i < n_vertexes - 1; ++i) {
        for (auto& edge: edges) {
            auto [from, to, weight] = edge;
            if (distance[from] != infinity && distance[to] > distance[from] + weight) {
                distance[to] = distance[from] + weight;
            }
        }
    }
    return distance;
}

int main() {
    size_t n_vertexes, n_edges;
    std::cin >> n_vertexes >> n_edges;

    std::vector<Edge> edges;

    for (size_t i = 0; i < n_edges; ++i) {
        size_t from, to;
        int weight;
        std::cin >> from >> to >> weight;
        --from, --to;
        edges.push_back({from, to, weight});
    }

    for (auto distance: FordBellman(edges, n_vertexes, 0)) {
        std::cout << distance << ' ';
    }

    return 0;
}