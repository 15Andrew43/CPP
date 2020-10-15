#include <iostream>
#include <vector>
#include <exception>
#include <algorithm>
#include <stdexcept>

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
    AdjacecyListsGraph(const std::vector<std::vector<vertex_t>>& graph) : graph_(graph) {
        for (auto neighbours: graph_) {
            edge_cnt_ += neighbours.size();
        }
//        edge_cnt_ /= 2;
    }
    AdjacecyListsGraph(vertex_t vertex_cnt) : graph_(vertex_cnt, std::vector<vertex_t>()) {}

    vertex_t GetCntVertex() const noexcept {
        return graph_.size();
    }

    void AddEdge(vertex_t from, vertex_t to) {
        if (std::min(from, to) < 0) {
            throw std::invalid_argument("numbers of the vertexes must be >= 0, when you try to add a new edge");
        }
        vertex_t new_cnt_vertex = std::max(from, to);
        ++new_cnt_vertex;
        vertex_t  old_cnt_vertex = GetCntVertex();
        while (old_cnt_vertex < new_cnt_vertex) {
            graph_.push_back(std::vector<vertex_t >());
            ++old_cnt_vertex;
        }
        graph_[from].push_back(to);
    }
    void DeleteEdge(vertex_t from, vertex_t to) {
        if (! EdgeExist(from, to)) {
            return;
        }
        auto iter_to = std::find(graph_[from].begin(), graph_[from].end(), to);
        if (iter_to != graph_[from].end()) {
            graph_[from].erase(iter_to);
        }
    }

    bool EdgeExist(vertex_t from, vertex_t to) const noexcept {
        if (from > GetCntVertex() - 1 || to > GetCntVertex() - 1 || from < 0 || to < 0) {
            return false;
        }
        auto it = std::find(graph_[from].begin(), graph_[from].end(), to);
        if (it != graph_[from].end()) {
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
        return std::vector<vertex_t>();
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

class AdjacencyMatrixGraph : public Graph {
    std::vector<std::vector<vertex_t>> graph_;

public:
    AdjacencyMatrixGraph(const std::vector<std::vector<vertex_t>>& graph) : graph_(graph) {}
    AdjacencyMatrixGraph(vertex_t vertex_cnt) : graph_(vertex_cnt, std::vector<vertex_t>(vertex_cnt, 0)) {}

    vertex_t GetCntVertex() const noexcept {
        return graph_.size();
    }
    vertex_t GetCntEdge() const noexcept {
        vertex_t edge_cnt = 0;
        for (auto line: graph_) {
            for (auto edge: line) {
                if (edge != 0)
                    ++edge_cnt;
            }
        }
        return edge_cnt;
    }
    void AddEdge(vertex_t from, vertex_t to) {
        if (std::min(from, to) < 0) {
            throw std::invalid_argument("numbers of the vertexes must be >= 0, when you try to add a new edge");
        }
        vertex_t new_cnt_vertex = std::max(from, to);
        ++new_cnt_vertex;
        vertex_t  old_cnt_vertex = GetCntVertex();
        vertex_t delta = new_cnt_vertex - old_cnt_vertex;
        if (delta < 0) {
            graph_[from][to] = 1;
            return;
        }
        for (vertex_t i = 0; i < delta; ++i) {
            graph_.push_back(std::vector<vertex_t>());
        }
        for (vertex_t i = 0; i < old_cnt_vertex; ++i) {
            for (vertex_t j = old_cnt_vertex; j < new_cnt_vertex; ++j) {
                if (i == from && j == to)
                    graph_[i].push_back(1);
                else
                    graph_[i].push_back(0);
            }
        }
        for (vertex_t i = old_cnt_vertex; i < new_cnt_vertex; ++i) {
            graph_[i] = std::vector<vertex_t>(new_cnt_vertex, 0);
        }
        for (vertex_t i = old_cnt_vertex; i < new_cnt_vertex; ++i) {
            for (vertex_t j = 0; j < new_cnt_vertex; ++j) {
                if (i == from && j == to)
                    graph_[i][j] = 1;
                else
                    graph_[i][j] = 0;
            }
        }
    }
    void DeleteEdge(vertex_t from, vertex_t to) {
        if (! EdgeExist(from, to)) {
            return;
        }
        graph_[from][to] = 0;
    }


    bool EdgeExist(vertex_t from, vertex_t to) const noexcept {
        if (from > GetCntVertex() - 1 || to > GetCntVertex() - 1 || from < 0 || to < 0) {
            return false;
        }
        if (graph_[from][to] != 0) {
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

    std::vector<std::vector<vertex_t>> GetTransposed() const noexcept {
        AdjacencyMatrixGraph transposed_graph(graph_);
        transposed_graph.Transpose();
        return transposed_graph.graph_;
    }
    void Transpose() noexcept {
        for (vertex_t i = 0; i < GetCntVertex(); ++i) {
            for (vertex_t j = 0; j < i; ++j) {
                std::swap(graph_[i][j], graph_[j][i]);
            }
        }
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
std::ostream& operator<<(std::ostream& os, const AdjacencyMatrixGraph& graph) {
    graph.PrintGraph();
    return os;
}

int main() {
    std::vector<std::vector<vertex_t>> g;
    for (vertex_t i = 0; i < 5; ++i) {
        std::vector<vertex_t> line;
        for (vertex_t j = 0; j < 3; ++j) {
            line.push_back( rand() % 5);
        }
        g.push_back(line);
    }

    AdjacecyListsGraph graph(g);

//    graph.PrintGraph();
    std::cout << graph;

    std::cout << "vertexes = " << graph.GetCntVertex() << '\n'
              << "edges = " << graph.GetCntEdge() << '\n';

    std::cout << "adding edge 1 5\n";
    graph.AddEdge(1, 5);
//    graph.PrintGraph();
    std::cout << graph;

    std::cout << "deleting edge 1 2\n";
    graph.DeleteEdge(1, 2);
//    graph.PrintGraph();
    std::cout << graph;

    std::cout << "printing neigbouts 2\n";
    for (auto x: graph.GetNeighbours(2)) {
        std::cout << x << ' ';
    }
    std::cout << '\n';

//    graph.PrintGraph();
    std::cout << graph;
    std::cout << "transposing\n";
    graph.Transpose();
//    graph.PrintGraph();
    std::cout << graph;

    std::cout << "===================================================================================\n";
    std::cout << "===================================================================================\n";
    std::cout << "===================================================================================\n";

    std::vector<std::vector<vertex_t>> gg;
    for (vertex_t i = 0; i < 5; ++i) {
        std::vector<vertex_t> line;
        for (vertex_t j = 0; j < 5; ++j) {
            line.push_back( rand() % 2);
        }
        gg.push_back(line);
    }

    AdjacencyMatrixGraph graph1(gg);

//    graph1.PrintGraph();
    std::cout << graph1;

    std::cout << "vertexes = " << graph1.GetCntVertex() << '\n'
              << "edges = " << graph1.GetCntEdge() << '\n';

    std::cout << "adding edge 1 5\n";
    graph1.AddEdge(1, 5);
//    graph1.PrintGraph();
    std::cout << graph1;

    std::cout << "deleting edge 1 2\n";
    graph1.DeleteEdge(1, 2);
//    graph1.PrintGraph();
    std::cout << graph1;

    std::cout << "printing neigbouts 2\n";
    for (auto x: graph1.GetNeighbours(2)) {
        std::cout << x << ' ';
    }
    std::cout << '\n';

//    graph1.PrintGraph();
    std::cout << graph1;
    std::cout << "transposing\n";
    graph1.Transpose();
//    graph1.PrintGraph();
    std::cout << graph1;

    std::cout << "Hello, World!" << std::endl;
    return 0;
}