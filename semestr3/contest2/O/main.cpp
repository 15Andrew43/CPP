#include <iostream>
#include <vector>
#include <exception>
#include <algorithm>
#include <stdexcept>

#include "graph.h"

enum Status {
    kUndiscovered = 0,
    kDiscovered = 1,
    kProcessed = 2
};

void PassageReachableVertices(const Graph& graph, int vertex, std::vector<vertex_t>& sorted_array, std::vector<Status>& statuses) {
    statuses[vertex] = kDiscovered;
    for (auto neighbour: graph.GetNeighbours(vertex)) {
        if (statuses[neighbour] == kUndiscovered) {
            PassageReachableVertices(graph, neighbour, sorted_array, statuses);
        }
    }
    statuses[vertex] = kProcessed;
    sorted_array.push_back(vertex);
}

std::vector<vertex_t> TopSortWithoutCheckCycles(const Graph& graph) {
    std::vector<Status> statuses(graph.GetCntVertex(), kUndiscovered);
    std::vector<vertex_t> sorted_array;
    for (int vertex = 0; vertex < graph.GetCntVertex(); ++vertex) {
        if (statuses[vertex] == kUndiscovered) {
            PassageReachableVertices(graph, vertex, sorted_array, statuses);
        }
    }
    return {sorted_array.rbegin(), sorted_array.rend()};
}

std::vector<std::vector<vertex_t>> GetAllocationComponents (const Graph& graph, const std::vector<vertex_t>& vertexes_group_in_scc) {
    std::vector<std::vector<vertex_t>> strong_connected_components;
    std::vector<Status> statuses(graph.GetCntVertex(), kUndiscovered);
    for (auto vertex: vertexes_group_in_scc) {
        std::vector<vertex_t> sorted_array;
        if (statuses[vertex] == kUndiscovered) {
            PassageReachableVertices(graph, vertex, sorted_array, statuses);
            strong_connected_components.push_back(sorted_array);
        }
    }
    return strong_connected_components;
}

std::vector<std::vector<vertex_t>> FindStronglyConnectedComponents(const Graph& graph) {
    auto vertexes_group_in_scc  = TopSortWithoutCheckCycles(graph); // топ сорт без прверик циклов
    auto new_graph_ptr = graph.Copy();
    new_graph_ptr->Transpose();
    return GetAllocationComponents(*new_graph_ptr, vertexes_group_in_scc);
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


    std::vector<vertex_t> answer(graph.GetCntVertex());
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