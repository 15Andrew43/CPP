#include <vector>
#include <algorithm>
#include <stdexcept>
#include "graph.h"

std::ostream& operator<<(std::ostream& os, const Graph& graph) {
    for (vertex_t vertex = 0; vertex < graph.GetCntVertex(); ++vertex) {
        std::cout << vertex << " : ";
        for (auto neighbour: graph.GetNeighbours(vertex)) {
            std::cout << neighbour << ' ';
        }
        std::cout << '\n';
    }
    return os;
}



AdjacencyListsGraph::AdjacencyListsGraph(const std::vector<std::vector<vertex_t>>& graph) : graph_(graph) {
    for (const auto& neighbours: graph_) {
        edge_cnt_ += neighbours.size();
    }
}

AdjacencyListsGraph::AdjacencyListsGraph(vertex_t vertex_cnt) : graph_(vertex_cnt) {
}

vertex_t AdjacencyListsGraph::GetCntVertex() const noexcept {
    return graph_.size();
}

vertex_t AdjacencyListsGraph::GetCntEdge() const noexcept {
    return edge_cnt_;
}

void AdjacencyListsGraph::AddEdge(vertex_t from, vertex_t to) {
    graph_.at(from).push_back(to);
    ++edge_cnt_;
}

void AdjacencyListsGraph::DeleteEdge(vertex_t from, vertex_t to) {
    if (!EdgeExist(from, to)) {
        return;
    }
    auto& neighbours_from = graph_[from];
    auto iter_to = std::find(neighbours_from.begin(), neighbours_from.end(), to);
    if (iter_to != neighbours_from.end()) {
        std::iter_swap(iter_to, std::prev(neighbours_from.end()));
        neighbours_from.pop_back();
        --edge_cnt_;
    }
}

bool AdjacencyListsGraph::EdgeExist(vertex_t from, vertex_t to) const noexcept {
    if (from > GetCntVertex() - 1 || to > GetCntVertex() - 1 || from < 0 || to < 0) {
        return false;
    }
    auto& neighbours_from = graph_[from];
    auto it = std::find(neighbours_from.begin(), neighbours_from.end(), to);
    return it != neighbours_from.end();
}

bool AdjacencyListsGraph::VertexExist(vertex_t vertex) const noexcept {
    if (vertex < 0 || vertex > GetCntVertex() - 1) {
        return false;
    }
    return true;
}

std::vector<vertex_t> AdjacencyListsGraph::GetNeighbours(vertex_t vertex) const {
    try {
        return graph_.at(vertex);
    } catch (const std::exception&) {
        return {};
    }
}

void AdjacencyListsGraph::Transpose() {
    std::vector<std::vector<vertex_t>> transposed_graph(graph_.size());
    for (vertex_t vertex = 0; vertex < graph_.size(); ++vertex) {
        for (const auto& neighbour: GetNeighbours(vertex)) {
            transposed_graph[neighbour].push_back(vertex);
        }
    }
    graph_ = std::move(transposed_graph);
//    graph_.swap(transposed_graph);
}

std::shared_ptr<Graph> AdjacencyListsGraph::Copy() const {
    return std::make_shared<AdjacencyListsGraph>(graph_);
}

//AdjacencyListsGraph::~AdjacencyListsGraph() {
//    std::cout << "Ppe\n";
//}


AdjacencyMatrixGraph::AdjacencyMatrixGraph(const std::vector<std::vector<vertex_t>>& graph) : graph_(graph) {
    for (const auto& neighbours: graph_) {
        edge_cnt_ += neighbours.size();
    }
}

AdjacencyMatrixGraph::AdjacencyMatrixGraph(vertex_t vertex_cnt) : graph_(vertex_cnt, std::vector<vertex_t>(vertex_cnt, 0)) {
}

vertex_t AdjacencyMatrixGraph::GetCntVertex() const noexcept {
    return graph_.size();
}

vertex_t AdjacencyMatrixGraph::GetCntEdge() const noexcept {
    return edge_cnt_;
}

void AdjacencyMatrixGraph::AddEdge(vertex_t from, vertex_t to) {
    graph_.at(from).at(to) = 1;
    ++edge_cnt_;
}

void AdjacencyMatrixGraph::DeleteEdge(vertex_t from, vertex_t to) {
    if (!EdgeExist(from, to)) {
        return;
    }
    graph_[from][to] = 0;
    --edge_cnt_;
}

bool AdjacencyMatrixGraph::EdgeExist(vertex_t from, vertex_t to) const noexcept {
    if (from > GetCntVertex() - 1 || to > GetCntVertex() - 1 || from < 0 || to < 0) {
        return false;
    }
    if (graph_[from][to] != 0) {
        return true;
    }
    return false;
}

bool AdjacencyMatrixGraph::VertexExist(vertex_t vertex) const noexcept {
    return vertex >= 0 && vertex < GetCntVertex();
}

std::vector<vertex_t> AdjacencyMatrixGraph::GetNeighbours(vertex_t vertex) const {
    std::vector<vertex_t> neighbours;
    try {
        for (vertex_t j = 0; j < GetCntVertex(); ++j) {
            if (graph_.at(vertex)[j] != 0) {
                neighbours.push_back(j);
            }
        }
    } catch (const std::exception&) {
    }
    return neighbours;
}

void AdjacencyMatrixGraph::Transpose() {
    for (vertex_t i = 0; i < GetCntVertex(); ++i) {
        for (vertex_t j = 0; j < i; ++j) {
            std::swap(graph_[i][j], graph_[j][i]);
        }
    }
}

std::shared_ptr<Graph> AdjacencyMatrixGraph::Copy() const {
    return std::make_shared<AdjacencyMatrixGraph>(graph_);
}

//AdjacencyMatrixGraph::~AdjacencyMatrixGraph() {
//    std::cout << "Ppe\n";
//}
