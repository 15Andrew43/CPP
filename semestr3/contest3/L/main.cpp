#include <iostream>
#include <vector>
#include <utility>

struct Edge {
    
};

using Graph = std::vector<std::vector<Edge>>;

enum Status {
    kUndiscovered = 0,
    kDiscovered = 1,
    kProcessed = 2
};

void DfsVisit(const Graph& graph, int from, int to, std::vector<Status>& statuses, std::vector<int>& predecessors) {
    statuses[from] = kDiscovered;
    if (from == to) {
        return;
    }
    for (auto neighbour: graph[from]) {
         if (statuses[neighbour.first] == kUndiscovered) {
             predecessors[neighbour.first] = from;
             DfsVisit(graph, neighbour.first, to,statuses, predecessors);
        }
    }
    statuses[from] = kProcessed;
}

std::vector<int> GetPath(const Graph& graph, int from, int to) {
    std::vector<Status> statuses(graph.size(), kUndiscovered);
    std::vector<int> predecessors(graph.size(), -1);

    DfsVisit(graph, from, to, statuses, predecessors);

    std::vector<int> path;
    int current = to;
    while (current != -1) {
        path.push_back(current);
        current = predecessors[current];
    }
    return {path.rbegin(), path.rend()};
}

int FindMinFlow(const Graph& graph, const std::vector<int>& path) {
    int min = 1000000;

}

int FordFalcon(const Graph& info_graph) {
    Graph graph = info_graph;

    auto path = GetPath(graph, 0, graph.size()-1);

    int min = FindMinFlow(graph, path);
}

int main() {
    int n_vertex, n_edge;
    std::cin >> n_vertex >> n_edge;

    Graph info_graph(n_vertex);

    for (int i = 0; i < n_edge; ++i) {
        int from, to, bandwidth;
        std::cin >> from >> to >> bandwidth;
        --from, --to;
        info_graph[from].emplace_back(to, bandwidth);
        info_graph[to].emplace_back(from, 0);
    }

    std::cout << FordFalcon(info_graph);
    return 0;
}