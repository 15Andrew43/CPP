#include <iostream>
#include <vector>
#include <queue>

using Graph = std::vector<std::vector<int>>;

int INFINITY = 1000000;

 std::vector<int> GetShortestPath(const Graph& graph, int from, int to) {
    std::queue<int> queue;
    std::vector<int> distance(graph.size(), INFINITY);
    std::vector<int> parent(graph.size());
    parent[from] = -1;
    distance[from] = 0;
    queue.push(from);

    while (!queue.empty()) {
        int v = queue.front();
        queue.pop();
        for (auto u: graph[v]) {
            if (distance[u] == INFINITY) {
                queue.push(u);
                distance[u] = distance[v] + 1;
                parent[u] = v;
            }
        }
    }

    std::vector<int> path;
    if (distance[to] == INFINITY) {
        path.push_back(-1);
        return path;
    }
    while (to != from) {
        path.push_back(to);
        to = parent[to];
    }
    path.push_back(from);
    return {path.rbegin(), path.rend()};
}

bool Contain(const std::vector<int>& array, int value) {
    for (auto it = array.begin(); it != array.end(); ++it) {
        if (*it == value) {
            return true;
        }
    }
    return false;
}

int main() {
    int v_cnt, e_cnt;
    std::cin >> v_cnt >> e_cnt;
    int start, finish;
    std::cin >> start >> finish;

    Graph graph(v_cnt, std::vector<int>());

    for (int i = 0; i < e_cnt; ++i) {
        int v_from, v_to;
        std::cin >> v_from >> v_to;
        if (!Contain(graph[v_from-1], v_to-1)) {
            graph[v_from - 1].push_back(v_to - 1);
            graph[v_to - 1].push_back(v_from - 1);
        }
    }

    std::vector<int> path = GetShortestPath(graph, start-1, finish-1);
    if (path[0] == -1) {
        std::cout << -1;
    } else {
        std::cout << path.size() - 1 << '\n';
        for (auto v: path) {
            std::cout << v + 1 << ' ';
        }
    }
    return 0;
}
