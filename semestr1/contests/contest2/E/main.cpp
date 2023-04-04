#include <iostream>
#include <cstring>

using namespace std;

struct Node {
    int d;
    int ind;
};

int parent(int i){
    return (i - 1) / 2;
}

int leftSon(int i){
    return 2 * i + 1;
}

int rightSon(int i){
    return 2 * i + 2;
}

void siftDown(Node* &a, Node* &b, int size, int ind, bool IsMin){
    int left = leftSon(ind);
    int right = rightSon(ind);
    int ind_max = ind;

    if (right < size && left < size && a[right].d == a[left].d && (IsMin ? a[right].d < a[ind].d : a[right].d > a[ind].d)) {
        ind_max = left;
    }
    else {
        if (left < size && (IsMin ? a[left].d < a[ind_max].d : a[left].d > a[ind_max].d)) {
            ind_max = left;
        }

        if (right < size &&
            (IsMin ? a[right].d < a[ind_max].d : a[right].d > a[ind_max].d)) {
            ind_max = right;
        }
    }

    if (ind_max != ind){
        swap(b[a[ind].ind].ind, b[a[ind_max].ind].ind);
        swap(a[ind], a[ind_max]);
        siftDown(a, b, size, ind_max, IsMin);
    }
}

void siftUp(Node* &a, Node* &b, int ind, bool isMin){
    int i = ind;
    while ((isMin ? a[parent(i)].d > a[i].d : a[parent(i)].d < a[i].d) && i > 0){
        swap(b[a[i].ind].ind, b[a[parent(i)].ind].ind);
        swap(a[i], a[parent(i)]);
        i = parent(i);
    }
}

int getMin(Node* &aMin, Node* &aMax) {
    return aMin[0].d;
}

int getMax(Node* &aMin, Node* &aMax) {
    return aMax[0].d;
}

void insert(Node* &aMin, Node* &aMax, int &size, int v) {
    Node elem;
    elem.d = v;
    elem.ind = size;
    aMin[size] = elem;
    aMax[size] = elem;

    ++size;
    int tempSize = size - 1;
    siftUp(aMin, aMax, tempSize, true);
    tempSize = size - 1;
    siftUp(aMax, aMin, tempSize, false);
}

int extract(Node* &a, Node* &b, int size, int indToDelete, bool isMin) {
    swap(b[a[indToDelete].ind].ind, b[a[size - 1].ind].ind);
    swap(a[indToDelete], a[size - 1]);
    int result = a[size - 1].d;
    --size;
    if (indToDelete < size){
        siftDown(a, b, size, indToDelete, isMin);
        siftUp(a, b, indToDelete, isMin);
    }
    return result;
}

void clear(Node* &aMin, Node* &aMax, int &size)
{
    size = 0;
}

int main(){
    int m;
    cin >> m;

    Node * aMin = new Node[m];
    Node * aMax = new Node[m];

    int size = 0;

    char operation[15];

    for (int i = 0; i < m; ++i) {
        cin >> operation;
        if (strcmp(operation, "insert") == 0) {
            int v;
            cin >> v;
            insert(aMin, aMax, size, v);
            cout << "ok" << endl;
        }
        else if (strcmp(operation, "extract_min") == 0) {
            if (!size) {
                cout << "error" << endl;
            }
            else {
                cout << getMin(aMin, aMax) << endl;
                extract(aMin, aMax, size, 0, true);
                extract(aMax, aMin, size, aMin[size - 1].ind, false);
                size--;
            }
        }
        else if (strcmp(operation, "get_min") == 0) {
            if (size == 0) {
                cout << "error" << endl;
            }
            else {
                cout << getMin(aMin, aMax) << endl;
            }
        }
        else if (strcmp(operation, "extract_max") == 0) {
            if (size == 0) {
                cout << "error" << endl;
            }
            else {
                cout << getMax(aMin, aMax) << endl;
                extract(aMax, aMin, size, 0, false);
                extract(aMin, aMax, size, aMax[size - 1].ind, true);
                size--;
            }
        }
        else if (strcmp(operation, "get_max") == 0) {
            if (size == 0) {
                cout << "error" << endl;
            }
            else {
                cout << getMax(aMin, aMax) << endl;
            }
        }
        else if (strcmp(operation, "size") == 0) {
            cout << size << endl;
        }
        else if (strcmp(operation, "clear") == 0) {
            clear(aMin, aMax, size);
            cout << "ok" << endl;
        }
    }

    delete[] aMax;
    delete[] aMin;
}