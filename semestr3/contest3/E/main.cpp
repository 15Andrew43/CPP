#include <iostream>
#include <vector>
#include <set>
#include <tuple>
#include <queue>
#include <algorithm>
//#include <unordered_multiset>
#include <unordered_set>


using Graph = std::vector<std::unordered_multiset<int>>;

void Connect(Graph& graph, int vertex0, int vertex1, int vertex2) {
    graph[vertex0].insert(vertex1);
    graph[vertex0].insert(vertex2);

    graph[vertex1].insert(vertex0);
    graph[vertex1].insert(vertex2);

    graph[vertex2].insert(vertex0);
    graph[vertex2].insert(vertex1);
}

void DeleteEdge(Graph& graph, int vertex0, int vertex1) {
    auto& neighbours0 = graph[vertex0];
    auto& neighbours1 = graph[vertex1];
//    auto it = std::find(neighbours0.begin(), neighbours0.end(), vertex1);
//    std::iter_swap(it, std::prev(neighbours0.end()));
//    neighbours0.pop_back();
    neighbours0.erase(neighbours0.find(vertex1));
//    it = std::find(neighbours1.begin(), neighbours1.end(), vertex0);
//    std::iter_swap(it, std::prev(neighbours1.end()));
//    neighbours1.pop_back();
    neighbours1.erase(neighbours1.find(vertex0));
}


void DeleteConnection(Graph& graph, int vertex0, int vertex1, int vertex2) {
    DeleteEdge(graph, vertex0, vertex1);
    DeleteEdge(graph, vertex0, vertex2);
    DeleteEdge(graph, vertex1, vertex2);
}

bool ExistPath(const Graph& graph, int from, int to0, int to1) {
    int infinity = 1000000;
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
                if (distance[to0] < infinity && distance[to1] < infinity) {
                    return true;
                }
            }
        }
    }
    return false;
}

int main() {
    int n_skyscraper;
    int n_pillows;
    std::cin >> n_skyscraper >> n_pillows;

    Graph graph(n_skyscraper);
    std::vector<std::tuple<int, int, int>> pillows;
    for (int i = 0; i < n_pillows; ++i) {
        int vertex0, vertex1, vertex2;
        std::cin >> vertex0 >> vertex1 >> vertex2;
        --vertex0, --vertex1, --vertex2;
        Connect(graph, vertex0, vertex1, vertex2);
        pillows.push_back(std::tuple<int, int, int>(vertex0, vertex1, vertex2));
    }
    std::vector<int> ness_pillows;
    for (int i = 0; i < pillows.size(); ++i) {
        DeleteConnection(graph, std::get<0>(pillows[i]), std::get<1>(pillows[i]), std::get<2>(pillows[i]));
        if (!ExistPath(graph, std::get<0>(pillows[i]), std::get<1>(pillows[i]), std::get<2>(pillows[i]))) {
            ness_pillows.push_back(i);
        }
        Connect(graph, std::get<0>(pillows[i]), std::get<1>(pillows[i]), std::get<2>(pillows[i]));
    }

    std::cout << ness_pillows.size() << '\n';

    for (auto it = ness_pillows.begin(); it != ness_pillows.end(); ++it) {
        std::cout << *it + 1 << ' ';
    }
    return 0;
}