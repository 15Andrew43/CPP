#include <vector>
#include <algorithm>
#include <stdexcept>
#include "graph.h"

using vertex_t = int;

AdjacecyListsGraph::AdjacecyListsGraph(const std::vector<std::vector<vertex_t>>& graph) : graph_(graph) {
    for (auto neighbours: graph_) {
        edge_cnt_ += neighbours.size();
    }
}
AdjacecyListsGraph::AdjacecyListsGraph(vertex_t vertex_cnt) : graph_(vertex_cnt, std::vector<vertex_t>()) {}

vertex_t AdjacecyListsGraph::GetCntVertex() const noexcept {
    return graph_.size();
}

vertex_t AdjacecyListsGraph::GetCntEdge() const noexcept {
    return edge_cnt_;
}

void AdjacecyListsGraph::AddEdge(vertex_t from, vertex_t to) {
    if (std::min(from, to) < 0) {
        throw std::invalid_argument("numbers of the vertexes must be >= 0, when you try to add a new edge");
    }
    graph_[from].push_back(to);
    ++edge_cnt_;
}
void AdjacecyListsGraph::DeleteEdge(vertex_t from, vertex_t to) {
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

bool AdjacecyListsGraph::EdgeExist(vertex_t from, vertex_t to) const noexcept {
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
bool AdjacecyListsGraph::VertexExist(vertex_t vertex) const noexcept {
    if (vertex < 0 || vertex > GetCntVertex() - 1) {
        return false;
    }
    return true;
}
std::vector<vertex_t> AdjacecyListsGraph::GetNeighbours(vertex_t vertex) const noexcept {
    if (VertexExist(vertex)) {
        return graph_[vertex];
    }
    return {};
}
std::vector<std::vector<vertex_t>> AdjacecyListsGraph::GetTransposed() const noexcept {
    std::vector<std::vector<vertex_t>> transposed_graph(graph_.size(), std::vector<vertex_t>());
    for (vertex_t vertex = 0; vertex < graph_.size(); ++vertex) {
        for (auto neighbour: GetNeighbours(vertex)) {
            transposed_graph[neighbour].push_back(vertex);
        }
    }
    return transposed_graph;
}
void AdjacecyListsGraph::Transpose() noexcept {
    graph_ = GetTransposed();
}

void AdjacecyListsGraph::PrintGraph() const noexcept {
    for (vertex_t i = 0; i < graph_.size(); ++i) {
        std::cout << i << " : ";
        for (auto j = graph_[i].begin(); j != graph_[i].end(); ++j) {
            std::cout << *j << ' ';
        }
        std::cout << '\n';

    }
}

std::ostream& operator<<(std::ostream& os, const AdjacecyListsGraph& graph) {
    graph.PrintGraph();
    return os;
}



AdjacencyMatrixGraph::AdjacencyMatrixGraph(const std::vector<std::vector<vertex_t>>& graph) : graph_(graph) {
    for (auto neighbours: graph_) {
        edge_cnt_ += neighbours.size();
    }
}
AdjacencyMatrixGraph::AdjacencyMatrixGraph(vertex_t vertex_cnt) : graph_(vertex_cnt, std::vector<vertex_t>(vertex_cnt, 0)) {}

vertex_t AdjacencyMatrixGraph::GetCntVertex() const noexcept {
    return graph_.size();
}
vertex_t AdjacencyMatrixGraph::GetCntEdge() const noexcept {
    return edge_cnt_;
}
void AdjacencyMatrixGraph::AddEdge(vertex_t from, vertex_t to) {
    if (std::min(from, to) < 0) {
        throw std::invalid_argument("numbers of the vertexes must be >= 0, when you try to add a new edge");
    }
    graph_[from][to] = 1;
    ++edge_cnt_;
}
void AdjacencyMatrixGraph::DeleteEdge(vertex_t from, vertex_t to) {
    if (! EdgeExist(from, to)) {
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
    if (vertex < 0 || vertex > GetCntVertex() - 1) {
        return false;
    }
    return true;
}
std::vector<vertex_t> AdjacencyMatrixGraph::GetNeighbours(vertex_t vertex) const noexcept {
    std::vector<vertex_t> neighbours;
    if (VertexExist(vertex)) {
        for (vertex_t j = 0; j < GetCntVertex(); ++j) {
            if (graph_[vertex][j] != 0) {
                neighbours.push_back(j);
            }
        }
    }
    return neighbours;
}

std::vector<std::vector<vertex_t>> AdjacencyMatrixGraph::GetTransposed() const noexcept {
    AdjacencyMatrixGraph transposed_graph(graph_);
    transposed_graph.Transpose();
    return transposed_graph.graph_;
}
void AdjacencyMatrixGraph::Transpose() noexcept {
    for (vertex_t i = 0; i < GetCntVertex(); ++i) {
        for (vertex_t j = 0; j < i; ++j) {
            std::swap(graph_[i][j], graph_[j][i]);
        }
    }
}

void AdjacencyMatrixGraph::PrintGraph() const noexcept {
    for (vertex_t i = 0; i < graph_.size(); ++i) {
        std::cout << i << " : ";
        for (auto j = graph_[i].begin(); j != graph_[i].end(); ++j) {
            std::cout << *j << ' ';
        }
        std::cout << '\n';
    }
}

std::ostream& operator<<(std::ostream& os, const AdjacencyMatrixGraph& graph) {
    graph.PrintGraph();
    return os;
}