#include <iostream>
#include <vector>
#include <stack>

class StackMax : public std::stack<uint64_t> {
    std::stack<uint64_t> stack_max;
public:
    StackMax() = default;
    void MyPush(uint64_t value) {
        if (size() == 0 || value > stack_max.top()) {
            stack_max.push(value);
        } else {
            stack_max.push(stack_max.top());
        }
        push(value);
    }
    void MyPop() {
        pop();
        stack_max.pop();
    }
    uint64_t GetMax() {
        return stack_max.top();
    }
};

class QueryMaxQueue {
    StackMax first;
    StackMax second;
public:
    QueryMaxQueue() = default;
    void Push(uint64_t value) {
        first.MyPush(value);
    }
    void Pop() {
        if (second.size() > 0) {
            second.MyPop();
        } else {
            while (first.size() > 0) {
                second.MyPush(first.top());
                first.MyPop();
            }
            second.MyPop();
        }
    }
    uint64_t GetMax() {
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


int main() {
    QueryMaxQueue queue;
    queue.Push(8);
    queue.Push(2);
    queue.Push(7);
    std::cout << queue.GetMax() << '\n';
    queue.Pop();
    std::cout << queue.GetMax() << '\n';
    queue.Push(11);
    std::cout << queue.GetMax() << '\n';
    queue.Pop();
    std::cout << queue.GetMax() << '\n';
    queue.Push(1);
    queue.Pop();
    queue.Push(2);
    std::cout << queue.GetMax() << '\n';
    queue.Pop();
    std::cout << queue.GetMax() << '\n';
    queue.Pop();
    std::cout << queue.GetMax() << '\n';
    queue.Pop();
    std::cout << queue.GetMax() << '\n';
    return 0;
}