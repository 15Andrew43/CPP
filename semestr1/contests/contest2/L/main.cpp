#include <iostream>

using namespace std;

struct Node {
    char d;
    Node* next;
};

struct Stack {
    Node* top;
};

void push_back(Stack &stack, char v);
char pop(Stack &stack);
char back(Stack stack);

char comparison(char c);

int main() {
    Stack stack;
    stack.top = nullptr;

    char c;
    while (cin.get(c)) {
        if (c == '\n')
            break;
        else if (stack.top && back(stack) == comparison(c)) {
            pop(stack);
        }
        else {
            push_back(stack, c);
        }
    }

    cout << ((!stack.top) ? ("yes") : ("no"));

    return 0;
}

char comparison(char c) {
    char comparied_c;
    switch (c) {
        case ')':
            comparied_c = '(';
            break;
        case ']':
            comparied_c = '[';
            break;
        case '}':
            comparied_c = '{';
            break;
    }
    return  comparied_c;
}


void push_back(Stack &stack, char v) {
    //size++;
    Node* n = new Node;
    n -> d = v;
    n -> next = stack.top;
    stack.top = n;
}

char back(Stack stack) {
    return stack.top->d;
}

char pop(Stack &stack) {
    //size--;
    char res = stack.top->d;
    Node* prev = stack.top;
    stack.top = stack.top->next;
    delete prev;
    return res;
}