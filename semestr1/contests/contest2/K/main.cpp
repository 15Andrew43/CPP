#include <iostream>

using namespace std;

struct Node {
    int d;
    //long long int min;
    Node* next;
};

struct Stack {
    Node* top;
};

void push_back(Stack &stack, int v);
int pop(Stack &stack);

int convert_CharToInt(char c);

int main() {
    Stack stack;
    stack.top = nullptr;

    char c;
    while (cin.get(c)) {
        if (c == '\n')
            break;
        else if (c != ' ') {
            if (c == '+' || c == '-' || c == '*') {
                int a, b;
                b = pop(stack);
                a = pop(stack);
                switch (c) {
                    case '+':
                        push_back(stack, a+b);
                        break;
                    case '-':
                        push_back(stack, a-b);
                        break;
                    case '*':
                        push_back(stack, a*b);
                        break;
                }
            }
            else {
                push_back(stack, convert_CharToInt(c));
            }
        }
    }
    cout << stack.top->d;


    return 0;
}

int convert_CharToInt(char c) {
    return c-'0';
}


void push_back(Stack &stack, int v) {
    //size++;
    Node* n = new Node;
    n -> d = v;
    n -> next = stack.top;
    stack.top = n;
}


int pop(Stack &stack) {
    //size--;
    int res = stack.top->d;
    Node* prev = stack.top;
    stack.top = stack.top->next;
    delete prev;
    return res;
}