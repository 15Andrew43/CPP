#include <iostream>
#include <vector>
#include <list>

enum Color {
    undiscovered = 0,
    discovered = 1,
    processed = 2,
};

using std::vector<std::list<int>> = Graph

void DFSVisit(const Graph& graph, int source, std::vector<Color>& colors) {
    colors[source] = discovered;
    for (auto u: graph[source]) {
        int node = u;
        if (colors[node] == undiscovered) {
            DFSVisit(graph, node, colors);
        }
    }
    colors[source] = processed;
}


int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}