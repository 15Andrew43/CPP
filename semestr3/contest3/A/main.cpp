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



void DfsVisit(const Graph& graph, int vertex, bool is_root, DfsStatus& dfs_status, std::set<int>& cut_vertexes) {
    auto& statuses = dfs_status.statuses;
    auto& time_in = dfs_status.time_in;
    auto& time_up = dfs_status.time_up;
    statuses[vertex] = Discovered;
    time_in[vertex] = time_up[vertex] = ++TIME;
    int n_children = 0;
    for (auto neigbour: graph[vertex]) {
        if (statuses[neigbour] != Undiscovered) {
            time_up[vertex] = std::min(time_up[vertex], time_in[neigbour]);
        } else if (statuses[neigbour] == Undiscovered) {
            DfsVisit(graph, neigbour, false, dfs_status, cut_vertexes);
            ++n_children;
            time_up[vertex] = std::min(time_up[vertex], time_up[neigbour]);
            if (time_in[vertex] <= time_up[neigbour] && ! is_root) {
                cut_vertexes.insert(vertex);
            }
        }
    }
    statuses[vertex] = Processed;
    if (is_root && n_children >= 2) {
        cut_vertexes.insert(vertex);
    }
}



std::set<int> CutVertexes(const Graph& graph) {
    int infinity_time = 1000000;
    std::set<int> cut_vertexes;
    DfsStatus dfs_status{
            std::vector<Status>(graph.size(), Undiscovered),
            std::vector<int>(graph.size(), -1),
            std::vector<int>(graph.size(), infinity_time)
    };
    for (int vertex = 0; vertex < graph.size(); ++vertex) {
        if (dfs_status.statuses[vertex] == Undiscovered) {
            DfsVisit(graph, vertex, true, dfs_status, cut_vertexes);
        }
    }
    return cut_vertexes;
}

int main() {
    int n, m;
    std::cin >> n >> m;
    Graph graph(n);
    for (int i = 0; i < m; ++i) {
        int from, to;
        std::cin >> from >> to;
        --from, --to;
        graph[from].push_back(to);
        graph[to].push_back(from);
    }

    auto answer = CutVertexes(graph);

    std::cout << answer.size() << '\n';
    for (auto cut_vertex: answer) {
        std::cout << cut_vertex+1 << '\n';
    }

    return 0;
}