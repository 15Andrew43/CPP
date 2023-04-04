#include <iostream>
#include <cstring>

using namespace std;

struct Node {
    long long int d;
    Node* next;
    Node* prev;
};

struct Dequeue {
    Node* head;
    Node* tail;
};

void push_back(Dequeue &dequeue, long int v, int &size);
void push_front(Dequeue &Dequeue, long int v, int &size);

long long int pop_back(Dequeue &dequeue, int &size);
long long int pop_front(Dequeue &dequeue, int &size);

long long int back(Dequeue dequeue);
long long int front(Dequeue dequeue);

long long int FindMin(Dequeue dequeue);
void clear(Dequeue &dequeue, int &size);

int main() {
    int m;
    string operation;
    cin >> m;

    //Node* head;
    //head = nullptr;
    Dequeue dequeue;
    dequeue.head = dequeue.tail = nullptr;

    int size = 0;

    for (int i = 0; i < m; ++i) {
        cin >> operation;
        if (operation == "push_back") {//push_back
            cout << "ok\n";
            long int v;
            cin >> v;
            push_back(dequeue, v, size);
        }
        else if (operation == "push_front") {//push_back
            cout << "ok\n";
            long int v;
            cin >> v;
            push_front(dequeue, v, size);
        }
        else if (operation == "pop_back") {//pop
            if (size)
                cout << pop_back(dequeue, size) << endl;
            else
                cout << "error\n";
        }
        else if (operation == "pop_front") {//pop
            if (size)
                cout << pop_front(dequeue, size) << endl;
            else
                cout << "error\n";
        }
        else if (operation == "back") {//back
            if (size)
                cout << back(dequeue) << endl;
            else
                cout << "error\n";
        }
        else if (operation == "front") {//back
            if (size)
                cout << front(dequeue) << endl;
            else
                cout << "error\n";
        }
        else if (operation == "size") {//size
            cout << size << endl;
        }
        else {//clear
            cout << "ok\n";
            clear(dequeue, size);
        }
    }
    return 0;
}


void push_back(Dequeue &dequeue, long int v, int &size) {
    size++;
    Node* n = new Node;
    n -> d = v;
    n -> next = dequeue.head;
    if (dequeue.head)
        dequeue.head -> prev = n;
    if (size == 1) {
        dequeue.tail = dequeue.head = n;
    }
    //n -> prev = nullptr;
    dequeue.head = n;
}

void push_front(Dequeue &dequeue, long int v, int &size) {
    size++;
    Node* n = new Node;
    n -> d = v;
    n -> next = nullptr;
    n -> prev = dequeue.tail;
    if (dequeue.tail)
        dequeue.tail -> next = n;
    if (size == 1) {
        dequeue.tail = dequeue.head = n;
    }
    dequeue.tail = n;
}


long long int pop_back(Dequeue &dequeue, int &size) {
    size--;
    int res = dequeue.head->d;
    Node* prev = dequeue.head;
    if (!size){
        dequeue.head = dequeue.tail = nullptr;
    }
    else {
        dequeue.head = dequeue.head->next;
    }
    delete prev;
    return res;
}

long long int pop_front(Dequeue &dequeue, int &size) {
    size--;
    int res = dequeue.tail->d;
    Node* next = dequeue.tail;
    if (!size){
        dequeue.head = dequeue.tail = nullptr;
    }
    else {
        dequeue.tail = dequeue.tail->prev;
        dequeue.tail->next = nullptr;
    }
    delete next;
    return res;
}


long long int back(Dequeue dequeue) {
    return dequeue.head->d;
}

long long int front(Dequeue dequeue) {
    return dequeue.tail->d;
}


void clear(Dequeue &dequeue, int &size) {
    size = 0;
    while (dequeue.head) {
        Node *prev = dequeue.head;
        dequeue.head = dequeue.head->next;
        delete prev;
    }
    dequeue.tail = nullptr;
}