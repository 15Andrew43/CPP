#include <iostream>
#include <vector>
#include <deque>
#include <exception>
#include <algorithm>
#include <stdexcept>

class AdjacecyListsGraph {
    std::vector<std::vector<size_t>> graph_;
public:
    AdjacecyListsGraph(const std::vector<std::vector<size_t>>& g) : graph_(g) {}
    AdjacecyListsGraph() = default;

    std::vector<size_t > operator[](int i) const {
        return graph_[i];
    }
    std::vector<size_t >& operator[](int i) {
        return graph_[i];
    }

    size_t getCntVertex() const noexcept {
        return graph_.size();
    }
    size_t getCntEdge() const noexcept {
        size_t edge_cnt = 0;
        for (auto neighbours: graph_) {
            edge_cnt += neighbours.size();
        }
        return edge_cnt;
    }
    void addEdge(int from, int to) {
        if (std::min(from, to) < 0) {
            throw std::invalid_argument("numbers of the vertexes must be >= 0, when you try to add a new edge");
        }
        size_t new_cnt_vertex = std::max(from, to);
        ++new_cnt_vertex;
        size_t  old_cnt_vertex = getCntVertex();
        while (old_cnt_vertex < new_cnt_vertex) {
            graph_.push_back(std::vector<size_t >());
            ++old_cnt_vertex;
        }
        graph_[from].push_back(to);
    }
    void deleteEdge(int from, int to) {
        if (! EdgeExist(from, to)) {
            return;
        }
        auto iter_to = std::find(graph_[from].begin(), graph_[from].end(), to);
        if (iter_to != graph_[from].end()) {
            graph_[from].erase(iter_to);
        }
    }

    bool EdgeExist(int from, int to) const noexcept {
        if (from > getCntVertex() - 1 || to > getCntVertex() - 1 || from < 0 || to < 0) {
            return false;
        }
        auto it = std::find(graph_[from].begin(), graph_[from].end(), to);
        if (it != graph_[from].end()) {
            return true;
        }
        return false;
    }
    bool VertexExist(int vertex) const noexcept {
        if (vertex < 0 || vertex > getCntVertex() - 1) {
            return false;
        }
        return true;
    }
    std::vector<size_t> getNeighbours(int vertex) const noexcept {
        if (VertexExist(vertex)) {
            return graph_[vertex];
        }
        return std::vector<size_t>();
    }
    std::vector<std::vector<size_t>> getTransposed() const noexcept {
        std::vector<std::vector<size_t>> transposed_graph(graph_.size(), std::vector<size_t>());
        for (size_t vertex = 0; vertex < graph_.size(); ++vertex) {
            for (auto neighbour: getNeighbours(vertex)) {
                transposed_graph[neighbour].push_back(vertex);
            }
        }
        return transposed_graph;
    }
    void Transpose() noexcept {
        graph_ = getTransposed();
    }

    void printGraph() const noexcept {
        for (int i = 0; i < graph_.size(); ++i) {
            std::cout << i << " : ";
            for (auto j = graph_[i].begin(); j != graph_[i].end(); ++j) {
                std::cout << *j << ' ';
            }
            std::cout << '\n';

        }
    }
};

enum Color {
    undiscovered = 0,
    discovered = 1,
    processed = 2
};

void DfsVisit(const AdjacecyListsGraph& graph, int vertex, std::deque<int>& sorted_array, std::vector<Color>& colors) {
    colors[vertex] = discovered;
    for (auto neighbour: graph[vertex]) {
        if (colors[neighbour] == undiscovered) {
            DfsVisit(graph, neighbour, sorted_array, colors);
        }
    }
    colors[vertex] = processed;
    sorted_array.push_front(vertex);
}

std::deque<int> TopSort(const AdjacecyListsGraph& graph) {
    std::vector<Color> colors(graph.getCntVertex(), undiscovered);
    std::deque<int> sorted_array;
    for (int vertex = 0; vertex < graph.getCntVertex(); ++vertex) {
        if (colors[vertex] == undiscovered) {
            DfsVisit(graph, vertex, sorted_array, colors);
        }
    }
    return sorted_array;
}

std::vector<std::deque<int>> FindStronglyConnectedComponents(const AdjacecyListsGraph& graph) {
    auto answer = TopSort(graph); // топ сорт без прверик циклов
    AdjacecyListsGraph new_graph = graph.getTransposed();
    std::vector<std::deque<int>> StrongConnectedComponents;
    std::vector<Color> colors(new_graph.getCntVertex(), undiscovered);

    for (auto v: answer) {
        std::deque<int> sorted_array;
        if (colors[v] == undiscovered) {
            DfsVisit(new_graph, v, sorted_array, colors);
            StrongConnectedComponents.push_back(sorted_array);
        }
    }
    return StrongConnectedComponents;
}

int main() {
    int v_cnt, e_cnt;
    std::cin >> v_cnt >> e_cnt;

    std::vector<std::vector<size_t >> vector(v_cnt, std::vector<size_t >());

    for (int i = 0; i < e_cnt; ++i) {
        int from, to;
        std::cin >> from >> to;
        --from;
        --to;
        vector[from].push_back(to);
    }
    AdjacecyListsGraph graph(vector);

    auto SCCs = FindStronglyConnectedComponents(graph);
    std::cout << SCCs.size() << '\n';


    std::vector<int> answer(graph.getCntVertex());
    int number = 1;
    for (auto SCC: SCCs) {
        for (auto vertex: SCC) {
            answer[vertex] = number;
        }
        ++number;
    }
    for (auto number_SCC: answer) {
        std::cout << number_SCC << ' ';
    }
    return 0;
}