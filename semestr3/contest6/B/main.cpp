#include <iostream>
#include <vector>
#include <algorithm>

int GetNextPow2(int n) {
    int cur_n = 1;
    while (cur_n < n) {
        cur_n *= 2;
    }
    return cur_n;
}

class Node {
public:
    int key;

//    int value;
//    int result;
//    int promise;

    int priority;

    Node* left = nullptr;
    Node* right = nullptr;
    Node* parent = nullptr;

    size_t size = 1;

    ~Node() {
        delete left;
        delete right;
    }
};

class Treap { // Tree + Heap, CartesianTree

    Node* root_ = nullptr;
//    static const int kNeutral = 1;

    static size_t Size(Node* node) {
        return node ? node->size : 0;
    }
/*
    static int Result(Node* node) {
        return node ? node->result * node->promise : kNeutral; // neutral element for operation
    }
*/
    static void UpdateNode(Node* node) {
        if (node) {
            node->size = 1 + Size(node->left) + Size(node->right);
//            node->result = operation(Result(node->left),
//                                     operation(node->value, Result(node->right)));
            // node->result = Result(node->left) + Result(node->right) + node->value;
        }
    }
/*
    static void Push(Node* node) {
        if (!node) {
            return;
        }
        if (node->left) {
            node->left->promise = node->left->promise * node->promise; // 1 - node->promise (xor)
        }
        if (node->right) {
            node->right->promise = node->right->promise * node->promise;
        }
        node->value = operation(node->value, node->promise); // if promise == 1 : swap(left, right)
        node->result = operation(node->result, node->promise);
        node->promise = kNeutral; // neutral elem
    }
*/
    static void SetLeft(Node* node, Node* new_left) {
//        Push(node);
        if (node) {
            node->left = new_left;
        }
        if (new_left) {
            new_left->parent = node;
        }
        UpdateNode(node);
    }

    static void SetRight(Node* node, Node* new_right) {
//        Push(node);
        if (node) {
            node->right = new_right;
        }
        if (new_right) {
            new_right->parent = node;
        }
        UpdateNode(node);
    }

    static std::pair<Node*, Node*> Split(Node* node, const int& key) { // key -> size_t idx
        if (node == nullptr) {
            return {nullptr, nullptr};
        }
        if (node->key < key) {
            auto [less_tree, ge_tree] = Split(node->right, key);
            SetRight(node, less_tree);
            return {node, ge_tree};
        }
        else {
            auto [less_tree, ge_tree] = Split(node->left, key);
            SetLeft(node, ge_tree);
            return {less_tree, node};
        }
    }

    static Node* Merge(Node* left_root, Node* right_root) { // keys(left_root) < keys(right_root)
        if (!left_root) {
            return right_root;
        }
        if (!right_root) {
            return left_root;
        }
        if (left_root->priority < right_root->priority) { // was < ????????????????????????????????????????
//            Push(right_root);
            SetLeft(right_root, Merge(left_root, right_root->left));
            return right_root;
        } else { // left_root->priority >= right_root->priority
//            Push(left_root);
            SetRight(left_root, Merge(left_root->right, right_root));
            return left_root;
        }
    }

    static Node* Find(Node* node, const int& key) {
        if (node == nullptr) {
            return nullptr;
        } else if (node->key < key) {
            return Find(node->right, key);
        } else if (node->key > key) {
            return Find(node->left, key);
        } else {
            return node;
        }
    }

    static std::pair<Node*, Node*> Insert(Node* root, const int& key, const int& priority) {
        auto [less_tree, ge_tree] = Split(root, key);
        Node* new_node = new Node;
        new_node->key = key;
        new_node->priority = priority;
        return {
                Merge(
                        Merge(less_tree, new_node), ge_tree
                )
                , new_node
        };
    }

    static Node* Erase(Node* root, const int& key) {
//        std::cout << "deleting " << key << '\n';
        if (Find(root, key) == nullptr) {
//            std::cout << "not found key " << key << '\n';
            return root;
        }
        auto [less_tree, ge_tree] = Split(root, key);
//        std::cout << (less_tree == nullptr) << ' ' << (ge_tree == nullptr) << '\n';
        auto [equal_tree, greater_tree] = Split(ge_tree, key + 1); // key + 0:
//        std::cout << (equal_tree == nullptr) << ' ' << (greater_tree == nullptr) << '\n';
        delete equal_tree;
        return Merge(less_tree, greater_tree);
    }

    static Node* Next(Node*& root, const int& key) {
        int new_key = key + 1; // ??????????????????????????????????????????????????????
        auto [less_tree, ge_tree] = Split(root, new_key);
        auto cur_tree = ge_tree;
        while (cur_tree && cur_tree->left) {
            cur_tree = cur_tree->left;
        }
        root = Merge(less_tree, ge_tree);
        return cur_tree;
    }

    static Node* Prev(Node*& root, const int& key) {
        int new_key = key; // ???????????????????????????????????????????????????????????????
        auto [less_tree, ge_tree] = Split(root, new_key);
        auto cur_tree = less_tree;
        while (cur_tree && cur_tree->right) {
            cur_tree = cur_tree->right;
        }
        root = Merge(less_tree, ge_tree);
        return cur_tree;
    }

    static Node* Get(Node* node, const int& idx) {
//        if (!Find(node, idx)) {
//            return nullptr;
//        }
        if (node == nullptr) {
            return nullptr;
        } else if (Size(node->left) == idx) {
            return node;
        } else if (Size(node->left) < idx) {
            return Get(node->right, idx - Size(node->left) - 1);
        } else {
            return Get(node->left, idx);
        }
    }

//    template <class FwdIterator>
//    static Node* BuildFromSorted(FwdIterator begin, FwdIterator end) {
//        int cnt_elements = end - begin;
//        int next_pow2 = GetNextPow2(cnt_elements);
//        std::vector<Node*> treaps(next_pow2, nullptr);
//        for (auto it = begin; it != end; ++it) {
//            treaps[it - begin] = new Node{it->key, it->priority};
//        }
//        while (next_pow2 > 1) {
//            for (int i = 0; i < next_pow2; i += 2) {
//                treaps[i / 2] = Merge(treaps[i], treaps[i + 1]);
//            }
//            next_pow2 /= 2;
//        }
//        return treaps[0];
//    }
public:
    Treap() = default;
//    template <class FwdIterator>
//    Treap(FwdIterator begin, FwdIterator end) {
//        if (std::is_sorted(begin, end, [](const auto& x, const auto& y) {
//            return x.key < y.key;
//        })) {
//            root_ = BuildFromSorted(begin, end);
//        } else {
//            for (auto it = begin; it != end; ++it) {
//                Insert(it->key, it->priority);
//            }
//        }
//    }

    size_t Size() const {
        return Size(root_);
    }

    Node* Find(const int& key) const {
        return Find(root_, key);
    }

    std::pair<Node*, Node*> Insert(const int& key, const int& priority) {
        auto nodes = Insert(root_, key, priority);
        root_ = nodes.first;
        return nodes;
    }

    Node* Erase(const int& key) {
        return root_ = Erase(root_, key);
    }

    Node* Next(const int& key) {
        return Next(root_, key);
    }

    Node* Prev(const int& key) {
        return Prev(root_, key);
    }

    Node* Get(const int& key) {
        return Get(root_, key);
    }
};

int GetRandProirity(std::vector<int>& numbers) {
    int idx = rand() % numbers.size();
    int res = numbers[idx];
    std::swap(numbers[idx], numbers.back());
    numbers.pop_back();
    return idx;
}

int main() {
    const int max_elements = 100000;
    std::vector<int> numbers;
    for (int i = 0; i < max_elements; ++i) {
        numbers.push_back(i);
    }
    std::string operation;
    int number;
    Treap treap;
    while (std::cin >> operation && std::cin >> number) {
//        std::cout << "doing " << operation << ' ' <<  number << '\n';
        if ("insert" == operation) {
            treap.Insert(number, GetRandProirity(numbers));
        } else if ("delete" == operation) {
            treap.Erase(number);
        } else if ("exists" == operation) {
            std::cout << (treap.Find(number) ? "true" : "false") << '\n';
        } else if ("next" == operation) {
            auto node_ptr = treap.Next(number);
            if (node_ptr) {
                std::cout << node_ptr->key << '\n';
            } else {
                std::cout << "none\n";
            }
        } else if ("prev" == operation) {
            auto node_ptr = treap.Prev(number);
            if (node_ptr) {
                std::cout << node_ptr->key << '\n';
            } else {
                std::cout << "none\n";
            }
        } else if ("kth" == operation) {
            auto node_ptr = treap.Get(number-1);
            if (node_ptr) {
                std::cout << node_ptr->key << '\n';
            } else {
                std::cout << "none\n";
            }
        }
    }
    return 0;
}
