#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

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


std::vector<std::pair<int, int>> Bridges(const Graph& graph, int vertex) {
    int infinity_time = 1000000;
    std::vector<std::pair<int, int>> bridges;
    DfsStatus dfs_status{
            std::vector<Status>(graph.size(), Undiscovered),
            std::vector<int>(graph.size(), -1),
            std::vector<int>(graph.size(), infinity_time),
            -1
    };
    DfsVisit(graph, vertex, dfs_status, bridges);


//    for (auto x: dfs_status.time_in) {
//    //    std::cout << x << ' ';
//    }
////    std::cout << '\n';
//    for (auto x: dfs_status.time_up) {
//    //    std::cout << x << ' ';
//    }
////    std::cout << '\n';

    return bridges;
}

void DFSVisitForTree(const Graph& graph, int source, std::vector<Status>& statuses,
                        std::vector<std::pair<int, int>>& bridges, int& vertex_number, Graph& condens_graph) {
    statuses[source] = Discovered;

    auto current_number = vertex_number;

    for (auto u: graph[source]) {
        if (statuses[u] == Undiscovered) {
            if (std::find(bridges.begin(), bridges.end(),
                    std::make_pair(std::min(source, u), std::max(source, u))) != bridges.end()) {
                ++vertex_number;
                condens_graph[current_number].push_back(vertex_number);
                condens_graph[vertex_number].push_back(current_number);
            //    std::cout << "pep\n";

            }
            DFSVisitForTree(graph, u, statuses, bridges, vertex_number, condens_graph);
        }
    }
    statuses[source] = Processed;
}

void DFS(const Graph& graph, int source, std::vector<Status>& statuses) {
    statuses[source] = Discovered;

    for (auto u: graph[source]) {
        if (statuses[u] == Undiscovered) {
            DFS(graph, u, statuses);
        }
    }
    statuses[source] = Processed;
}

int GetCntTonnels(const Graph& graph) {
    int vertex_number = -1;

    std::vector<Status> statuses(graph.size(), Undiscovered);

    int n_leaves = 0;
    int cnt_cycle = 0;
    for (int i = 0; i < graph.size(); ++i) {
        if (statuses[i] == Undiscovered) {
        //    std::cout << i << '\n';
            if (graph[i].size() == 0) {
                statuses[i] = Processed;
                n_leaves += 2;
                continue;
            }
            auto bridges = Bridges(graph, i);
            if (bridges.size() == 0) {
                n_leaves += 2;
                ++cnt_cycle;
                DFS(graph, i, statuses);
                continue;
            }

            Graph condens_graph(bridges.size()+1);
            DFSVisitForTree(graph, bridges[0].first, statuses, bridges, ++vertex_number, condens_graph);
        //    std::cout << "pep\n";

            for (int j = 0; j < condens_graph.size(); ++j) {
                if (condens_graph[j].size() == 1) {
                    ++n_leaves;
                //    std::cout << "pep\n";
                }
            }
            vertex_number = -1;
        }
    }

    if (n_leaves == 2 && cnt_cycle == 1) {
        return 0;
    }
    return (n_leaves+1)/2;
}

int main() {
    int n_buildings, n_tonnels;
    std::cin >> n_buildings >> n_tonnels;

    Graph graph(n_buildings);

    for (int i = 0; i < n_tonnels; ++i) {
        int from, to;
        std::cin >> from >> to;
        --from, --to;
        graph[from].push_back(to);
        graph[to].push_back(from);
    }

    std::cout << GetCntTonnels(graph);
    return 0;
}