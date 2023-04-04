
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

void siftDown(Node* &a, int* &insertIndex, int size, int ind){
    int left = leftSon(ind);
    int right = rightSon(ind);
    int ind_max = ind;

    if (right < size && left < size && a[right].d == a[left].d && a[right].d < a[ind].d){
        ind_max = left;
    }
    else {
        if (left < size && a[left].d < a[ind_max].d) {
            ind_max = left;
        }

        if (right < size && a[right].d < a[ind_max].d) {
            ind_max = right;
        }
    }

    if (ind_max != ind){
        swap(insertIndex[a[ind].ind], insertIndex[a[ind_max].ind]);
        swap(a[ind], a[ind_max]);
        siftDown(a, insertIndex, size, ind_max);
    }
}

void siftUp(Node* &a, int* &insertIndex, int ind){
    int i = ind;
    while (a[parent(i)].d > a[i].d && i > 0){
        swap(insertIndex[a[i].ind], insertIndex[a[parent(i)].ind]);
        swap(a[i], a[parent(i)]);
        i = parent(i);
    }
}

int extractMin(Node* &a, int* &insertIndex, int& size){
    Node max_elem = a[0];
    swap(insertIndex[a[0].ind], insertIndex[a[size - 1].ind]);
    swap(a[0], a[size - 1]);

    insertIndex[a[size - 1].ind] = -1;

    --size;
    if (size){
        siftDown(a, insertIndex, size, 0);
    }
    return max_elem.d;
}

int getMin(Node* &a, int* &insertIndex, int& size)
{
    return a[0].d;
}

void insert(Node* &a, int &size, int* &insertIndex, Node key, int currInsert){
    a[size] = key;
    insertIndex[currInsert] = size;
    ++size;
    int tempSize = size - 1;
    siftUp(a, insertIndex, tempSize);
}

void extract(Node* &a, int* &insertIndex, int &size, int indToDelete){

    swap(insertIndex[a[indToDelete].ind], insertIndex[a[size - 1].ind]);
    swap(a[indToDelete], a[size - 1]);

    insertIndex[a[size - 1].ind] = -1;

    --size;
    if (indToDelete < size){
        siftDown(a, insertIndex, size, indToDelete);
        siftUp(a, insertIndex, indToDelete);
    }
}

void clear(Node* &a, int* &insertIndex, int &size)
{
    for (int i = 0; i < size; ++i) {
        insertIndex[a[i].ind] = -1;
    }
    size = 0;
}

int main() {
    int m;
    cin >> m;

    Node *a = new Node[m];
    int size = 0;
    int *IndexInsert = new int[m];
    for (int i = 0; i < m; ++i) {
        IndexInsert[i] = -1;
    }
    int InsertCurr = 0;

    char task[15];

    for (int i = 0; i < m; ++i) {
        cin >> task;
        if (strcmp(task, "insert") == 0) {
            Node elem;
            cin >> elem.d;
            elem.ind = InsertCurr;
            insert(a, size, IndexInsert, elem, InsertCurr);

            InsertCurr++;

            cout << "ok" << endl;
        } else if (strcmp(task, "extract_min") == 0) {
            if (size == 0) {
                cout << "error" << endl;
            } else {
                cout << extractMin(a, IndexInsert, size) << endl;
            }
        } else if (strcmp(task, "delete") == 0) {
            int x;
            cin >> x;
            if (IndexInsert[x - 1] == -1) {
                cout << "error" << endl;
            } else {
                extract(a, IndexInsert, size, IndexInsert[x - 1]);
                cout << "ok" << endl;
            }
        } else if (strcmp(task, "change") == 0) {
            int x, n;
            cin >> x >> n;
            if (IndexInsert[x - 1] == -1) {
                cout << "error" << endl;
            } else {
                Node elem = a[IndexInsert[x - 1]];
                elem.d = n;
                extract(a, IndexInsert, size, IndexInsert[x - 1]);
                insert(a, size, IndexInsert, elem, x - 1);
                cout << "ok" << endl;
            }
        } else if (strcmp(task, "get_min") == 0) {
            if (size == 0) {
                cout << "error" << endl;
            } else {
                cout << getMin(a, IndexInsert, size) << endl;
            }
        } else if (strcmp(task, "size") == 0) {
            cout << size << endl;
        } else if (strcmp(task, "clear") == 0) {
            clear(a, IndexInsert, size);
            cout << "ok" << endl;
        }
    }

    delete[] a;
    delete[] IndexInsert;
}