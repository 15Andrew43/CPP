#include <iostream>
#include <vector>
#include <deque>
#include <exception>
#include <algorithm>
#include <stdexcept>

using vertex_t = int;

class AdjacecyListsGraph {
    std::vector<std::vector<vertex_t>> graph_;
    vertex_t edge_cnt_ = 0;

public:
    AdjacecyListsGraph(const std::vector<std::vector<vertex_t>>& graph) : graph_(graph) {
        for (auto neighbours: graph_) {
            edge_cnt_ += neighbours.size();
        }
    }
    AdjacecyListsGraph(vertex_t vertex_cnt) : graph_(vertex_cnt, std::vector<vertex_t>()) {}

    vertex_t GetCntVertex() const noexcept {
        return graph_.size();
    }

    vertex_t GetCntEdge() const noexcept {
        return edge_cnt_;
    }

    void AddEdge(vertex_t from, vertex_t to) {
        if (std::min(from, to) < 0) {
            throw std::invalid_argument("numbers of the vertexes must be >= 0, when you try to add a new edge");
        }
        graph_[from].push_back(to);
        ++edge_cnt_;
    }
    void DeleteEdge(vertex_t from, vertex_t to) {
        if (! EdgeExist(from, to)) {
            return;
        }
        auto& neighbours_from = graph_[from];
        auto iter_to = std::find(neighbours_from.begin(), neighbours_from.end(), to);
        if (iter_to != neighbours_from.end()) {
//            graph_[from].erase(iter_to);
            std::swap(*iter_to, *std::prev(neighbours_from.end()));
            neighbours_from.pop_back();
            --edge_cnt_;
        }
    }

    bool EdgeExist(vertex_t from, vertex_t to) const noexcept {
        if (from > GetCntVertex() - 1 || to > GetCntVertex() - 1 || from < 0 || to < 0) {
            return false;
        }
        auto& neighbours_from = graph_[from];
        auto it = std::find(neighbours_from.begin(), neighbours_from.end(), to);
        if (it != neighbours_from.end()) {
            return true;
        }
        return false;
    }
    bool VertexExist(vertex_t vertex) const noexcept {
        if (vertex < 0 || vertex > GetCntVertex() - 1) {
            return false;
        }
        return true;
    }
    std::vector<vertex_t> GetNeighbours(vertex_t vertex) const noexcept {
        if (VertexExist(vertex)) {
            return graph_[vertex];
        }
        return {};
    }
    std::vector<std::vector<vertex_t>> GetTransposed() const noexcept {
        std::vector<std::vector<vertex_t>> transposed_graph(graph_.size(), std::vector<vertex_t>());
        for (vertex_t vertex = 0; vertex < graph_.size(); ++vertex) {
            for (auto neighbour: GetNeighbours(vertex)) {
                transposed_graph[neighbour].push_back(vertex);
            }
        }
        return transposed_graph;
    }
    void Transpose() noexcept {
        graph_ = GetTransposed();
    }

    void PrintGraph() const noexcept {
        for (vertex_t i = 0; i < graph_.size(); ++i) {
            std::cout << i << " : ";
            for (auto j = graph_[i].begin(); j != graph_[i].end(); ++j) {
                std::cout << *j << ' ';
            }
            std::cout << '\n';

        }
    }
};

std::ostream& operator<<(std::ostream& os, const AdjacecyListsGraph& graph) {
    graph.PrintGraph();
    return os;
}

enum Status {
    kUndiscovered = 0,
    kDiscovered = 1,
    Processed = 2
};

void AllocateSCC(const AdjacecyListsGraph& graph, int vertex, std::vector<int>& sorted_array, std::vector<Status>& statuses) {
    statuses[vertex] = kDiscovered;
    for (auto neighbour: graph.GetNeighbours(vertex)) {
        if (statuses[neighbour] == kUndiscovered) {
            AllocateSCC(graph, neighbour, sorted_array, statuses);
        }
    }
    statuses[vertex] = Processed;
    sorted_array.push_back(vertex);
}

std::vector<int> TopSortWithoutCheckCycles(const AdjacecyListsGraph& graph) {
    std::vector<Status> statuses(graph.GetCntVertex(), kUndiscovered);
    std::vector<int> sorted_array;
    for (int vertex = 0; vertex < graph.GetCntVertex(); ++vertex) {
        if (statuses[vertex] == kUndiscovered) {
            AllocateSCC(graph, vertex, sorted_array, statuses);
        }
    }
    return {sorted_array.rbegin(), sorted_array.rend()};
}

std::vector<std::vector<int>> GetAllocationComponents (const AdjacecyListsGraph& graph, const std::vector<int>& answer) {
    std::vector<std::vector<int>> strong_connected_components;
    std::vector<Status> statuses(graph.GetCntVertex(), kUndiscovered);
    for (auto v: answer) {
        std::vector<int> sorted_array;
        if (statuses[v] == kUndiscovered) {
            AllocateSCC(graph, v, sorted_array, statuses);
            strong_connected_components.push_back(sorted_array);
        }
    }
    return strong_connected_components;
}

std::vector<std::vector<int>> FindStronglyConnectedComponents(const AdjacecyListsGraph& graph) {
    auto answer = TopSortWithoutCheckCycles(graph); // топ сорт без прверик циклов
    AdjacecyListsGraph new_graph = graph.GetTransposed();
    auto strong_connected_components = GetAllocationComponents(new_graph, answer); //std::vector<std::vector<int>>
    return strong_connected_components;
}

int main() {
    int v_cnt, e_cnt;
    std::cin >> v_cnt >> e_cnt;

    std::vector<std::vector<vertex_t>> vector(v_cnt, std::vector<vertex_t>());

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


    std::vector<int> answer(graph.GetCntVertex());
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