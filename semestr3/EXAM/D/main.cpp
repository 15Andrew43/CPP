/*
 Двудольным графом называется неориентированный граф (V,E),  такой, что его множество вершин V можно разбить на два множества A и B, для которых  e1 ∈ A, e2 ∈ B и , .

Паросочетанием в двудольном графе называется любой набор его несмежных рёбер, то есть такой набор , что для любых двух рёбер e1 = (u1, v1), e2 = (u2, v2) из S  и .

Ваша задача — найти максимальное паросочетание в двудольном графе, то есть паросочетание с максимально возможным числом рёбер.

Формат ввода
В первой строке записаны два целых числа n и m (), где n — число вершин в множестве A, а m — число вершин в B.

Далее следуют n строк с описаниями рёбер — i-я вершина из A описана в (i+1)-й строке файла. Каждая из этих строк содержит номера вершин из B, соединённых с i-й вершиной A. Вершины в A и B нумеруются независимо (с единицы). Список завершается числом 0.

Формат вывода
Первая строка выходного файла должна содержать одно целое число l — количество рёбер в максимальном паросочетании. Далее следуют l строк, в каждой из которых должны быть два целых числа uj и vj — концы рёбер паросочетания в A и B соотвественно.

Пример
Ввод	Вывод
2 2
1 2 0
2 0

2
1 1
2 2
 */

#include <iostream>
#include <vector>
#include <utility>

using weight_t = int ;

struct Edge {
    int to;
    weight_t flow;
    weight_t capacity;
    int back;
    Edge(int to, weight_t flow, weight_t capacity, int back) : to(to), flow(flow), capacity(capacity), back(back) {
    }

};

using Graph = std::vector<std::vector<Edge>>;

enum Status {
    kUndiscovered = 0,
    kDiscovered = 1,
};


int FindFlow(Graph& graph, std::vector<Status>& statuses, int from, int to, weight_t max_flow) {
    statuses[from] = kDiscovered;
    if (from == to) {
//        std::cout << max_flow << "\n";
        return max_flow;
    }
    for (auto& edge: graph[from]) {
        if (statuses[edge.to] == kUndiscovered && edge.capacity - edge.flow > 0) {
            int cur_flow = FindFlow(graph, statuses, edge.to, to, std::min(max_flow, edge.capacity - edge.flow));
            if (cur_flow > 0) {
                edge.flow += cur_flow;
                graph[edge.to][edge.back].flow -= cur_flow;
                return cur_flow;
            }
        }
    }
    return 0;
}

int FordFalcon(Graph& graph, int from, int to) {
    int cur_flow;
    int res_flow = 0;
    do {
        std::vector<Status> statuses(graph.size(), kUndiscovered);
        cur_flow = FindFlow(graph, statuses, from, to, 1000000);
        res_flow += cur_flow;
    } while (cur_flow > 0);

    return res_flow;
}

int main() {
    int cnt_vertexA, cnt_vertexB;
    std::cin >> cnt_vertexA >> cnt_vertexB;

    Graph info_graph(cnt_vertexA + cnt_vertexB);

    for (int i = 0; i < cnt_vertexA; ++i) {
        int to;
        while (true) {
            std::cin >> to;
            if (to == 0) {
                break;
            }
            info_graph[i].emplace_back((to - 1) + cnt_vertexA, 0, 1, info_graph[(to - 1) + cnt_vertexA].size());
            info_graph[(to - 1) + cnt_vertexA].emplace_back(i, 0, 0, info_graph[i].size() - 1);
        }
    }

    info_graph.push_back(std::vector<Edge>());
    for (int i = 0; i < cnt_vertexA; ++i) {
        info_graph.back().emplace_back(i, 0, 1, info_graph[i].size());
        info_graph[i].emplace_back(cnt_vertexA + cnt_vertexB, 0, 0, info_graph.back().size() - 1);
    }
    info_graph.push_back(std::vector<Edge>());
    for (int i = cnt_vertexA; i < cnt_vertexA + cnt_vertexB; ++i) {
        info_graph[i].emplace_back(cnt_vertexA + cnt_vertexB + 1, 0, 1, info_graph.back().size());
        info_graph.back().emplace_back(i, 0, 0, info_graph[i].size() - 1);
    }
    std::cout << FordFalcon(info_graph, cnt_vertexA + cnt_vertexB, cnt_vertexA + cnt_vertexB + 1) << '\n';


    for (int i = 0; i < cnt_vertexA; ++i) {
        for (int j = 0; j < info_graph[i].size(); ++j) {
            Edge& edge = info_graph[i][j];
//            std::cout << "=======   "<< i << ' ' << edge.to << ' ' << edge.flow << '\n';
            if (edge.to > cnt_vertexA + cnt_vertexB - 1) {
                continue;
            }
            if (edge.flow == 1) {
                std::cout << i + 1 << ' ' << edge.to - cnt_vertexA + 1 << '\n';
            }
        }
    }
    return 0;
}

/*
4 5
1 2 4
1 3 5
2 3 2
2 4 2
3 4 6
 */