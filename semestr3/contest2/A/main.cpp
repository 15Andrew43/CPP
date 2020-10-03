#include <iostream>
#include <vector>
#include <queue>

using Graph = std::vector<std::vector<int>>;
#define INFINITY 1000000


 std::vector<int> GetShortestPath(const Graph& g, int from, int to) {
    std::queue<int> q;
    std::vector<int> distance(g.size(), INFINITY);
    std::vector<int> parent(g.size());
    parent[from] = -1;
    distance[from] = 0;
    q.push(from);

    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (auto u: g[v]) {
            if (distance[u] == INFINITY) {
                q.push(u);
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

bool Contain(const std::vector<int>& g, int v) {
    for (auto it = g.begin(); it != g.end(); ++it) {
        if (*it == v) {
            return true;
        }
    }
    return false;
}

int main() {
    int n, m;
    std::cin >> n >> m;
    int a, b;
    std::cin >> a >> b;

    Graph G(n, std::vector<int>());

    for (int i = 0; i < m; ++i) {
        int v_from, v_to;
        std::cin >> v_from >> v_to;
        if (!Contain(G[v_from-1], v_to-1)) {
            G[v_from - 1].push_back(v_to - 1);
            G[v_to - 1].push_back(v_from - 1);
        }
    }

    std::vector<int> path = GetShortestPath(G, a-1, b-1);
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
