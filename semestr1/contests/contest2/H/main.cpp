#include <iostream>

using namespace std;

struct Node {
    long long int d;
    long long int min;
    Node* next;
};

struct Stack {
    Node* top;
};

void push_back(Stack &stack, long int v, int &size);
int pop(Stack &stack, int &size);
int back(Stack stack);
long long int FindMin(Stack stack);
void clear(Stack &stack, int &size);

int main() {
    int m;
    char operation[10];
    cin >> m;

    //Node* head;
    //head = nullptr;
    Stack stack;
    stack.top = nullptr;


    int size = 0;

    for (int i = 0; i < m; ++i) {
        cin >> operation;
        if (operation[2] == 's') {//push
            cout << "ok\n";
            long int v;
            cin >> v;
            push_back(stack, v, size);
        }
        else if (operation[2] == 'p') {//pop
            if (size)
                cout << pop(stack, size) << endl;
            else
                cout << "error\n";
        }
        else if (operation[2] == 'c') {//back
            if (size)
                cout << back(stack) << endl;
            else
                cout << "error\n";
        }
        else if (operation[2] == 'n') {//min
            if (size) {
                cout << FindMin(stack) << endl;
            }
            else
                cout << "error\n";
        }
        else if (operation[2] == 'z') {//size
            cout << size << endl;
        }
        else {//clear
            cout << "ok\n";
            clear(stack, size);
        }
    }
    return 0;
}


void push_back(Stack &stack, long int v, int &size) {
    size++;
    Node* n = new Node;
    n -> d = v;
    n -> next = stack.top;
    if (!(stack.top) || v < stack.top->min) {
        n->min = v;
    }
    else {
        n->min = stack.top->min;
    }
    stack.top = n;
}


int pop(Stack &stack, int &size) {
    size--;
    int res = stack.top->d;
    Node* prev = stack.top;
    stack.top = stack.top->next;
    delete prev;
    return res;
}


int back(Stack stack) {
    return stack.top->d;
}


long long int FindMin(Stack stack) {
    return stack.top->min;
}


void clear(Stack &stack, int &size) {
    size = 0;
    while (stack.top) {
        Node *prev = stack.top;
        stack.top = stack.top->next;
        delete prev;
    }
}