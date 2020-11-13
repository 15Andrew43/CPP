#include <iostream>
#include <vector>
#include <algorithm>

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
    int parent;
};



void DfsVisit(const Graph& graph, int vertex, DfsStatus& dfs_status, std::vector<std::pair<int, int>>& bridges) {
    auto& statuses = dfs_status.statuses;
    auto& time_in = dfs_status.time_in;
    auto& time_up = dfs_status.time_up;
    auto parent = dfs_status.parent;
    statuses[vertex] = Discovered;
    time_in[vertex] = time_up[vertex] = ++TIME;
    for (auto neigbour: graph[vertex]) {
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        if (parent == neigbour) {
            continue;
        }
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        if (statuses[neigbour] != Undiscovered) {
            time_up[vertex] = std::min(time_up[vertex], time_in[neigbour]);
        } else if (statuses[neigbour] == Undiscovered) {
//            parent = vertex;
            dfs_status.parent = vertex;
            DfsVisit(graph, neigbour, dfs_status, bridges);
            time_up[vertex] = std::min(time_up[vertex], time_up[neigbour]);
            if (time_in[vertex] < time_up[neigbour]) {
                int min = std::min(vertex, neigbour);
                int max = std::max(vertex, neigbour);
                bridges.emplace_back(min, max);
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
            std::vector<int>(graph.size(), infinity_time),
            -1
    };
    for (int vertex = 0; vertex < graph.size(); ++vertex) {
        if (dfs_status.statuses[vertex] == Undiscovered) {
            DfsVisit(graph, vertex, dfs_status, bridges);
        }
    }

//    for (auto x: dfs_status.time_in) {
//        std::cout << x << ' ';
//    }
//    std::cout << '\n';
//    for (auto x: dfs_status.time_up) {
//        std::cout << x << ' ';
//    }
//    std::cout << '\n';

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

    auto bridges = Bridges(graph);

//    for (auto bridge: bridges) {
//        std::cout << bridge
//    }

    std::vector<int> answer;
    std::cout << bridges.size() << '\n';
    for (auto bridge: bridges) {
        auto it = std::find(edges.begin(), edges.end(), bridge);
//        std::cout << it->first << ' ' << it -> second << '\n';

        answer.push_back(it - edges.begin() + 1);
    }

    std::sort(answer.begin(), answer.end());

    for (auto ind: answer) {
        std::cout << ind << ' ';
    }

    return 0;
}

/*
3 2
2 3
2 1
 */