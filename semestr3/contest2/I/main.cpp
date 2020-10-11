#include <iostream>
#include <vector>
#include <deque>

using Graph = std::vector<std::vector<std::pair<int, int>>>;

int GetShortestPath(const Graph& graph, int from, int to, const int infinity) {
    std::deque<int> deque;
    std::vector<int> distance(graph.size(), infinity);
    deque.push_back(from);
    distance[from] = 0;
    while (! deque.empty()) {
        int vertex = deque.front();
        deque.pop_front();
        for (auto neighbour: graph[vertex]) {
            if (distance[neighbour.first] > distance[vertex] + neighbour.second) {
                distance[neighbour.first] = distance[vertex] + neighbour.second;
                if (neighbour.second == 0) {
                    deque.push_front(neighbour.first);
                } else {
                    deque.push_back(neighbour.first);
                }
            }
        }
    }
    return (distance[to] == infinity)?(-1):(distance[to]);
}

int main() {
    int v_cnt, e_cnt;
    std::cin >> v_cnt >> e_cnt;
    Graph graph(v_cnt, std::vector<std::pair<int, int>>());
    for (int i = 0; i < e_cnt; ++i) {
        int from, to;
        std::cin >> from >> to;
        --from;
        --to;
        graph[from].push_back(std::make_pair(to, 0));
        graph[to].push_back(std::make_pair(from, 1));
    }

    int question_cnt;
    std::cin >> question_cnt;
    for (int i = 0; i < question_cnt; ++i) {
        int from, to;
        std::cin >> from >> to;
        std::cout << GetShortestPath(graph, from-1, to-1, 1000000) << '\n';
    }

    return 0;
}