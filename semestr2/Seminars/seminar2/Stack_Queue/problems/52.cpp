#include <iostream>
#include <cstring>
#include <iomanip>

typedef int T;

struct Node {
    T value_;
    Node* prev;
};


class Stack {
    Node* head_ = nullptr;
    size_t size_ = 0;
public:
    void Push(T value);
    void Pop();
    T Top() const;
    T& Top();
    
    void Clear();
    bool Empty() const;
    size_t Size() const;

    Stack() = default;

    Stack& operator=(const Stack& other);

    ~Stack();

    friend void rehandling(Stack& L, Stack& R);
};


int main() {
    Stack stack;
    char c;

    while (std::cin.get(c)) {
        if (c == '\n')
            break;
        else if (c != ' ') {
            if (c == '+' || c == '-' || c == '*') {
                int a, b;
                a = stack.Top();
                stack.Pop();
                b = stack.Top();
                stack.Pop();
                switch (c) {
                    case '+':
                        stack.Push(a+b);
                        break;
                    case '-':
                        stack.Push(b-a);
                        break;
                    case '*':
                        stack.Push(a*b);
                        break;
                }
            }
            else {
                stack.Push(atoi(&c));
            }
        }
    }
    std::cout << stack.Top();


    return 0;
}

void Stack::Push(T value) {
    Node* t = new Node;
    t->value_ = value;
    t->prev = head_;
    head_ = t;
    ++size_;
}

void Stack::Pop() {
    Node* t = head_;
    head_ = head_->prev;
    delete t;
    --size_;
}

T Stack::Top() const {
    return head_->value_;
}

T& Stack::Top() {
    return head_->value_;
}

void Stack::Clear() {
    while (head_) {
        Node* t = head_;
        head_ = head_->prev;
        delete t;
    }
    size_ = 0;
}

bool Stack::Empty() const {
    return size_ == 0;
}
size_t Stack::Size() const {
    return size_;
}


Stack& Stack::operator=(const Stack& other) {
    Stack s;
    Node* ptr = other.head_;
    while (ptr) {
        s.Push(ptr->value_);
        ptr = ptr->prev;
    }
    ptr = s.head_;
    while (ptr) {
        Push(ptr->value_);
        ptr = ptr->prev;
    }
    delete ptr;
    return *this;
}

Stack::~Stack() {
    Clear();
    delete head_;
}
