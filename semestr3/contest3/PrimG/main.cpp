#include <iostream>
#include <vector>
#include <stack>
#include <cmath>
#include <iomanip>
#include <algorithm>

using Coordinates = std::pair<int, int>;

struct Edge {
    double weight;
    size_t to;
    Edge(double weight, size_t to) : weight(weight), to(to) {
    }
};

using Graph = std::vector<std::vector<Edge>>;



double GetDistance(const std::pair<int, int>& from, const std::pair<int, int>& to) {
    return sqrt((from.first - to.first)*(from.first - to.first) + (from.second - to.second)*(from.second - to.second));
}

Edge FindMin(const std::vector<int> mst, const std::vector<Coordinates>& cities_coordinates, std::vector<bool>& used) {
    double min = 1000000;
    size_t ind;
    for (auto mst_vertex: mst) {
        for (int i = 0; i < cities_coordinates.size(); ++i) {
            if (used[i]) {
                continue;
            }
            auto distance = GetDistance(cities_coordinates[mst_vertex], cities_coordinates[i]);
            if (min > distance) {
                min = distance;
                ind = i;
            }
        }
    }
    return {min, ind};
}

double Prim(size_t n_cities, std::vector<Coordinates>& cities_coordinates) {
    std::vector<bool> used(n_cities, false);
    size_t current = 0;
    used[current] = true;
    double weight_mst = 0;
    size_t n_edge_in_mst = 0;
    std::vector<int> mst;
    mst.push_back(current);

    while (n_edge_in_mst < n_cities - 1) {
        Edge min_weight_edge = FindMin(mst, cities_coordinates, used);
        mst.push_back(min_weight_edge.to);
        if (used[min_weight_edge.to]) {
            continue;
        }
        used[min_weight_edge.to] = true;
        weight_mst += min_weight_edge.weight;

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



    std::cout << std::setprecision(17) << Prim(n_cities, cities_coordinates);

    return 0;
}