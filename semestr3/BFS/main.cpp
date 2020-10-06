#include <iostream>
#include <vector>
#include <queue>

/*
 * задача вывести минимальный путь до вершины фром к вершине ту
 */

using Graph = std::vector<std::vector<int>>;
#define INFINITY 100500
std::vector<int> GetShortestPath(const Graph& g, int from, int to) {
    std::queue<int> q;
    std::vector<int> distance(g.size());
    std::vector<int> parent(g.size());
    q.push(from);
    while (not q.empty()) {
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
    std::vector<int> path(distance.size());
    while (from != to) {
        path.push_back(from);
        from = parent[from];
    }
    path.push_back(to);
    return {path.rbegin(), path.rend()};
}

int main() {
    int n;
    std::cin >> n;
    Graph G;
    for (int i = 0; i < n; ++i) {
//        std::vector<int> g;
        for (int j = 0; i < n; ++j) {
            int v;
            std::cin >> v;
            if (v != 0) {
                G[i].push_back(j);
                G[j].push_back(i);
            }
        }
    }

    std::vector<int> path = GetShortestPath(G, 0, 1);
    std::cout << "Hello, World!" << std::endl;
    return 0;
}