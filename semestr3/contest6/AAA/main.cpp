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
    int value;

    int priority;
    Node* left = nullptr;
    Node* right = nullptr;
    Node* parent = nullptr;

    ~Node() {
        delete left;
        delete right;
    }
};

class Treap { // Tree + Heap, CartesianTree

    Node* root_ = nullptr;

    static void SetLeft(Node* node, Node* new_left) {
        if (node) {
            node->left = new_left;
        }
        if (new_left) {
            new_left->parent = node;
        }
    }

    static void SetRight(Node* node, Node* new_right) {
        if (node) {
            node->right = new_right;
        }
        if (new_right) {
            new_right->parent = node;
        }
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
        if (left_root->priority > right_root->priority) { // was <
            SetLeft(right_root, Merge(left_root, right_root->left));
            return right_root;
        } else { // left_root->priority >= right_root->priority
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

    static std::pair<Node*, Node*> Insert(Node* root, const int& key, const int& priority, const int& value) {
        auto [less_tree, ge_tree] = Split(root, key);
        Node* new_node = new Node;
        new_node->key = key;
        new_node->priority = priority;
        new_node->value = value;
        return {
                Merge(
                        Merge(less_tree, new_node), ge_tree
                )
                , new_node
        };
    }

    template <class FwdIterator>
    static Node* BuildFromSorted(FwdIterator begin, FwdIterator end) {

    }
public:
    Treap() = default;
    template <class FwdIterator>
    Treap(FwdIterator begin, FwdIterator end) {
        if (std::is_sorted(begin, end, [](const auto& x, const auto& y) {
            return x.key < y.key;
        })) {
            root_ = BuildFromSorted(begin, end);
        } else {
            for (auto it = begin; it != end; ++it) {
                Insert(it->key, it->priority, it->value);
            }
        }
    }

    Node* Find(const int& key) const {
        return Find(root_, key);
    }

    std::pair<Node*, Node*> Insert(const int& key, const int& priority, const int& value) {
        auto nodes = Insert(root_, key, priority, value);
        root_ = nodes.first;
        return nodes;
    }
};


int main() {
    int cnt_pairs;
    std::cin >> cnt_pairs;
    std::vector<Node> nodes(cnt_pairs);
    std::vector<int> keys(cnt_pairs);

    for (int i = 0; i < cnt_pairs; ++i) {
        int key, priority;
        std::cin >> key >> priority;
        Node node{key, i, priority, nullptr, nullptr, nullptr};
        nodes[i] = node;
        keys[i] = key;
    }

    std::sort(nodes.begin(), nodes.end(), [](const auto& x, const auto& y) {
        return x.key < y.key;
    });

    Treap treap(nodes.begin(), nodes.end());

    std::cout << "YES\n";
    for (int i = 0; i < cnt_pairs; ++i) {
        Node* node = treap.Find(keys[i]);
        std::cout << (node->parent ? node->parent->value+1 : 0)
                  << ' ' << (node->left ? node->left->value+1 : 0)
                  << ' ' << (node->right ? node->right->value+1 : 0) << '\n';
    }

    return 0;
}