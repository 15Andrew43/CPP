#include <iostream>
#include <vector>


class Graph {
private:
    std::vector<std::vector<int>> graph_;
public:
    explicit Graph(int N) {
        graph_.reserve(N);
        for (int i = 0; i < N; ++i) {
            graph_[i] = std::vector<int>();
        }
    }
    void NewEdge(int a, int b) {
        graph_[a-1].push_back(b-1);
        graph_[b-1].push_back(a-1);
    }
    const std::vector<int> getAdjacentVertexes(int a) {
        return graph_[a-1];
    }
};


int main() {
    int N;
    std::cin >> N;
    Graph graph(N);
    int K;
    std::cin >> K;
    int operation;
    for (int i = 0; i < K; ++i) {
        std::cin >> operation;
        switch (operation) {
            case 1:
                int a, b;
                std::cin >> a >> b;
                graph.NewEdge(a, b);
                break;
            case 2:
                int c;
                std::cin >> c;
                for (int v : graph.getAdjacentVertexes(c)) {
                    std::cout << v + 1 << ' ';
                }
                std::cout << '\n';
                break;
        }
    }
    return 0;
}