#include <iostream>
#include <vector>
#include <queue>

struct AdjacentVertex {
    size_t to;
    size_t weight;
};

size_t infinity = 2009000999;
using Graph = std::vector<std::vector<AdjacentVertex>>;

bool Relax(size_t vertex, const AdjacentVertex& adjacent_vertex, std::vector<size_t>& distances) {
    if (distances[adjacent_vertex.to] > distances[vertex] + adjacent_vertex.weight) {
        distances[adjacent_vertex.to] = distances[vertex] + adjacent_vertex.weight;
        return true;
    }
    return false;
}

std::vector<size_t> Dijkstra(const Graph& graph, const size_t start) {
    std::vector<bool> used(graph.size(), false);
    std::vector<size_t> distances(graph.size(), infinity);
    distances[start] = 0;
    std::priority_queue<std::pair<size_t, size_t>, std::vector<std::pair<size_t, size_t>>, std::greater<std::pair<size_t, size_t>>> heap;
    heap.push(std::make_pair(distances[start], start));

    while (!heap.empty()) {
        auto vertex = heap.top().second;
        heap.pop();
        if (used[vertex]) {
            continue;
        }
        used[vertex] = true;

        for (const auto& adjacent_vertex: graph[vertex]) {
            if (Relax(vertex, adjacent_vertex, distances)) {
                heap.push(std::make_pair(distances[adjacent_vertex.to], adjacent_vertex.to));
            }
        }
    }
    return distances;
}

int main() {
    short int num;
    std::cin >> num;
    for (short int i = 0; i < num; ++i) {
        size_t n_vertexes, n_edges;
        std::cin >> n_vertexes >> n_edges;
        Graph graph(n_vertexes);
        for (size_t j = 0; j < n_edges; ++j) {
            size_t from, to, weight;
            std::cin >> from >> to >> weight;
            graph[from].push_back({to, weight});
            graph[to].push_back({from, weight});
        }
        size_t start;
        std::cin >> start;
        auto distances = Dijkstra(graph, start);
        for (auto distance: distances) {
            std::cout << distance << ' ';
        }
        std::cout << '\n';
    }
    return 0;
}