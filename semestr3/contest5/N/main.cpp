#include <iostream>
#include <vector>
#include <stack>

class StackMax : public std::stack<std::pair<uint64_t, uint32_t>> {
    std::stack<std::pair<uint64_t, uint32_t>> stack_max;
public:
    StackMax() = default;
    void MyPush(uint64_t value, uint32_t ind) {
        if (size() == 0 || value > stack_max.top().first) {
            stack_max.push({value, ind});
        } else {
            stack_max.push(stack_max.top());
        }
        push({value, ind});
    }
    void MyPop() {
        pop();
        stack_max.pop();
    }
    std::pair<uint64_t , uint32_t> GetMax() {
        return stack_max.top();
    }
};

class QueryMaxQueue {
    StackMax first;
    StackMax second;
public:
    QueryMaxQueue() = default;
    void Push(uint64_t value, uint32_t ind) {
        first.MyPush(value, ind);
    }
    void Pop() {
        if (second.size() > 0) {
            second.MyPop();
        } else {
            while (first.size() > 0) {
                second.MyPush(first.top().first, first.top().second);
                first.MyPop();
            }
            second.MyPop();
        }
    }
    std::pair<uint64_t, uint32_t> GetMax() {
        if (first.size() > 0 && second.size() > 0) {
            return std::max(first.GetMax(), second.GetMax());
        }
        if (first.size() == 0 && second.size() != 0) {
            return second.GetMax();
        }
        if (first.size() != 0 && second.size() == 0) {
            return first.GetMax();
        }
        throw 1;
    }
};

std::vector<std::vector<std::vector<std::vector<uint32_t>>>> GetMaxSpace(const std::vector<std::vector<std::vector<std::pair<uint64_t, uint32_t >>>>& space,
                                                            uint32_t x_len, uint32_t y_len, uint32_t z_len,
                                                            uint32_t see_x, uint32_t see_y, uint32_t see_z) {
    std::vector<std::vector<std::vector<std::pair<uint64_t, uint32_t>>>> max_space = space;
    std::vector<std::vector<std::vector<std::vector<uint32_t>>>> max_space_ind(x_len, std::vector<std::vector<std::vector<uint32_t>>>(y_len, std::vector<std::vector<uint32_t>>(z_len)));

    for (uint32_t x = 0; x < x_len; ++x) {
        std::cout << "=============================\n";
        for (uint32_t y = 0; y < y_len; ++y) {
            QueryMaxQueue queue;
            std::cout << "pep\n";

            for (uint32_t i = 0; i < see_z; ++i) {
                queue.Push(max_space[x][y][i].first, max_space[x][y][i].first);
            }
            for (uint32_t z = 0; z < z_len - see_z; ++z) {
                max_space[x][y][z] = queue.GetMax();
                max_space_ind[x][y][z].push_back(max_space[x][y][z].second);
                queue.Push(max_space[x][y][z + see_z].first, max_space[x][y][z + see_z].second);
                queue.Pop();
            }
            for (uint32_t z = z_len - see_z + 1; z < z_len; ++z) {
                max_space[x][y][z] = queue.GetMax();
                max_space_ind[x][y][z].push_back(max_space[x][y][z].second);
                queue.Pop();
            }
            std::cout << "------------------------\n";
        }
    }
    std::cout << "kasdgsdfklsfsd\n";
    for (uint32_t z = 0; z < z_len; ++z) {
        for (uint32_t x = 0; x < x_len; ++x) {
            QueryMaxQueue queue;
            for (uint32_t i = 0; i < see_y; ++i) {
                queue.Push(max_space[x][i][z].first, max_space[x][i][z].second);
            }
            for (uint32_t y = 0; y < y_len - see_y; ++y) { //??????????????
                max_space[x][y][z] = queue.GetMax();
                max_space_ind[x][y][z].push_back(max_space[x][y][z].second);
                queue.Push(max_space[x][y + see_y][z].first, max_space[x][y + see_y][z].second);
                queue.Pop();
            }
            for (uint32_t y = y_len - see_y + 1; y < y_len; ++y) {
                max_space[x][y][z] = queue.GetMax();
                max_space_ind[x][y][z].push_back(max_space[x][y][z].second);
                queue.Pop();
            }
        }
    }
    std::cout << "asdfasdfasdfasdfasdfasdfasdfasdfasdfasdf\n";

    for (uint32_t y = 0; y < y_len; ++y) {
        for (uint32_t z = 0; z < z_len; ++z) {
            QueryMaxQueue queue;
            for (uint32_t i = 0; i < see_x; ++i) {
                queue.Push(max_space[i][y][z].first, max_space[i][y][z].second);
            }
            for (uint32_t x = 0; x < x_len - see_x; ++x) {
                max_space[x][y][z] = queue.GetMax();
                max_space_ind[x][y][z].push_back(max_space[x][y][z].second);
                queue.Push(max_space[x + see_x][y][z].first, max_space[x + see_x][y][z].second);
                queue.Pop();
            }
            for (uint32_t x = x_len - see_x + 1; x < x_len; ++x) {
                max_space[x][y][z] = queue.GetMax();
                max_space_ind[x][y][z].push_back(max_space[x][y][z].second);
                queue.Pop();
            }
        }
    }
    std::cout << "                           asdfasdfasdfasdfasdfasdfasdfasdfasdfasdf\n";

    return max_space_ind;
}

int main() {
    uint32_t x_len, y_len, z_len;
    std::cin >> x_len >> y_len >> z_len;
    uint32_t see_x, see_y, see_z;
    std::cin >> see_x >> see_y >> see_z;
    std::vector<std::vector<std::vector<std::pair<uint64_t, uint32_t>>>> space(x_len, std::vector<std::vector<std::pair<uint64_t, uint32_t>>>(y_len, std::vector<std::pair<uint64_t, uint32_t >>(z_len)));
    for (uint32_t x = 0; x < x_len; ++x) {
        for (uint32_t y = 0; y < y_len; ++y) {
            for (uint32_t z = 0; z < z_len; ++z) {
                std::cin >> space[x][y][z].first;
            }
        }
    }

    auto max_space_ind = GetMaxSpace(space, x_len, y_len, z_len, see_x, see_y, see_z);



    uint32_t cnt_positions;
    std::cin >> cnt_positions;

    for (uint32_t i = 0; i < cnt_positions; ++i) {
        uint32_t x, y, z;
        std::cin >> x >> y >> z;
        auto coord = max_space_ind[x][y][z];
        for (auto lol: coord) {
            std::cout << lol << ' ';
        }
        std::cout << '\n';
        while (x != coord[0] || y != coord[1] || z != coord[2]) {
            x = coord[0];
            y = coord[1];
            z = coord[2];
            coord = max_space_ind[x][y][z];
        }
        std::cout << x << ' ' << y << ' ' << z << '\n';
    }

    return 0;
}