#include <iostream>
#include <vector>
#include <queue>
#include <utility>

struct AdjacentVertex {
    size_t to;
    size_t weight;
    size_t n_elevant;
};

size_t infinity = 2009000999;
using Graph = std::vector<std::vector<AdjacentVertex>>;

struct Info {
    size_t n_floor, money_to_up, money_to_down, money_to_in, money_to_out, cnt_elevators, max;
};

bool Relax(size_t vertex, const AdjacentVertex& adjacent_vertex, std::vector<size_t>& money_to_reach) {
    if (money_to_reach[adjacent_vertex.to] > money_to_reach[vertex] + adjacent_vertex.weight) {
        money_to_reach[adjacent_vertex.to] = money_to_reach[vertex] + adjacent_vertex.weight;
        return true;
    }
    return false;
}

size_t Dijkstra(const Graph& graph, const Info& info, const size_t start, const size_t finish) {
    std::vector<bool> used(info.max+1, false);
    std::vector<size_t> money_to_reach(info.max+1, infinity);
    money_to_reach[start] = 0;
    std::priority_queue<std::pair<size_t, size_t>, std::vector<std::pair<size_t, size_t>>, std::greater<std::pair<size_t, size_t>>> heap;
    heap.push(std::make_pair(money_to_reach[start], start));
    while (!heap.empty()) {
        auto vertex = heap.top().second;
        heap.pop();
        if (used[vertex]) {
            continue;
        }
        used[vertex] = true;

        if (vertex < info.max - 1 && Relax(vertex, {vertex + 1, info.money_to_up}, money_to_reach)) {
            heap.push(std::make_pair(money_to_reach[vertex + 1], vertex + 1));
        }
        if (vertex > 0 && Relax(vertex, {vertex - 1, info.money_to_down}, money_to_reach)) {
            heap.push(std::make_pair(money_to_reach[vertex - 1], vertex - 1));
        }
        for (const auto& adjacent_vertex: graph[vertex]) {
            if (Relax(vertex, adjacent_vertex, money_to_reach)) {
                heap.push(std::make_pair(money_to_reach[adjacent_vertex.to], adjacent_vertex.to));
            }
            if (adjacent_vertex.to < vertex) {
                for (const auto& adjacent_under_vertex: graph[adjacent_vertex.to]) {
                    if (adjacent_under_vertex.n_elevant == adjacent_vertex.n_elevant) {
                        if (Relax(vertex, adjacent_under_vertex, money_to_reach)) {
                            heap.push(std::make_pair(money_to_reach[adjacent_under_vertex.to], adjacent_under_vertex.to));
                        }
                    }
                }
            }
        }
    }
    return money_to_reach[finish];
}

int main() {
    size_t n_floor, money_to_up, money_to_down, money_to_in, money_to_out, cnt_elevators;
    std::cin >> n_floor >>  money_to_up >> money_to_down >> money_to_in >> money_to_out >> cnt_elevators;


    Graph graph(n_floor);

    size_t max = n_floor;

    for (size_t i = 0; i < cnt_elevators; ++i) {
        size_t cnt_stops;
        std::cin >> cnt_stops;
        std::vector<size_t> stops(cnt_stops);
        for (size_t j = 0; j < cnt_stops; ++j) {
            std::cin >> stops[j];
            if (stops[j] > max) {
                max = stops[j];
                --max;
                while (graph.size() <= max)
                    graph.push_back(std::vector<AdjacentVertex>());
            }
            --stops[j];
        }
        for (size_t j = 1; j < cnt_stops; ++j) {
            graph[stops[0]].push_back({stops[j], money_to_in + money_to_out, i});
            graph[stops[j]].push_back({stops[0], money_to_in + money_to_out, i});
        }
    }

    Info info = {n_floor, money_to_up, money_to_down, money_to_in, money_to_out, cnt_elevators, max};

    std::cout << Dijkstra(graph, info, 0, n_floor-1);

    return 0;
}