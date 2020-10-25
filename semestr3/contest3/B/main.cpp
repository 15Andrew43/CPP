#include <iostream>
#include <vector>
#include <set>

using Graph = std::vector<std::vector<int>>;
int TIME = -1;

enum Status {
    Undiscovered = 0,
    Discovered = 1,
    Processed = 2
};

struct DfsStatus {
    std::vector<Status> statuses;
    std::vector<int> time_in;
    std::vector<int> time_up;
};



void DfsVisit(const Graph& graph, int vertex, bool is_root, DfsStatus& dfs_status, std::set<std::pair<int, int>>& bridges) {
    auto& statuses = dfs_status.statuses;
    auto& time_in = dfs_status.time_in;
    auto& time_up = dfs_status.time_up;
    statuses[vertex] = Discovered;
    time_in[vertex] = time_up[vertex] = ++TIME;
    for (auto neigbour: graph[vertex]) {
        if (statuses[neigbour] != Undiscovered) {
            time_up[vertex] = std::min(time_up[vertex], time_in[neigbour]);
        } else if (statuses[neigbour] == Undiscovered) {
            DfsVisit(graph, neigbour, false, dfs_status, bridges);
            time_up[vertex] = std::min(time_up[vertex], time_up[neigbour]);
            if (time_in[vertex] <= time_up[neigbour] && ! is_root) {
                int min = std::min(vertex, neigbour);
                int max = std::max(vertex, neigbour);
                bridges.emplace(min, max);
            }
        }
    }
    statuses[vertex] = Processed;
}


std::vector<std::pair<int, int>> Bridges(const Graph& graph) {
    int infinity_time = 1000000;
    std::vector<std::pair<int, int>> bridges;
    DfsStatus dfs_status{
            std::vector<Status>(graph.size(), Undiscovered),
            std::vector<int>(graph.size(), -1),
            std::vector<int>(graph.size(), infinity_time)
    };
    for (int vertex = 0; vertex < graph.size(); ++vertex) {
        if (dfs_status.statuses[vertex] == Undiscovered) {
            DfsVisit(graph, vertex, dfs_status, bridges);
        }
    }
    return bridges;
}

int main() {
    int n, m;
    std::cin >> n >> m;
    Graph graph(n);
    std::vector<std::pair<int, int>> edges;
    for (int i = 0; i < m; ++i) {
        int from, to;
        std::cin >> from >> to;
        --from, --to;
        int min = std::min(from, to);
        int max = std::max(from, to);
        edges.emplace_back(min, max);
        graph[from].push_back(to);
        graph[to].push_back(from);
    }

    auto answer = Bridges(graph);

    std::cout << answer.size() << '\n';
    for (auto edge: answer) {
        std::cout << edge.first << ' ' << edge.second << '\n';
    }

    return 0;
}