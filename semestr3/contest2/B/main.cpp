#include <iostream>
#include <vector>
#include <queue>

using Graph = std::vector<std::vector<int>>;


 bool IsBipartite(const Graph& graph) {
     std::queue<int> queue;
     std::vector<int> colors(graph.size(), 0);
     for (int i = 0; i < graph.size(); ++i) {
         if (colors[i] == 0) {
             queue.push(i);
             colors[i] = 1;
             while (!queue.empty()) {
                 int vertex = queue.front();
                 queue.pop();
                 for (auto neighbour: graph[vertex]) {
                     if (colors[neighbour] == 0) {
                         queue.push(neighbour);
                         colors[neighbour] = colors[vertex] * (-1);
                     } else if (colors[neighbour] == colors[vertex]) {
                         return false;
                     }
                 }
             }
         }
     }
     return true;
 }


int main() {
    int students_cnt, student_pair_cnt;
    std::cin >> students_cnt >> student_pair_cnt;

    Graph graph(students_cnt, std::vector<int>());

    for (int i = 0; i < student_pair_cnt; ++i) {
        int v_from, v_to;
        std::cin >> v_from >> v_to;
        graph[v_from - 1].push_back(v_to - 1);
        graph[v_to - 1].push_back(v_from - 1);
        }
    if (IsBipartite(graph)) {
        std::cout << "YES";
    } else {
        std::cout << "NO";
    }
    return 0;
}
