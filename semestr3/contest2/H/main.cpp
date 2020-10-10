#include <iostream>
#include <queue>

int infinity = 1000000;
using Graph = std::vector<std::vector<int>>;

int GetShortestPath(const Graph& graph, int from, int to) {
    std::queue<int> queue;
    std::vector<int> distance(graph.size(), infinity);
    distance[from] = 0;
    queue.push(from);

    while (!queue.empty()) {
        int v = queue.front();
        queue.pop();
        for (auto u: graph[v]) {
            if (distance[u] == infinity) {
                queue.push(u);
                distance[u] = distance[v] + 1;
            }
        }
    }
    return ((distance[to] == infinity)?(-1):(distance[to]));
}

int main() {
    int v_cnt;
    int e_cnt;
    std::cin >> v_cnt >> e_cnt;
    int start, finish;
    std::cin >> start >> finish;

    Graph graph(v_cnt, std::vector<int>());

    for (int i = 0; i < e_cnt; ++i) {
        int from, to;
        std::cin >> from >> to;
        --from, --to;
        int dist;
        std::cin >> dist;
        if (dist == 1) {
            graph[from].push_back(to);
        } else {
            int new_v_cnt = v_cnt;
            while (new_v_cnt < v_cnt + dist - 1) {
                graph[from].push_back(new_v_cnt);
                graph.push_back(std::vector<int>());
                from = new_v_cnt;
                ++new_v_cnt;
            }
            graph[from].push_back(to);
            v_cnt = new_v_cnt;
        }
    }

    std::cout << GetShortestPath(graph, start-1, finish-1);

    return 0;
}