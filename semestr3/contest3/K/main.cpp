#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

struct Edge {
    size_t weight;
    size_t to;
    Edge(size_t weight, size_t to) : weight(weight), to(to) {
    }
};

using Graph = std::vector<std::vector<Edge>>;


size_t Prim(const Graph& graph) {
    std::vector<bool> used(graph.size(), false);
    used[0] = true;
    std::vector<size_t> distance(graph.size(), 1000000);
    size_t current = 0;
    size_t weight_mst = 0;
    size_t n_edge_in_mst = 0;
    std::vector<Edge> heap;
    for (const auto& vertex: graph[current]) {
        heap.push_back(vertex);
    }
    std::make_heap(heap.begin(), heap.end(), [](const Edge& a, const Edge& b) {
                                                    return a.weight > b.weight;
                                                });
    while (n_edge_in_mst < graph.size() - 1) {
        std::pop_heap(heap.begin(), heap.end(), [](const Edge& a, const Edge& b) {
                                                    return a.weight > b.weight;
                                                });
        auto min_weight_edge = heap.back();
        heap.pop_back();
        if (used[min_weight_edge.to]) {
            continue;
        }
        used[min_weight_edge.to] = true;
        weight_mst += min_weight_edge.weight;
        for (auto vertex: graph[min_weight_edge.to]) {
            if (!used[vertex.to] && distance[vertex.to] > min_weight_edge.weight) {
                distance[vertex.to] = vertex.weight;
                heap.push_back(vertex);
                std::push_heap(heap.begin(), heap.end(), [](const Edge& a, const Edge& b) {
                                                                return a.weight > b.weight;
                                                            });
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