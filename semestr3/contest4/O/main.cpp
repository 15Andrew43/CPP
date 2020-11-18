#include <iostream>
#include <vector>
#include <queue>

struct AdjacentVertex {
    int to;
    int weight;
};

int infinity = 2009000999;
using Graph = std::vector<std::vector<AdjacentVertex>>;

bool Relax(int vertex, const AdjacentVertex& adjacent_vertex, std::vector<int>& distances) {
    if (distances[adjacent_vertex.to] > distances[vertex] + adjacent_vertex.weight) {
        distances[adjacent_vertex.to] = distances[vertex] + adjacent_vertex.weight;
        return true;
    }
    return false;
}

std::vector<int> Dijkstra(const Graph& graph, const int start) {
    std::vector<bool> used(graph.size(), false);
    std::vector<int> distances(graph.size(), infinity);
    distances[start] = 0;
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> heap;
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


std::vector<int> BellmanFord(const Graph& graph, const int start = 0) {
    std::vector<int> distances(graph.size(), infinity);
    distances[start] = 0;
    std::queue<int> queue;
    queue.push(start);
    std::vector<bool> used(graph.size(), false);
    while (!queue.empty()) {
        auto vertex = queue.front();
        queue.pop();
        used[vertex] = false;
        for (const auto& adjacent_vertex: graph[vertex]) {
            if (Relax(vertex, adjacent_vertex, distances) && !used[adjacent_vertex.to]) {
                queue.push(adjacent_vertex.to);
                used[adjacent_vertex.to] = true;
            }
        }
    }
    return distances;
}

void AddPotentialToDistances(Graph& graph, int cnt_vertex, const std::vector<int>& potentials, short sighn) {
    for (int i = 0; i < cnt_vertex; ++i) {
        for (int j = 0; j < graph[i].size(); ++j) {
            graph[i][j].weight += sighn*(potentials[i] - potentials[graph[i][j].to]);
        }
    }
}

std::vector<std::vector<int>> Johnson(Graph& graph) {
// super-vertex
    int cnt_vertex = graph.size();
    int super_vertex = cnt_vertex;
    graph.push_back(std::vector<AdjacentVertex>());
    for (int i = 0; i < cnt_vertex; ++i) {
        graph[cnt_vertex].push_back({i, 0});
    }

// Ford-Bellman
    auto potentials = BellmanFord(graph, super_vertex);
    graph.pop_back();

// Dijkstra
    std::vector<std::vector<int>> distances(cnt_vertex);
    AddPotentialToDistances(graph, cnt_vertex, potentials, 1);
    for (int i = 0; i < cnt_vertex; ++i) {
        distances.push_back(Dijkstra(graph, i));
    }
    AddPotentialToDistances(graph, cnt_vertex, potentials, -1);
    return distances;
}


int GteMaxMinDistance(Graph& graph) {
    auto distances = Johnson(graph);
    int max_min_dist = -1;
    for (int i = 0; i < distances.size(); ++i) {
        for (int j = 0; j < distances[i].size(); ++j) {
            if (distances[i][j] < infinity && distances[i][j] > max_min_dist) {
                max_min_dist = distances[i][j];
            }
        }
    }
    return max_min_dist;
}

int main() {
    int cnt_vertexes;
    std::cin >> cnt_vertexes;
    Graph graph(cnt_vertexes);
    for (int i = 0; i < cnt_vertexes; ++i) {
        for (int j = 0; j < cnt_vertexes; ++j) {
            int weight;
            std::cin >> weight;
            if (weight != -1) {
                graph[i].push_back({j, weight});
            }
        }
    }

    auto distance = GteMaxMinDistance(graph);
    std::cout << distance;
    return 0;
}