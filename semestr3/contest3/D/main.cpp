#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using Graph = std::vector<std::vector<size_t >>;
int TIME = -1;

enum Status {
    Undiscovered = 0,
    Discovered = 1,
    Processed = 2
};

struct DfsStatus {
    std::vector<Status>& statuses;
    std::vector<int> time_in;
    std::vector<int> time_up;
    int parent;
};



void DfsVisit(const Graph& graph, size_t vertex, DfsStatus& dfs_status, bool& last_bridge, int& cnt_last, bool& is_last, size_t& cnt_bridges) {
    auto& statuses = dfs_status.statuses;
    auto& time_in = dfs_status.time_in;
    auto& time_up = dfs_status.time_up;
    auto parent = dfs_status.parent;
    statuses[vertex] = Discovered;
    time_in[vertex] = time_up[vertex] = ++TIME;

//    bool last_bridge = false;

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
            last_bridge = true;
            dfs_status.parent = vertex;
            DfsVisit(graph, neigbour, dfs_status, last_bridge, cnt_last, is_last, cnt_bridges);
            time_up[vertex] = std::min(time_up[vertex], time_up[neigbour]);
            if (time_in[vertex] < time_up[neigbour]) {
                int min = std::min(vertex, neigbour);
                int max = std::max(vertex, neigbour);
                if (last_bridge) {
//                bridges.emplace_back(min, max);
//                    std::cout << "||| " << min << ' ' << max << '\n';
                    ++cnt_bridges;
                    last_bridge = false;
//                    cnt_last = false;
                    is_last = false;
                }
                if (min == 0) {
                    ++cnt_last;
                    is_last = true;
                }
            }
        }
    }
    statuses[vertex] = Processed;
}


size_t Bridges(const Graph& graph, size_t vertex, std::vector<Status >& statuses) {
    size_t infinity_time = 1000000000;
//    std::vector<std::pair<int, int>> bridges;
    size_t cnt_bridges = 0;
    DfsStatus dfs_status{
            statuses,
            std::vector<int>(graph.size(), -1),
            std::vector<int>(graph.size(), infinity_time),
            -1
    };
    bool last_bridge = true;
    int cnt_last = 0;
    bool is_last = false;
    DfsVisit(graph, vertex, dfs_status, last_bridge, cnt_last, is_last, cnt_bridges);
    if (cnt_last == 1 && is_last && cnt_bridges != 1) {
        ++cnt_bridges;
    }
//    std::cout << "cnt = " << cnt_bridges << '\n';

//    for (auto x: dfs_status.time_in) {
//    //    std::cout << x << ' ';
//    }
////    std::cout << '\n';
//    for (auto x: dfs_status.time_up) {
//    //    std::cout << x << ' ';
//    }
////    std::cout << '\n';

//    if (graph[0].size() == 1 && graph[graph[0][0]].size() > 1 && cnt_bridges > 0) {
//        std::cout << "pep\n";
//        ++cnt_bridges;
//    }

    return cnt_bridges;
}

//void DFSVisitForTree(const Graph& graph, int source, std::vector<Status>& statuses,
//                        std::vector<std::pair<int, int>>& bridges, int& vertex_number, Graph& condens_graph) {
//    statuses[source] = Discovered;
//
//    auto current_number = vertex_number;
//
//    for (auto u: graph[source]) {
//        if (statuses[u] == Undiscovered) {
//            if (std::find(bridges.begin(), bridges.end(),
//                    std::make_pair(std::min(source, u), std::max(source, u))) != bridges.end()) {
//                ++vertex_number;
//                condens_graph[current_number].push_back(vertex_number);
//                condens_graph[vertex_number].push_back(current_number);
//                std::cout << "pep\n";
//
//            }
//            DFSVisitForTree(graph, u, statuses, bridges, vertex_number, condens_graph);
//        }
//    }
//    statuses[source] = Processed;
//}

//void DFS(const Graph& graph, int source, std::vector<Status>& statuses) {
//    statuses[source] = Discovered;
//
//    for (auto u: graph[source]) {
//        if (statuses[u] == Undiscovered) {
//            DFS(graph, u, statuses);
//        }
//    }
//    statuses[source] = Processed;
//}

bool BFS(const Graph& graph) {
    size_t infinity = 1000000000;
    std::queue<int> queue;
    std::vector<int> distance(graph.size(), infinity);
    size_t  from = 0;
    distance[from] = 0;
    size_t cnt = 1;
    queue.push(from);

    while (!queue.empty()) {
        int v = queue.front();
        queue.pop();
        for (auto u: graph[v]) {
            if (distance[u] == infinity) {
                queue.push(u);
                ++cnt;
                distance[u] = distance[v] + 1;
            }
        }
    }
    return cnt < graph.size();
}


int GetCntTonnels(const Graph& graph) {
//    bool many_components = BFS(graph);
    size_t cnt_tonnels = 0;
    std::vector<Status> statuses(graph.size(), Undiscovered);
    auto cnt_last_bridge = 0;
//    int cnt_separate_connected_component = 0;
    int i = 0;
//    for (int i = 0; i < graph.size(); ++i) {
//    if (statuses[i] == Undiscovered) {
//        ++cnt_separate_connected_component;
//        statuses[i] = Discovered;
    cnt_last_bridge = Bridges(graph, i, statuses);
//        std::cout << "cnt = " << cnt_last_bridge << '\n';
//        std::cout << cnt_last_bridge << '\n';
//            if (many_components && cnt_last_bridge - 2 > 0) {
//                cnt_tonnels += (((cnt_last_bridge - 2) + 1) / 2);
//            }
//            if (!many_components) {
    cnt_tonnels += ((cnt_last_bridge + 1) / 2);
//            }
//        }
//    }
//    cnt_tonnels += (many_components ? cnt_separate_connected_component : 0);
    return cnt_tonnels;
}

int main() {
    size_t n_buildings, n_tonnels;
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