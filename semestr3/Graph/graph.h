#ifndef GRAPH_GRAPH_H
#define GRAPH_GRAPH_H

#include <utility>
#include <vector>
#include <iostream>

using vertex_t = int;
using edge_t = int;

class Graph {
public:
    virtual vertex_t GetCntVertex() const noexcept = 0;
    virtual edge_t GetCntEdge() const noexcept = 0;
    virtual void AddEdge(vertex_t from, vertex_t to) = 0;
    virtual void DeleteEdge(vertex_t from, vertex_t to) = 0;
    virtual bool EdgeExist(vertex_t from, vertex_t to) const noexcept = 0;
    virtual bool VertexExist(vertex_t vertex) const noexcept = 0;
    virtual std::vector<vertex_t> GetNeighbours(vertex_t vertex) const = 0;
    virtual void Transpose() = 0;
//    virtual Graph* Copy() const  = 0;
    virtual std::shared_ptr<Graph> Copy() const  = 0;
    virtual ~Graph() {}; // "= 0", doesn't works(
};

std::ostream& operator<<(std::ostream& os, const Graph& graph);

class AdjacencyListsGraph : public Graph {
    std::vector<std::vector<vertex_t>> graph_;
    edge_t edge_cnt_ = 0;

public:
    AdjacencyListsGraph(const std::vector<std::vector<vertex_t>>& graph);
    AdjacencyListsGraph(vertex_t vertex_cnt);

    vertex_t GetCntVertex() const noexcept override;
    edge_t GetCntEdge() const noexcept override;
    void AddEdge(vertex_t from, vertex_t to) override;
    void DeleteEdge(vertex_t from, vertex_t to) override;
    bool EdgeExist(vertex_t from, vertex_t to) const noexcept override;
    bool VertexExist(vertex_t vertex) const noexcept override;
    std::vector<vertex_t> GetNeighbours(vertex_t vertex) const override;
    void Transpose() override;
//    Graph* Copy() const override;
    std::shared_ptr<Graph> Copy() const override; // Здесь можно поставить AdjacencyListsGraph* (ковариантный возвращаемый тип) todo!
    ~AdjacencyListsGraph() override = default;
};

class AdjacencyMatrixGraph : public Graph {
    std::vector<std::vector<vertex_t>> graph_;
    edge_t edge_cnt_ = 0;

public:
    AdjacencyMatrixGraph(const std::vector<std::vector<vertex_t>>& graph);
    AdjacencyMatrixGraph(vertex_t vertex_cnt);

    vertex_t GetCntVertex() const noexcept override;
    edge_t GetCntEdge() const noexcept override;
    void AddEdge(vertex_t from, vertex_t to) override;
    void DeleteEdge(vertex_t from, vertex_t to) override;
    bool EdgeExist(vertex_t from, vertex_t to) const noexcept override;
    bool VertexExist(vertex_t vertex) const noexcept override;
    std::vector<vertex_t> GetNeighbours(vertex_t vertex) const override;
    void Transpose() override;
//    Graph* Copy()const override;
    std::shared_ptr<Graph> Copy() const override; // Здесь можно поставить AdjacencyMatrixGraph* (ковариантный возвращаемый тип) todo!
    ~AdjacencyMatrixGraph() override = default;
};
#endif //GRAPH_GRAPH_H
