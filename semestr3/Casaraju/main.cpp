#include <iostream>
#include <vector>

// -Wall -Werror

std::vector<int> DFS(const Graph& g, int v, std::vector<int>answer) {
    ;
}

std::vector<std::vector<int>> FindStronglyConnectedComponents(const Graph& g) {
    auto answer = TopSort(); // топ сорт без прверик циклов
    Graph new_g = Transpose(g);
    std::vector<std::vector<int>> StrongConnectedComponents;
    for (auto v: answer) {
        StrongConnectedComponents.push_back(DFS(new_g, v, answer, ));
    }
    return StrongConnectedComponents;
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}