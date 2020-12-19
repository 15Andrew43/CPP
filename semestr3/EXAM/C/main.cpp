/*
 Отрезок целочисленной прямой длины N разбит на единичные отрезки, которые пронумерованы от 1 до N.

Их объединяют в группы по следующим правилам:

Несколько подряд идущих отрезков, ни один из которых не принадлежит ни одной из групп, могут быть объединены в группу.
Любая ранее созданная группа может быть уничтожена, при этом входившие в нее отрезки больше не относятся ни к какой группе и могут впоследствии быть отнесены к другим группам.
Видно, что любой отрезок всегда находится не более, чем в одной группе.

Каждую группу можно идентифицировать парой чисел: номером первого и номером последнего отрезка, входящего в группу.

Первоначально нет ни одной группы.

Формат ввода
Первая строка входных данных содержит число N — количество отрезков и число K — количество запросов (1 ≤ N, K ≤ 105). Далее идет K строчек, содержащих запросы к структуре данных. Каждый запрос начинается с числа 1 (запрос на создание группы) или 2 (запрос на удаление группы). После числа 1 указывается два других числа l и r (1 ≤ l ≤ r ≤ N), после числа 2 указывается одно число i (1 ≤ i ≤ N).

Формат вывода
Для каждого запроса типа 1 необходимо отрезки с номерами от l до r объединить в группу. Если все эти отрезки не входят ни в одну группу, запрос считается удачным и программа должна вывести 1. Если хотя бы один из этих отрезков уже относится к какой-то группе, запрос считается неудачным, объединение не производится и программа выводит 0.

Для каждого запроса типа 2 необходимо удалить группу, в которую входит отрезок с номером i, при этом программа должна вывести два числа: номер первого и последнего отрезка, входящих в удаляемую группу. Если отрезок с номером i не относится ни к одной группе, программа должна вывести два нуля.

Пример
Ввод
5 6
1 1 2
1 4 5
1 2 4
2 5
2 1
2 4
 Вывод
1
1
0
4 5
1 2
0 0
*/
#include <iostream>
#include <vector>
#include <algorithm>

class SegmentTree {
    int n;
    std::vector<int> x;
    std::vector <std::pair<int, int> > tree;
    std::vector<char> free;
public:
    SegmentTree(int _n) : n(_n) {
        tree.resize(4 * n, { -1,-1 });
        free.resize(4 * n, 1);
    }

    void push(int ver) {
        if (tree[ver] != std::pair<int, int>{-1, -1}) {
            tree[ver * 2] = tree[ver * 2 + 1] = tree[ver];
            if (tree[ver] != std::pair<int, int>({ -1,0 })) {
                free[ver * 2] = free[ver * 2 + 1] = 0;
            } else {
                free[ver * 2] = free[ver * 2 + 1] = 1;
            }
            tree[ver] = {-1, -1};
        }
    }

    void update(int ver, int l_lim, int r_lim, int left, int right, std::pair<int, int> val) {
        if (left > right) {
            return;
        }
        if (l_lim == left && r_lim == right) {
            tree[ver] = val;
            free[ver] = val == std::pair<int, int>({-1, 0});
        } else {
            push(ver);
            int mid = l_lim + r_lim >> 1;
            update(ver * 2, l_lim, mid, left, std::min(mid, right), val);
            update(ver * 2 + 1, mid + 1, r_lim, std::max(mid + 1, left), right, val);
            free[ver] = std::min(free[ver * 2], free[ver * 2 + 1]);
        }
    }

    bool query(int ver, int l_lim, int r_lim, int left, int right)  {
        if (left > right) {
            return 1;
        }
        if (l_lim == left && r_lim == right) {
            return free[ver];
        }
        push(ver);
        int mid = l_lim + r_lim >> 1;
        return std::min(query(ver * 2, l_lim, mid, left, std::min(mid, right)),
                   query(ver * 2 + 1, mid + 1, r_lim, std::max(mid + 1, left), right));
    }

    std::pair<int, int> get_identity(int ver, int l_lim, int r_lim, int pos) {
        if (l_lim == r_lim) {
            return tree[ver];
        }
        push(ver);
        int mid = l_lim + r_lim >> 1;
        if (pos <= mid) {
            return get_identity(ver * 2, l_lim, mid, pos);
        }
        return get_identity(ver * 2 + 1, mid + 1, r_lim, pos);
    }

};

int main() {
    int n;
    int k;
    std::cin >> n >> k;
    SegmentTree st(n);

    for(int i = 0; i < k; ++i) {
        int type;
        std::cin >> type;
        if (type == 1) {
            int from, to;
            std::cin >> from >> to;
            --from;
            --to;
            if (!st.query(1, 0, n - 1, from, to)) {
                std::cout << 0 << '\n';
            } else {
                std::cout << 1 << '\n';
                st.update(1, 0, n - 1, from, to, { from, to });
            }
        } else {
            int pos;
            std::cin >> pos;
            --pos;
            auto ident = st.get_identity(1, 0, n - 1, pos);
            if ((ident == std::pair<int, int>{-1, -1}) || (ident == std::pair<int, int>({-1, 0}))) {
                std::cout << 0 << ' ' << 0 << '\n';
            } else {
                std::cout << ident.first + 1 << ' ' << ident.second + 1 << '\n';
                st.update(1, 0, n - 1, ident.first, ident.second, {-1, 0});
            }
        }
    }
    return 0;
}