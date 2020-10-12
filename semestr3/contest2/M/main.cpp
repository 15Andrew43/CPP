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
            if (sorted_array[0] == -1) {
                return;
            }
        } else if (colors[neighbour] == discovered) {
            sorted_array = {-1};
            return;
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
            if (sorted_array[0] == -1) {
                return sorted_array;
            }
        }
    }
    return sorted_array;
}


int main() {
    int v_cnt, e_cnt;
    std::cin >> v_cnt >> e_cnt;

    Graph graph(v_cnt, std::vector<int>());
    for (int i = 0; i < e_cnt; ++i) {
        int from, to;
        std::cin >> from >> to;
        --from;
        --to;
        graph[from].push_back(to);
    }

    auto sorted_arr = TopSort(graph);
    if (sorted_arr[0] != -1) {
        for (auto vertex: sorted_arr) {
            std::cout << vertex + 1 << ' ';
        }
    } else {
        std::cout << -1;
    }
    return 0;
}
/*
5 5
1 2
2 3
3 1
1 4
2 5
 */