#include <iostream>
#include <vector>
#include <utility>

using weight_t = int ;

struct Edge {
    int to;
//    weight_t flow;
    weight_t capacity;
//    int back;
    Edge(int to, weight_t capacity) : to(to), capacity(capacity) {
    }

};

using Graph = std::vector<std::vector<Edge>>;

enum Status {
    kUndiscovered = 0,
    kDiscovered = 1,
    kProcessed = 2
};

void DfsVisit(const Graph& graph, int from, int to, std::vector<Status>& statuses, std::vector<int>& predecessors) {
    statuses[from] = kDiscovered;
    for (auto neighbour: graph[from]) {
        if (statuses[neighbour.to] == kUndiscovered && neighbour.capacity > 0) {
            predecessors[neighbour.to] = from;
            DfsVisit(graph, neighbour.to, to,statuses, predecessors);
        }
    }
    statuses[from] = kProcessed;
}


int FindFlow(Graph& graph, int from, int to) {
    std::vector<Status> statuses(graph.size(), kUndiscovered);
    std::vector<int> predecessors(graph.size(), -1);

    DfsVisit(graph, from, to, statuses, predecessors);

    std::vector<int> path;
    int current = to;
    while (current != -1) {
        path.push_back(current);
        current = predecessors[current];
    }

    for (int i = 0; i < path.size() / 2; ++i) {
        std::swap(path[i], path[path.size() - 1]);
    }
    std::cout << "path\n";
    for (auto x: path) {
        std::cout << x + 1 << ' ';
    }
    std::cout << '\n';

    int min_flow = 1000000;
    for (int i = 0; i < path.size() - 1; ++i) {
        for (int j = 0; j < graph[path[i]].size(); ++j) {
            if (graph[path[i]][j].to == path[i+1]) {
                if (graph[path[i]][j].capacity < min_flow) {
                    min_flow = graph[path[i]][j].capacity;
                }
                break;
            }
        }
    }
    for (int i = 0; i < path.size() - 1; ++i) {
        for (int j = 0; j < graph[path[i]].size(); ++j) {
            if (graph[path[i]][j].to == path[i+1]) {
                graph[path[i]][j].capacity -= min_flow;
                for (int k = 0; k < graph[path[i+1]].size(); ++k) {
                    if (graph[path[i+1]][k].to == path[i]) {
                        graph[path[i+1]][k].capacity += min_flow; // ?????????
                    }
                }
            }
        }
    }
    return min_flow;
}

int FordFalcon(const Graph& info_graph, int from, int to) {
    Graph graph = info_graph;
    int cur_flow = 1000000;
    int flow = 0;
    do {
        cur_flow = FindFlow(graph, from, to);
        flow += cur_flow;
    } while (cur_flow > 0);

    return flow;
}

int main() {
    int n_vertex, n_edge;
    std::cin >> n_vertex >> n_edge;

    Graph info_graph(n_vertex);

    for (int i = 0; i < n_edge; ++i) {
        int from, to, capacity;
        std::cin >> from >> to >> capacity;
        --from, --to;
        info_graph[from].emplace_back(to, capacity); // info_graph[to].size()
        info_graph[to].emplace_back(from, 0); // , info_graph[from].size() - 1
    }

    std::cout << FordFalcon(info_graph, 0, info_graph.size()-1);
    return 0;
}