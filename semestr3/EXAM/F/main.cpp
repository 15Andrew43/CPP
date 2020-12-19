/*
В стране N городов, некоторые из которых соединены между собой дорогами. Для того, чтобы проехать по одной дороге, требуется один бак бензина. В каждом городе бак бензина имеет разную стоимость. Вам требуется добраться из первого города в N-й, потратив как можно меньшее количество денег.

Формат ввода
В первой сроке вводится число N (1 ≤ N ≤ 500), в следующей идет N чисел, i-е из которых задает стоимость бензина в i-м городе (все числа целые из диапазона от 0 до 100). Затем идет число M — количество дорог в стране, далее идет описание самих дорог. Каждая дорога задается двумя числами — номерами городов, которые она соединяет. Все дороги двухсторонние (то есть по ним можно ездить как в одну, так и в другую сторону); между двумя городами всегда существует не более одной дороги; не существует дорог, ведущих из города в себя.

Формат вывода
Требеутся вывести одно число — суммарную стоимость маршрута или -1, если добраться невозможно.

Пример
Ввод    Вывод
5
3 6 1 7 6
8
1 2
5 4
5 1
3 4
5 2
2 4
2 3
3 1


3
*/

#include <iostream>
#include <queue>


using Graph = std::vector<std::vector<std::pair<int, int>>>;

int GetShortestPath(const Graph& graph, int from, int to, int max_dist, int infinity) {
    std::vector<bool> visited(graph.size(), false);
    std::vector<std::queue<int>> queues(max_dist + 1, std::queue<int>());
    std::vector<int> distance(graph.size(), infinity);
    distance[from] = 0;
    int id = 0; // number current queue
    queues[id].push(from);
    int count = 0;
    while (count < max_dist + 3) {
        while (!queues[id].empty()) {
            count = 0;
            int current_vertex = queues[id].front();
            queues[id].pop();
            if (visited[current_vertex]) {
                continue;
            }
            visited[current_vertex] = true;
            for (auto neighbour: graph[current_vertex]) {
                if (distance[neighbour.first] > distance[current_vertex] + neighbour.second) {
                    distance[neighbour.first] = distance[current_vertex] + neighbour.second;
                    queues[(id + neighbour.second) % (max_dist + 1)].push(neighbour.first);
                }
//                visited[neighbour.first] = true;
            }
        }
        ++count;
        id = (id + 1) % (max_dist + 1);
    }
    return ((distance[to] == infinity)?(-1):(distance[to]));
}

int main() {
    int v_cnt;
    int e_cnt;
    std::cin >> v_cnt;
    std::vector<int> price(v_cnt);
    for (int i = 0; i < v_cnt; ++i) {
        std::cin >> price[i];
    }
    std::cin >> e_cnt;

    int start = 0;
    int finish = v_cnt - 1;
    int max_dist = 0;

    Graph graph(v_cnt, std::vector<std::pair<int, int>>());

    for (int i = 0; i < e_cnt; ++i) {
        int from, to;
        std::cin >> from >> to;
        --from, --to;
        if (max_dist < price[from]) {
            max_dist = price[from];
        }
        if (max_dist < price[to]) {
            max_dist = price[to];
        }
        graph[from].push_back(std::make_pair(to, price[from]));
        graph[to].push_back(std::make_pair(from, price[to]));
    }

    std::cout << GetShortestPath(graph, start, finish, max_dist, max_dist * v_cnt);

    return 0;
}