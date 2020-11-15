#include <iostream>
#include <vector>

struct Edge {
	size_t from;
	size_t to;
	size_t price;
	Edge() = default;
	Edge(size_t from, size_t to, size_t price) : from(from), to(to), price(price) {
	}
};


long long FordBellman(const std::vector<Edge>& edges, size_t n_cities, size_t start, size_t finish, size_t n_days) {
	size_t infinity = 1000000000;
	std::vector<size_t> distance(n_cities, infinity);
	distance[start] = 0;
	std::vector<size_t> new_distance = distance;
	for (size_t i = 0; i < n_days; ++i) {
		for (auto& edge: edges) {
			size_t from, to, price;
			from = edge.from;
			to = edge.to;
			price = edge.price;
			if (new_distance[to] > distance[from] + price) {
				new_distance[to] = distance[from] + price;
			}
		}
		distance = new_distance;
	}
	if (distance[finish] == infinity) {
		return -1;
	}
	return distance[finish];
} 

int main() {
	size_t n_cities, n_flights, n_days, start, finish;
	std::cin >> n_cities >> n_flights >> n_days >> start >> finish;

	std::vector<Edge> edges;

	for (size_t i = 0; i < n_flights; ++i) {
		size_t from, to;
		size_t price;
		std::cin >> from >> to >> price;
		--from, --to;
		edges.emplace_back(from, to, price);
	}

	std::cout << FordBellman(edges, n_cities, start-1, finish-1, n_days);

	return 0;
}