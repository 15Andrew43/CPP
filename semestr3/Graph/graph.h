#ifndef GRAPH_GRAPH_H
#define GRAPH_GRAPH_H

#include <vector>
#include <iostream>

using vertex_t = int;

class Graph {
public:
    virtual vertex_t GetCntVertex() const noexcept = 0;
    virtual vertex_t GetCntEdge() const noexcept = 0;
    virtual void AddEdge(vertex_t from, vertex_t to) = 0;
    virtual void DeleteEdge(vertex_t from, vertex_t to) = 0;
    virtual bool EdgeExist(vertex_t from, vertex_t to) const noexcept = 0;
    virtual bool VertexExist(vertex_t vertex) const noexcept = 0;
    virtual std::vector<vertex_t> GetNeighbours(vertex_t vertex) const noexcept = 0;
    virtual std::vector<std::vector<vertex_t>> GetTransposed() const noexcept = 0;
    virtual void Transpose() noexcept = 0;
    virtual void PrintGraph() const noexcept = 0;
};


class AdjacecyListsGraph : public Graph {
    std::vector<std::vector<vertex_t>> graph_;
    vertex_t edge_cnt_ = 0;

public:
    AdjacecyListsGraph(const std::vector<std::vector<vertex_t>>& graph);
    AdjacecyListsGraph(vertex_t vertex_cnt);

    vertex_t GetCntVertex() const noexcept;

    vertex_t GetCntEdge() const noexcept;

    void AddEdge(vertex_t from, vertex_t to);

    void DeleteEdge(vertex_t from, vertex_t to);

    bool EdgeExist(vertex_t from, vertex_t to) const noexcept;

    bool VertexExist(vertex_t vertex) const noexcept;

    std::vector<vertex_t> GetNeighbours(vertex_t vertex) const noexcept;

    std::vector<std::vector<vertex_t>> GetTransposed() const noexcept;

    void Transpose() noexcept;

    void PrintGraph() const noexcept;
};
std::ostream& operator<<(std::ostream& os, const AdjacecyListsGraph& graph);

class AdjacencyMatrixGraph : public Graph {
    std::vector<std::vector<vertex_t>> graph_;
    vertex_t edge_cnt_ = 0;

public:
    AdjacencyMatrixGraph(const std::vector<std::vector<vertex_t>>& graph);

    AdjacencyMatrixGraph(vertex_t vertex_cnt);

    vertex_t GetCntVertex() const noexcept;

    vertex_t GetCntEdge() const noexcept;

    void AddEdge(vertex_t from, vertex_t to);

    void DeleteEdge(vertex_t from, vertex_t to);

    bool EdgeExist(vertex_t from, vertex_t to) const noexcept;

    bool VertexExist(vertex_t vertex) const noexcept;

    std::vector<vertex_t> GetNeighbours(vertex_t vertex) const noexcept;

    std::vector<std::vector<vertex_t>> GetTransposed() const noexcept;

    void Transpose() noexcept;

    void PrintGraph() const noexcept;
};
std::ostream& operator<<(std::ostream& os, const AdjacencyMatrixGraph& graph);
#endif //GRAPH_GRAPH_H
