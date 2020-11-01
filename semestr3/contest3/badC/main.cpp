#include <iostream>

#include <utility>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>
#include <memory>

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
    virtual bool InConnectedComponent(vertex_t vertex0, vertex_t vertex1) const = 0;
//    virtual Graph* Copy() const  = 0;
    virtual std::shared_ptr<Graph> Copy() const  = 0;
    virtual ~Graph() {}; // "= 0", doesn't works(
};

std::ostream& operator<<(std::ostream& os, const Graph& graph);

class AdjacencyListsGraph : public Graph {
    std::vector<std::vector<vertex_t>> graph_;
    edge_t edge_cnt_ = 0;
    int infinity = 1000000;
    bool BFS(vertex_t from, vertex_t to) const;

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
    bool InConnectedComponent(vertex_t vertex0, vertex_t vertex1) const override;
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
    bool InConnectedComponent(vertex_t vertex0, vertex_t vertex1) const override;
    //    Graph* Copy()const override;
    std::shared_ptr<Graph> Copy() const override; // Здесь можно поставить AdjacencyMatrixGraph* (ковариантный возвращаемый тип) todo!
    ~AdjacencyMatrixGraph() override = default;
};

//===============================================================================================

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

bool AdjacencyListsGraph::BFS(vertex_t from, vertex_t to) const {
    if (from == to) {
        return true;
    }
    std::queue<vertex_t > queue;
    std::vector<int> distance(GetCntVertex(), infinity);
    distance[from] = 0;
    queue.push(from);

    while (!queue.empty()) {
        int v = queue.front();
        queue.pop();
        for (auto neighbour: GetNeighbours(v)) {
            if (distance[neighbour] == infinity) {
                if (neighbour == to) {
                    return true;
                }
                queue.push(neighbour);
                distance[neighbour] = distance[v] + 1;
            }
        }
    }
    return false;
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



bool AdjacencyListsGraph::InConnectedComponent(vertex_t vertex0, vertex_t vertex1) const {
    return BFS(vertex0, vertex1);
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

bool AdjacencyMatrixGraph::InConnectedComponent(vertex_t vertex0, vertex_t vertex1) const {
    return false;
}

std::shared_ptr<Graph> AdjacencyMatrixGraph::Copy() const {
    return std::make_shared<AdjacencyMatrixGraph>(graph_);
}

//AdjacencyMatrixGraph::~AdjacencyMatrixGraph() {
//    std::cout << "Ppe\n";
//}


int main() {
    vertex_t n_vertex;
    int n_edge, n_operation;
    std::cin >> n_vertex >> n_edge >> n_operation;
    std::vector<std::vector<vertex_t>> vec_graph(n_vertex);
    for (int i = 0; i < n_edge; ++i) {
        int from, to;
        std::cin >> from >> to;
        --from, --to;
        vec_graph[from].push_back(to);
        vec_graph[to].push_back(from);
    }

    AdjacencyListsGraph graph(vec_graph);

//    std::cout << graph;

    for (int i = 0; i < n_operation; ++i) {
        std::string operation;
        vertex_t vertex0, vertex1;
        std::cin >> operation >> vertex0 >> vertex1;
        --vertex0, --vertex1;
        if (operation == "cut") {
            graph.DeleteEdge(vertex0, vertex1);
            graph.DeleteEdge(vertex1, vertex0);
//            std::cout << graph << '\n';
        } else if (operation == "ask") {
            if (graph.InConnectedComponent(vertex0, vertex1)) {
                std::cout << "YES\n";
            } else {
                std::cout << "NO\n";
            }
        }
    }

    return 0;
}