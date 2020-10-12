#include <iostream>
#include <vector>
#include <deque>

using Graph = std::vector<std::vector<int>>;

enum Color {
    undiscovered = 0,
    discovered = 1,
    processed = 2
};

void DfsVisit(const Graph& graph, int vertex, std::deque<int>& sorted_array, std::vector<Color>& colors) {
    colors[vertex] = discovered;
    for (auto neighbour: graph[vertex]) {
        if (colors[neighbour] == undiscovered) {
            DfsVisit(graph, neighbour, sorted_array, colors);
        }
    }
    colors[vertex] = processed;
    sorted_array.push_front(vertex);
}

std::deque<int> TopSort(const Graph& graph) {
    std::vector<Color> colors(graph.size(), undiscovered);
    std::deque<int> sorted_array;
    for (int vertex = 0; vertex < graph.size(); ++vertex) {
        if (colors[vertex] == undiscovered) {
            DfsVisit(graph, vertex, sorted_array, colors);
        }
    }
    return sorted_array;
}

int GetMinCntConnectedComponent(const Graph& graph) {
    auto queue = TopSort(graph);
    std::vector<Color> colors(queue.size(), undiscovered);
    int CntConnectedComponent = 0;
    for (auto vertex: queue) {
        if (colors[vertex] == undiscovered) {
            ++CntConnectedComponent;
            std::deque<int> garbage;
            DfsVisit(graph, vertex, garbage, colors);
        }
    }
    return CntConnectedComponent;
}

int main() {
    int pigs_cnt;
    std::cin >> pigs_cnt;

    Graph graph(pigs_cnt, std::vector<int>());
    for (int i = 0; i < pigs_cnt; ++i) {
        int where_key;
        std::cin >> where_key;
        --where_key;
        graph[where_key].push_back(i);
    }

    std::cout << GetMinCntConnectedComponent(graph);
    return 0;
}