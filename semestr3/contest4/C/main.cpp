#include <iostream>
#include <vector>

struct Edge {
	size_t from;
	long long int time_from;
	size_t to;
	long long int time_to;
	size_t price;
};


long long int FordBellman(const std::vector<Edge>& edges, size_t n_stations, size_t start, size_t finish, size_t n_teleports) {
	long long int infinity = 1000000000;
	std::vector<long long int> time(n_stations, infinity);
	time[start] = 0;
	for (size_t i = 0; i < n_teleports; ++i) {
		for (auto& edge: edges) {
			size_t from, to;
			long long int time_from, time_to;
			from = edge.from;
			to = edge.to;
			time_from = edge.time_from;
			time_to = edge.time_to;
			if (time[to] > time_to && time[from] <= time_from) {
				time[to] = time_to;
			}
		}
	}
	return time[finish];
} 

int main() {
	size_t n_stations, start, finish, n_teleports;
	std::cin >> n_stations >> start >> finish >> n_teleports;

	std::vector<Edge> edges;

	for (size_t i = 0; i < n_teleports; ++i) {
		size_t from, to;
		long long int time_from, time_to;
		std::cin >> from >> time_from 
				 >> to >> time_to;
		--from, --to;
		edges.push_back({from, time_from, to, time_to});
	}

	std::cout << FordBellman(edges, n_stations, start-1, finish-1, n_teleports);

	return 0;
}