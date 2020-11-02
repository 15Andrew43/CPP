#include <iostream>
#include <vector>
#include <stack>
#include <cmath>
#include <iomanip>
#include <algorithm>

using Graph = std::vector<std::vector<double>>;
using Coordinates = std::pair<int, int>;

class DSU {
    using elem_t = int;
    mutable std::vector<elem_t> predecessors_;
    std::vector<size_t> ranks_;
public:
    DSU(size_t n_sets) : predecessors_(n_sets), ranks_(n_sets, 0) {
        for (elem_t i = 0; i < n_sets; ++i) {
            predecessors_[i] = i;
        }
    }
    elem_t MakeSet() {
        predecessors_.push_back(predecessors_.size());
        ranks_.push_back(0);
        return predecessors_.size() - 1;
    }
    elem_t FindSet(elem_t elem) const {
        if (predecessors_[elem] == elem) {
            return elem;
        }
        predecessors_[elem] = FindSet(predecessors_[elem]);
        return predecessors_[elem];
    }
    void Union(elem_t elem0, elem_t elem1) {
        elem0 = FindSet(elem0);
        elem1 = FindSet(elem1);
        if (ranks_[elem0] < ranks_[elem1]) {
            predecessors_[elem0] = elem1;
        } else if (ranks_[elem0] > ranks_[elem1]) {
            predecessors_[elem1] = elem0;
        } else {
            ++ranks_[elem0];
            predecessors_[elem1] = elem0;
        }
    }
};

double GetDistance(const std::pair<int, int>& from, const std::pair<int, int>& to) {
    return sqrt((from.first - to.first)*(from.first - to.first) + (from.second - to.second)*(from.second - to.second));
}

double Kruskal(size_t n_cities, std::vector<std::pair<double, std::pair<int, int>>>& edges) {
    std::sort(edges.begin(), edges.end());
//    for (auto x: edges) {
//        std::cout << x.first <<  ' ';
//    }
//    std::cout << '\n';
    DSU dsu(n_cities);

    double length = 0;

    for (auto edge: edges) {
        if (dsu.FindSet(edge.second.first) != dsu.FindSet(edge.second.second)) {
//            std::cout << edge.second.first << ' ' << edge.second.second << '\n';
            length += edge.first;
            dsu.Union(edge.second.first, edge.second.second);
        }
    }
    return length;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    size_t n_cities;
    std::cin >> n_cities;
    std::vector<Coordinates> cities_coordinates;



    for (int i = 0; i < n_cities; ++i) {
        int x, y;
        std::cin >> x >> y;
        cities_coordinates.emplace_back(x, y);
    }

    std::vector<std::pair<double, std::pair<int, int>>> edges;

    for (int i = 0; i < cities_coordinates.size()-1; ++i) {
        for (int j = i+1; j < cities_coordinates.size(); ++j) {
            double distance = GetDistance(cities_coordinates[i], cities_coordinates[j]);
            edges.emplace_back(distance, std::make_pair(i, j));
        }
    }

    std::cout << std::setprecision(17) <<  Kruskal(n_cities, edges);

    return 0;
}