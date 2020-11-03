#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <queue>

struct Edge {
    size_t weight;
    size_t to;
    Edge(size_t weight, size_t to) : weight(weight), to(to) {
    }
};

using Graph = std::vector<std::vector<Edge>>;

struct Comp {
    bool operator()(const Edge& a, const Edge& b) {
        return a.weight > b.weight;
    }
};


size_t Prim(const Graph& graph) {
    std::vector<bool> used(graph.size(), false);
    used[0] = true;
    std::vector<size_t> distance(graph.size(), 1000000000);
    size_t current = 0;
    distance[current] = 0;
    size_t weight_mst = 0;
    size_t n_edge_in_mst = 0;
    std::priority_queue<Edge, std::vector<Edge>, Comp> heap;
    for (const auto& vertex: graph[current]) {
        heap.push(vertex);
    }

    while (n_edge_in_mst < graph.size() - 1) {
        auto min_weight_edge = heap.top();
        heap.pop();
        if (used[min_weight_edge.to]) {
            continue;
        }
        used[min_weight_edge.to] = true;
        weight_mst += min_weight_edge.weight;
        for (auto vertex: graph[min_weight_edge.to]) {
            if (!used[vertex.to] && distance[vertex.to] > min_weight_edge.weight) {
                distance[vertex.to] = vertex.weight;
                heap.push(vertex);
            }
        }
        ++n_edge_in_mst;
    }
    return weight_mst;
}

int main() {
    size_t n_vertex, n_edge;
    std::cin >> n_vertex >> n_edge;

    Graph graph(n_vertex);

    for (size_t i = 0; i < n_edge; ++i) {
        size_t from, to;
        size_t weight;
        std::cin >> from >> to >> weight;
        --from, --to;
        graph[from].emplace_back(weight, to);
        graph[to].emplace_back(weight, from);
    }

    std::cout << Prim(graph);
    return 0;
}