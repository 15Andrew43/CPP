#include <iostream>
#include <vector>
#include <exception>

#include "graph.h"


int main() {
    AdjacencyListsGraph ggg(0);
    std::cout << ggg.EdgeExist(0, 1) << '\n';
    std::cout << ggg.VertexExist(0) << '\n';

    AdjacencyMatrixGraph gggg(0);
    std::cout << gggg.EdgeExist(0, 1) << '\n';
    std::cout << gggg.VertexExist(0) << '\n';

    std::vector<std::vector<vertex_t>> g;
    for (vertex_t i = 0; i < 6; ++i) {
        std::vector<vertex_t> line;
        for (vertex_t j = 0; j < 3; ++j) {
            line.push_back( rand() % 5);
        }
        g.push_back(line);
    }

    AdjacencyListsGraph graph(g);

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
    graph1.AddEdge(1, 3);
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