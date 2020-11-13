#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <queue>
#include <iomanip>
#include <cmath>

using Coordinates = std::pair<int, int>;

struct Edge {
    size_t weight;
    size_t to;
    Edge(size_t weight, size_t to) : weight(weight), to(to) {
    }
};

using Graph = std::vector<std::vector<Edge>>;

struct Comp {
    bool operator()(const Edge& a, const Edge& b) {
        return a.weight > b.weight;
    }
};

size_t GetDistance(const std::pair<int, int>& from, const std::pair<int, int>& to) {
    return ((from.first - to.first)*(from.first - to.first) + (from.second - to.second)*(from.second - to.second));
}

double Prim(size_t n_cities, std::vector<Coordinates>& cities_coordinates) {
    std::vector<bool> used(n_cities, false);
    size_t current = 0;
    used[current] = true;
    double weight_mst = 0;
    size_t n_edge_in_mst = 0;
    std::priority_queue<Edge, std::vector<Edge>, Comp> heap;
    for (int i = 1; i < n_cities; ++i) {
        heap.push(Edge(GetDistance(cities_coordinates[0], cities_coordinates[i]), i));
    }

    while (n_edge_in_mst < n_cities - 1) {
        auto min_weight_edge = heap.top();
        heap.pop();
        if (used[min_weight_edge.to]) {
            continue;
        }
        used[min_weight_edge.to] = true;
        weight_mst += sqrt(min_weight_edge.weight);
        for (int i = 0; i < n_cities; ++i) {
            if (!used[i]) {
                heap.push(Edge(GetDistance(cities_coordinates[min_weight_edge.to], cities_coordinates[i]), i));
            }
        }
        ++n_edge_in_mst;
    }
    return weight_mst;
}


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    size_t n_cities;
    std::cin >> n_cities;
    std::vector<Coordinates> cities_coordinates;

    Graph graph(n_cities);


    for (int i = 0; i < n_cities; ++i) {
        int x, y;
        std::cin >> x >> y;
        cities_coordinates.emplace_back(x, y);
    }



    std::cout << std::setprecision(8) << Prim(n_cities, cities_coordinates);

    return 0;
}
