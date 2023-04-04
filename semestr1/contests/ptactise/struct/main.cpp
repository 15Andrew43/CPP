#include <iostream>

using namespace std;

struct Node {
    int data;
    Node * prev;
    Node * next;
};

Node * first(int data) {
    Node * p = new Node;
    p->data = data;
    p->next = p->prev = nullptr;
    return p;
}

struct two_path_list {
    Node * beg;
    Node * end;
};

void push_front(two_path_list & l, int d) {
    Node * p = new Node;
    p->data = d;
    p->next = l.beg;
    l.beg->prev = p;
    p->prev = nullptr;
    l.beg = p;
}

void push_back(two_path_list & l, int d) {
    Node * p = new Node;
    p->data = d;
    p->prev = l.end;
    l.end->next = p;
    p->next = nullptr;
    l.end = p;
}

int main() {
    int a = 0;
    Node * p = first(a);
    two_path_list l = {p, p};

    short k = 1;
    int count = 1;
    for (int i = 0; i < 100; ++i) {
        if (k==1) {
            push_back(l, count);
        }
        else if (k==-1) {
            push_front(l, count);
            count++;
        }
        k*=(-1);
    }
    cout << "Hello, World!" << endl;

    for (Node * p = l.beg; p; p = p->next) {
        cout << p->data << ' ';
    }

    return 0;
}