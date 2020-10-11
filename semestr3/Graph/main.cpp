#include <iostream>
#include <vector>
#include <list>
#include <exception>
#include <algorithm>

class AdjacecyListsGraph {
    std::vector<std::list<size_t>> graph_;
public:
    AdjacecyListsGraph(const std::vector<std::list<size_t>>& g) : graph_(g) {}

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
            graph_.push_back(std::list<size_t >());
            ++old_cnt_vertex;
        }
        graph_[from].push_back(to);
//        graph_[to].push_back(from);
    }
    void deleteEdge(int from, int to) {
        if (! EdgeExist(from, to)) {
            return;
        }
        auto iter_to = std::find(graph_[from].begin(), graph_[from].end(), to);
        if (iter_to != graph_[from].end()) {
            graph_[from].erase(iter_to);
        }
//        auto iter_from = std::find(graph_[to].begin(), graph_[to].end(), from);
//        graph_[to].erase(iter_from);
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
    std::list<size_t> getNeighbours(int vertex) const noexcept {
        if (VertexExist(vertex)) {
            return graph_[vertex];
        }
        return std::list<size_t>();
    }
    std::vector<std::list<size_t>> getTransposed() const noexcept {
        std::vector<std::list<size_t>> transposed_graph(graph_.size(), std::list<size_t>());
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

class AdjacencyMatrixGraph {
    std::vector<std::vector<size_t>> graph_;
public:
    AdjacencyMatrixGraph(const std::vector<std::vector<size_t>>& g) : graph_(g) {}

    size_t getCntVertex() const noexcept {
        return graph_.size();
    }
    size_t getCntEdge() const noexcept {
        size_t edge_cnt = 0;
        for (auto line: graph_) {
            for (auto edge: line) {
                if (edge != 0)
                    ++edge_cnt;
            }
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
        int delta = new_cnt_vertex - old_cnt_vertex;
        if (delta < 0) {
            graph_[from][to] = 1;
            return;
        }
        for (size_t i = 0; i < delta; ++i) {
            graph_.push_back(std::vector<size_t>());
        }
        for (size_t i = 0; i < old_cnt_vertex; ++i) {
            for (size_t j = old_cnt_vertex; new_cnt_vertex; ++j) {
                if (i != from || j != to)
                    graph_[i].push_back(0);
                else
                    graph_[i].push_back(1);
            }
        }
        for (size_t i = old_cnt_vertex; i < new_cnt_vertex; ++i) {
            graph_[i] = std::vector<size_t>(new_cnt_vertex, 0);
        }
    }
    void deleteEdge(int from, int to) {
        if (! EdgeExist(from, to)) {
            return;
        }
        graph_[from][to] = 0;
    }

    bool EdgeExist(int from, int to) const noexcept {
        if (from > getCntVertex() - 1 || to > getCntVertex() - 1 || from < 0 || to < 0) {
            return false;
        }
        if (graph_[from][to] != 0) {
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
        std::vector<size_t> neighbours;
        if (VertexExist(vertex)) {
            for (size_t j = 0; j < getCntVertex(); ++j) {
                if (graph_[vertex][j] != 0) {
                    neighbours.push_back(j);
                }
            }
        }
        return neighbours;
    }

    std::vector<std::vector<size_t>> getTransposed() noexcept {
        std::vector<std::vector<size_t>> transposed_graph(graph_.size(), std::vector<size_t>());
        for (size_t i = 0; i < getCntVertex(); ++i) {
            for (size_t j = 0; j < getCntVertex(); ++j) {
                std::swap(graph_[i][j], graph_[j][i]);
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
//
//class Graph: public AdjacecyListsGraph, AdjacencyMatrixGraph {
//
//};

int main() {
//    std::vector<std::list<size_t>> g;
//    for (int i = 0; i < 5; ++i) {
//        std::list<size_t> list;
//        for (int j = 0; j < 3; ++j) {
//            list.push_back( rand() % 5);
//        }
//        g.push_back(list);
//    }
//
//    AdjacecyListsGraph graph(g);
//
//    graph.printGraph();
//
//    std::cout << "vertexes = " << graph.getCntVertex() << '\n'
//              << "edges = " << graph.getCntEdge() << '\n';
//
//    std::cout << "adding edge 1 5\n";
//    graph.addEdge(1, 5);
//    graph.printGraph();
//
//    std::cout << "deleting edge 1 2\n";
//    graph.deleteEdge(1, 2);
//    graph.printGraph();
//
//    std::cout << "printing neigbouts 2\n";
//    for (auto x: graph.getNeighbours(2)) {
//        std::cout << x << ' ';
//    }
//    std::cout << '\n';
//
//    graph.printGraph();
//    std::cout << "transposing\n";
//    graph.Transpose();
//    graph.printGraph();

//    std::cout << "===================================================================================\n";
//
    std::vector<std::vector<size_t>> g;
    for (int i = 0; i < 5; ++i) {
        std::vector<size_t> list;
        for (int j = 0; j < 5; ++j) {
            list.push_back( rand() % 2);
        }
        g.push_back(list);
    }

    AdjacencyMatrixGraph graph(g);

    graph.printGraph();

    std::cout << "vertexes = " << graph.getCntVertex() << '\n'
              << "edges = " << graph.getCntEdge() << '\n';

    std::cout << "adding edge 1 5\n";
    graph.addEdge(1, 5);
    graph.printGraph();

    std::cout << "deleting edge 1 2\n";
    graph.deleteEdge(1, 2);
    graph.printGraph();

    std::cout << "printing neigbouts 2\n";
    for (auto x: graph.getNeighbours(2)) {
        std::cout << x << ' ';
    }
    std::cout << '\n';

    graph.printGraph();
    std::cout << "transposing\n";
    graph.Transpose();
    graph.printGraph();

    std::cout << "Hello, World!" << std::endl;
    return 0;
}