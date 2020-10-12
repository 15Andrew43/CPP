#include <iostream>
#include <vector>
#include <unordered_set>
#include <queue>

using Graph = std::vector<std::vector<int>>;

enum Color {
    undiscovered = 0,
    discovered = 1,
    processed = 2
};

void BFS(const Graph& graph, int start, std::vector<Color>& colors, std::unordered_set<int>& group) {
    std::queue<int> queue;
    queue.push(start);
    colors[start] = discovered;
    while (! queue.empty()) {
        int vertex = queue.front();
        group.insert(vertex);
        queue.pop();
        for (auto neighbour: graph[vertex]) {
            if (colors[neighbour] == undiscovered) {
                queue.push(neighbour);
                colors[neighbour] = discovered;
            }
        }
        colors[vertex] = processed;
    }
}

std::vector<std::unordered_set<int>> GetCntConnectedComponents(const Graph& graph) {
    std::vector<Color> colors(graph.size(), undiscovered);
    size_t CntConnectedComponents = 0;
    std::vector<std::unordered_set<int>> result;
    for (int vertex = 0; vertex < graph.size(); ++vertex) {
        if (colors[vertex] == undiscovered) {
            std::unordered_set<int> group;
            ++CntConnectedComponents;
            BFS(graph, vertex, colors, group);
            result.push_back(group);
//            for (auto mate: group) {
//                std::cout << mate << ' ';
//            }
//            std::cout << '\n';
        }
    }
    return result;
}


int main() {
    int students_cnt, pair_cnt;
    std::cin >> students_cnt >> pair_cnt;

    Graph graph(students_cnt, std::vector<int>());

    for (int i = 0; i < pair_cnt; ++i) {
        int first_st, second_st;
        std::cin >> first_st >> second_st;
        --first_st;
        --second_st;
        graph[first_st].push_back(second_st);
        graph[second_st].push_back(first_st);
    }

    auto result = GetCntConnectedComponents(graph);

    std::cout << result.size() << '\n';
    for (auto group: result) {
        std::cout << group.size() << '\n';
        for (auto mate: group) {
            std::cout << mate+1 << ' ';
        }
        std::cout << '\n';
    }

    return 0;
}