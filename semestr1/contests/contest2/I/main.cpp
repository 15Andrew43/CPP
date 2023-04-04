#include <iostream>

using namespace std;

struct Node {
    long long int d;
    long long int min;
    Node* next;
};

struct Stack {
    Node* top;
    int size;
};

struct Queue {
    Stack left;
    Stack right;
    int size;
    long long int min;
};

void push_back(Stack &stack, long long int v);
int pop(Stack &stack);
long long int back(Stack stack);
long long int FindMin(Stack stack);
void clear(Stack &stack);

void enqueue(Queue &queue, long long int v);
long long int dequeue(Queue &queue);
long long int front(Queue &queue);
void clear_queue(Queue &queue);


int main() {
    int m;
    char operation[10];
    cin >> m;



    //initialization of queue
    Queue queue;
    queue.left.top = nullptr;
    queue.right.top = nullptr;
    queue.left.size = queue.right.size = 0;
    queue.size = 0;
    queue.min = 1000000001;


    for (int i = 0; i < m; ++i) {
        cin >> operation;
        if (operation[0] == 'e') {//enqueue
            cout << "ok\n";
            long int v;
            cin >> v;
            enqueue(queue, v);
        }
        else if (operation[0] == 'd') {//dequeue
            if (queue.size)
                cout << dequeue(queue) << endl;
            else
                cout << "error\n";
        }
        else if (operation[0] == 'f') {//front
            if (queue.size)
                cout << front(queue) << endl;
            else
                cout << "error\n";
        }
        else if (operation[0] == 'm') {//min
            if (queue.size) {
                cout << queue.min << endl;
            }
            else
                cout << "error\n";
        }
        else if (operation[0] == 's') {//size
            cout << queue.size << endl;
        }
        else {//clear
            cout << "ok\n";
            clear_queue(queue);
        }
    }
    return 0;
}

void clear_queue(Queue &queue) {
    queue.min = 1000000001;
    clear(queue.left);
    clear(queue.right);

    queue.size = queue.left.size + queue.right.size;
}

long long int front(Queue &queue) {
    if (!(queue.right.size)) {
        while (queue.left.size) {
            push_back(queue.right, pop(queue.left));
        }
    }
    return back(queue.right);
}

long long int dequeue(Queue &queue) {
    //queue.size--;

    if (!(queue.right.size)) {
        while (queue.left.size) {
            push_back(queue.right, pop(queue.left));
        }
    }

    long long int res = pop(queue.right);

    if (!(queue.right.size)) {
        while (queue.left.size) {
            push_back(queue.right, pop(queue.left));
        }
    }

    queue.size = queue.left.size + queue.right.size;
    if (queue.size) {
        queue.min = (queue.left.size ? min(FindMin(queue.right), FindMin(queue.left)) : FindMin(queue.right));
    }
    else {
        queue.min = 1000000001;
    }


    return res;
}

void enqueue(Queue &queue, long long int v) {
    //queue.size++;
    if (v < queue.min) {
        queue.min = v;
    }
    push_back(queue.left, v);

    queue.size = queue.left.size + queue.right.size;
}


void push_back(Stack &stack, long long int v) {
    Node* n = new Node;
    n -> d = v;
    n -> next = stack.top;
    if (!(stack.size) || v < stack.top->min) {
        n->min = v;
    }
    else {
        n->min = stack.top->min;
    }

    stack.size++;
    stack.top = n;
}

//////////////////////////////////
int pop(Stack &stack) {
    int res = stack.top->d;
    Node* prev = stack.top;
    stack.top = stack.top->next;
    delete prev;
    stack.size--;
    return res;
}


long long int back(Stack stack) {
    return stack.top->d;
}


long long int FindMin(Stack stack) {
    return stack.top->min;
}


void clear(Stack &stack) {
    stack.size = 0;
    while (stack.top) {
        Node *prev = stack.top;
        stack.top = stack.top->next;
        delete prev;
    }
}