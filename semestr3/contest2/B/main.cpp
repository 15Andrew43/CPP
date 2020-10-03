#include <iostream>
#include <vector>
#include <queue>

using Graph = std::vector<std::vector<int>>;


 bool IsBipartite(const Graph& g) {
     std::queue<int> q;
     std::vector<int> colors(g.size(), 0);
     for (int i = 0; i < g.size(); ++i) {
         if (colors[i] == 0) {
             q.push(i);
             colors[i] = 1;
             while (!q.empty()) {
                 int v = q.front();
                 q.pop();
                 for (auto u: g[v]) {
                     if (colors[u] == 0) {
                         q.push(u);
                         colors[u] = colors[v] * (-1);
                     } else if (colors[u] == colors[v]) {
                         return false;
                     }
                 }
             }
         }
     }
     return true;
 }


int main() {
    int n, m;
    std::cin >> n >> m;

    Graph G(n, std::vector<int>());

    for (int i = 0; i < m; ++i) {
        int v_from, v_to;
        std::cin >> v_from >> v_to;
        G[v_from - 1].push_back(v_to - 1);
        G[v_to - 1].push_back(v_from - 1);
        }
    if (IsBipartite(G)) {
        std::cout << "YES";
    } else {
        std::cout << "NO";
    }
    return 0;
}
