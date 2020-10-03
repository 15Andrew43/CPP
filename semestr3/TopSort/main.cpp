#include <iostream>
#include <vector>

using Graph = std::vector<std::vector<int>>;

enum Color {white=0, gray=1, black=2};

bool DFSVisit(const Graph& g, int v, std::vector<Color>& colors, std::vector<int> answer) {
    colors[v] = gray;
    for (auto neighbour: g[v]) {
        if (colors[v] == gray) {
//            error; // есть цикл
            return false;
        } else if (colors[v] == white) {
            DFSVisit(g, neighbour, colors, answer);
        }
    }
    colors[v] = black;
//    answer.push_front(v); // или пушбэк а потом реверзнуть
    answer.push_back(v);
}

std::vector<int> TopSort (const Graph& g) {
    std::vector<Color> colors(g.size(), white);
    std::vector<int> answer;
    for (int v = 0; v < g.size(); ++v) {
        if (colors[v] == white) {
            if (DFSVisit(g, v, colors, answer)) {
                return {};
            }
        }
    }
    return answer;
}


int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}