#include <iostream>
#include <queue>


using Graph = std::vector<std::vector<std::pair<int, int>>>;

int GetShortestPath(const Graph& graph, int from, int to, int max_dist, int infinity) {
    std::vector<bool> visited(graph.size(), false);
    std::vector<std::queue<int>> queues(max_dist + 1, std::queue<int>());
    std::vector<int> distance(graph.size(), infinity);
    distance[from] = 0;
    int id = 0; // number current queue
    queues[id].push(from);
    int count = 0;
    while (count < max_dist + 3) {
        while (!queues[id].empty()) {
            count = 0;
            int current_vertex = queues[id].front();
            queues[id].pop();
            if (visited[current_vertex]) {
                continue;
            }
            visited[current_vertex] = true;
            for (auto neighbour: graph[current_vertex]) {
                if (distance[neighbour.first] > distance[current_vertex] + neighbour.second) {
                    distance[neighbour.first] = distance[current_vertex] + neighbour.second;
                    queues[(id + neighbour.second) % (max_dist + 1)].push(neighbour.first);
                }
//                visited[neighbour.first] = true;
            }
        }
        ++count;
        id = (id + 1) % (max_dist + 1);
    }
    return ((distance[to] == infinity)?(-1):(distance[to]));
}

int main() {
    int v_cnt;
    int e_cnt;
    std::cin >> v_cnt >> e_cnt;
    int start, finish;
    int max_dist = 0;
    std::cin >> start >> finish;

    Graph graph(v_cnt, std::vector<std::pair<int, int>>());

    for (int i = 0; i < e_cnt; ++i) {
        int from, to;
        std::cin >> from >> to;
        --from, --to;
        int dist;
        std::cin >> dist;
        if (max_dist < dist) {
            max_dist = dist;
        }
        graph[from].push_back(std::make_pair(to, dist));
    }

    std::cout << GetShortestPath(graph, start-1, finish-1, max_dist, max_dist * v_cnt);

    return 0;
}