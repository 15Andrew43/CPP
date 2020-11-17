#include <iostream>
#include <vector>
#include <queue>


size_t infinity = 2009000999;
using Graph = std::vector<std::vector<size_t>>;

bool Relax(const Graph& graph, size_t vertex, size_t adjacent_vertex, std::vector<size_t>& distances) {
    if (distances[adjacent_vertex] > distances[vertex] + graph[vertex][adjacent_vertex]) {
        distances[adjacent_vertex] = distances[vertex] + graph[vertex][adjacent_vertex];
        return true;
    }
    return false;
}

long long int Dijkstra(const Graph& graph, const size_t start, const size_t finish) {
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

        for (size_t j = 0; j < graph[vertex].size(); ++j) {
            if (Relax(graph, vertex, j, distances)) {
                heap.push(std::make_pair(distances[j], j));
            }
        }
    }
    if (distances[finish] == infinity) {
        return -1;
    }
    return distances[finish];
}

