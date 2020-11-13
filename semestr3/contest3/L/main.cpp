#include <iostream>
#include <vector>
#include <utility>

using weight_t = int ;

struct Edge {
    int to;
    weight_t flow;
    weight_t capacity;
    int back;
    Edge(int to, weight_t flow, weight_t capacity, int back) : to(to), flow(flow), capacity(capacity), back(back) {
    }

};

using Graph = std::vector<std::vector<Edge>>;

enum Status {
    kUndiscovered = 0,
    kDiscovered = 1,
};


int FindFlow(Graph& graph, std::vector<Status>& statuses, int from, int to, weight_t max_flow) {
    statuses[from] = kDiscovered;
    if (from == to) {
//        std::cout << max_flow << "\n";
        return max_flow;
    }
    for (auto& edge: graph[from]) {
        if (statuses[edge.to] == kUndiscovered && edge.capacity - edge.flow > 0) {
            int cur_flow = FindFlow(graph, statuses, edge.to, to, std::min(max_flow, edge.capacity - edge.flow));
            if (cur_flow > 0) {
                edge.flow += cur_flow;
                graph[edge.to][edge.back].flow -= cur_flow;
                return cur_flow;
            }
        }
    }
    return 0;
}

int FordFalcon(Graph graph, int from, int to) {
    int cur_flow;
    int res_flow = 0;
    do {
        std::vector<Status> statuses(graph.size(), kUndiscovered);
        cur_flow = FindFlow(graph, statuses, from, to, 1000000);
        res_flow += cur_flow;
    } while (cur_flow > 0);

    return res_flow;
}

int main() {
    int n_vertex, n_edge;
    std::cin >> n_vertex >> n_edge;

    Graph info_graph(n_vertex);

    for (int i = 0; i < n_edge; ++i) {
        int from, to, capacity;
        std::cin >> from >> to >> capacity;
        --from, --to;
        info_graph[from].emplace_back(to, 0, capacity, info_graph[to].size());
        info_graph[to].emplace_back(from, 0, 0, info_graph[from].size() - 1);
    }

    std::cout << FordFalcon(info_graph, 0, info_graph.size()-1);
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