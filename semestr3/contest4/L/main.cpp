#include <iostream>
#include <vector>
#include <algorithm>


using Graph = std::vector<std::vector<int>>;


void FordBellman(const Graph& graph, std::vector<int>& distance, std::vector<size_t>& pred) {
	for (size_t k = 0; k < graph.size() - 1; ++k) {
		for (size_t i = 0; i < graph.size(); ++i) {
			for (size_t j = 0; j < graph.size(); ++j) { 
				if (graph[i][j] != 100000 && distance[j] > distance[i] + graph[i][j]) {
					distance[j] = distance[i] + graph[i][j];
					pred[j] = i;
				}
			}
		}
	}
}

std::vector<size_t> GetNegativeCycle(const Graph& graph) {
	int infinity = 100000;
	std::vector<int> distance(graph.size(), infinity);
	distance[0] = 0;
	std::vector<size_t> pred(graph.size(), -1);
	FordBellman(graph, distance, pred);
	auto new_distance = distance;
	FordBellman(graph, distance, pred);

	std::vector<size_t> cycle;

	for (size_t i = 0; i < distance.size(); ++i) {
		if (distance[i] == new_distance[i]) {
			continue;
		}
		size_t vertex = i;
		auto it = cycle.begin();
		cycle.push_back(vertex);
		vertex = pred[vertex];	
		while ((it=std::find(cycle.begin(), cycle.end(), vertex)) == cycle.end()) {
			// std::cout << "pep\n";
			cycle.push_back(vertex);
			vertex = pred[vertex];
		}
		cycle.push_back(vertex);
		cycle.erase(cycle.begin(), it);
		break;
	}
	return cycle;
}

int main() {
	size_t n_vertex;
	std::cin >> n_vertex;

	Graph graph(n_vertex, std::vector<int>(n_vertex));

	for (size_t i = 0; i < n_vertex; ++i) {
		for (size_t j = 0; j < n_vertex; ++j) {
			std::cin >> graph[i][j];
		}
	}

	auto cycle = GetNegativeCycle(graph);

	if (cycle.size() > 0) {
		std::cout << "YES\n";
		std::cout << cycle.size() << '\n';
		for (auto it = cycle.rbegin(); it != cycle.rend(); ++it) {
			std::cout << *it + 1 << ' ';
		}
	} else {
		std::cout << "NO\n";
	}

	return 0;
}