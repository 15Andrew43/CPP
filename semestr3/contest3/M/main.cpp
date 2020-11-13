#include <iostream>
#include <vector>
#include <utility>
#include <queue>

using weight_t = long long ;

struct Edge {
    long long from;
    long long to;
    weight_t flow;
    weight_t capacity;
    long long back;
    Edge(long long from, long long to, weight_t flow, weight_t capacity, long long back)
        : from(from), to(to), flow(flow), capacity(capacity), back(back) {
    }

};

using Graph = std::vector<std::vector<Edge>>;


bool FindFlow(Graph& graph, long long from, long long to, weight_t& max_flow) {
    std::vector<long long> distance(graph.size(), 1000000001);
    distance[0] = 0;
    std::vector<std::pair<Edge, long long>> parent(graph.size(), std::make_pair(Edge(-1, -1, -1, -1, -1), -1));
    std::queue<long long> queue;
    queue.push(from);

    while (!queue.empty()) {
        long long vertex = queue.front();
        queue.pop();
//        for (auto& edge: graph[vertex]) {
        for (long long i = 0; i < graph[vertex].size(); ++i) {
            auto& edge = graph[vertex][i];
            if (distance[edge.to] > distance[vertex] + 1 && edge.capacity - edge.flow > 0) {
                distance[edge.to] = distance[vertex] + 1;
                queue.push(edge.to);
                parent[edge.to] = std::make_pair(edge, i);
            }
        }
    }

    if (distance[to] == 1000000001) {
        return false;
    }
    Edge edge = parent[to].first;
    weight_t flow = 1000000001;
    while (edge.from != -1) {
        flow = std::min(flow, edge.capacity - edge.flow);
        edge = parent[edge.from].first;
    }
//    std::cout << flow << "\n";
    max_flow += flow;

//    graph[parent[to].first.from][parent[to].second];
    long long vertex = to;
    while (vertex != from) {
        Edge& edge = graph[parent[vertex].first.from][parent[vertex].second];
        edge.flow += flow;
        graph[edge.to][edge.back].flow -= flow;
        vertex = edge.from;
    }
    return true;
}

long long EdmCarp(Graph graph, long long from, long long to) {
    long long res_flow = 0;
    while (FindFlow(graph, from, to, res_flow)) {}

    return res_flow;
}

int main() {
    long long n_vertex, n_edge;
    std::cin >> n_vertex >> n_edge;

    Graph info_graph(n_vertex);

    for (long long i = 0; i < n_edge; ++i) {
        long long from, to, capacity;
        std::cin >> from >> to >> capacity;
        --from, --to;
        info_graph[from].emplace_back(from, to, 0, capacity, info_graph[to].size());
        info_graph[to].emplace_back(to, from, 0, 0, info_graph[from].size() - 1);
    }

    std::cout << EdmCarp(info_graph, 0, info_graph.size()-1);
    return 0;
}

/*
4 5
1 2 4
1 3 5
2 3 2
2 4 2
3 4 6
 */