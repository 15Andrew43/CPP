#include <iostream>
#include <vector>
#include <queue>

struct AdjacentVertex {
    int to;
    int weight;
};

using Graph = std::vector<std::vector<AdjacentVertex>>;

bool Relax(int from, const AdjacentVertex& adjacent_vertex, std::vector<int>& distance) {
    if (distance[adjacent_vertex.to] > distance[from] + adjacent_vertex.weight) {
        distance[adjacent_vertex.to] = distance[from] + adjacent_vertex.weight;
        return true;
    }
    return false;
}

std::vector<int> BellmanFord(const Graph& graph, const int start = 0) {
    int infinity = 30000;
    std::vector<int> distance(graph.size(), infinity);
    distance[start] = 0;
    std::queue<int> queue;
    queue.push(start);
    std::vector<bool> used(graph.size(), false);
    while (!queue.empty()) {
        auto vertex = queue.front();
        queue.pop();
        used[vertex] = false;
        for (const auto& adjacent_vertex: graph[vertex]) {
            if (Relax(vertex, adjacent_vertex, distance) && !used[adjacent_vertex.to]) { 
                queue.push(adjacent_vertex.to);
                used[adjacent_vertex.to] = true;
            }
        }
    }
    return distance;
}

int main() {
    int n_vertex, n_adjacent_vertex;
    std::cin >> n_vertex >> n_adjacent_vertex;

    Graph graph(n_vertex);

    for (int i = 0; i < n_adjacent_vertex; ++i) {
        int from, to, weight;
        std::cin >> from >> to >> weight;
        --from, --to;
        graph[from].push_back({to, weight});
    }

    auto distance = BellmanFord(graph);
    for (auto dist: distance) {
        std::cout << dist << ' ';
    }
    return 0;
}