#include <iostream>
#include <vector>
#include <unordered_set>

// https://informatics.msk.ru/mod/statements/view.php?chapterid=111690#1

using Graph = std::vector<std::vector<int>>;

int infinity = 1000000;
int Time = -1;

enum Color {
    white=0, gray=1, black=3
};


struct DfsStatus {
    int time;
    std::vector<int> tin;
    std::vector<int> tup;
    std::vector<Color> colors;
    std::unordered_set<int> answer;

};

void DFS(int v, const Graph& graph, int parent, DfsStatus& dfs_status) {
    dfs_status.colors[v] = gray;
    dfs_status.tin[v] = dfs_status.tup[v] = ++Time;
    int n_children = 0;
    for (auto u: graph[v]) {
        if (dfs_status.colors[u] != white && parent != u) {
            dfs_status.tup[v] = std::min(dfs_status.tup[v], dfs_status.tin[u]);
        }
        if (dfs_status.colors[u] == white) {
            ++n_children;
            DFS(u, graph, v, dfs_status);
            dfs_status.tup[v] = std::min(dfs_status.tup[v], dfs_status.tup[u]);
            if (dfs_status.tin[v] < dfs_status.tup[u] && parent != -1) {
                dfs_status.answer.insert(v);
            }
        }
    }
    dfs_status.colors[v] = black;
    if (parent == -1 && n_children >= 2) {
        dfs_status.answer.insert(v);
    }
}

std::unordered_set<int> CutVertices(const Graph& graph) {
    DfsStatus dfs_status = {0,
                            std::vector<int>(graph.size(), -1),
                            std::vector<int>(graph.size(), infinity),
                            std::vector<Color>(graph.size(), white),
                            std::unordered_set<int>()
                            };
    for (int v = 0; v < graph.size(); ++v) {
        if (dfs_status.colors[v] == white) {
            DFS(v, graph, -1, dfs_status);
        }
    }
    return dfs_status.answer;
}

int main() {
    int n, m;
    std::cin >> n >> m;
    Graph graph(n, std::vector<int>());
    for (int i = 0; i < m; ++i) {
        int from, to;
        std::cin >> from >> to;
        --from, --to;
        graph[from].push_back(to);
        graph[to].push_back(from);
    }

    auto ans = CutVertices(graph);

    for (auto i = ans.begin(); i != ans.end(); ++i) {
        std::cout << *i << '\n';
    }

    std::cout << "Hello, World!" << std::endl;
    return 0;
}