#include <iostream>
#include <vector>

//map[int] -> std::string
//KeyT = int
//ValueT = std::string

template <class KeyT, class PriorityT, class ValueT>
class Node {
public:
    KeyT key;

    ValueT value;
//        ValueT result;
//        ValueT promise;

    PriorityT priority;
    Node<KeyT, PriorityT,  ValueT>* left;
    Node<KeyT, PriorityT,  ValueT>* right;
    Node<KeyT, PriorityT,  ValueT>* parent;

//        size_t size;

    ~Node<KeyT, PriorityT,  ValueT>() {
        delete left;
        delete right;
    }
};

template <class KeyT, class PriorityT, class ValueT, class OperationHeap = std::less<PriorityT>>
class Treap { // Tree + Heap, CartesianTree

    Node<KeyT, PriorityT,  ValueT>* root_;

//    static size_t Size(Node<KeyT, PriorityT,  ValueT>* node) {
//        return node ? node->size : 0;
//    }

//    static ValueT Result(Node<KeyT, PriorityT,  ValueT>* node) {
//        return node ? node->result * node->promise : kNeutral; // neutral element for operation
//    }

//    static void UpdateNode<KeyT, PriorityT,  ValueT>(Node<KeyT, PriorityT,  ValueT>* node) {
//        if (node) {
//            node->size = 1 + Size(node->left) + Size(node->right);
//            node->result = operation(Result(node->left),
//                                     operation(node->value, Result(node->right)));
//             node->result = Result(node->left) + Result(node->right) + node->value;
//        }
//    }

//    static void Push(Node<KeyT, PriorityT,  ValueT>* node) {
//        if (!node) {
//            return;
//        }
//        if (node->left) {
//            node->left->promise = node->left->promise * node->promise; // 1 - node->promise (xor)
//        }
//        if (node->right) {
//            node->right->promise = node->right->promise * node->promise;
//        }
//        node->value = node->value * node->promise; // if promise == 1 : swap(left, right)
//        node->result = node->result * node->promise;
//        node->promise = 1; // neutral elem
//    }

    static void SetLeft(Node<KeyT, PriorityT,  ValueT>* node, Node<KeyT, PriorityT,  ValueT>* new_left) {
//        Push(node);
        if (node) {
            node->left = new_left;
        }
        if (new_left) {
            new_left->parent = node;
        }
//        UpdateNode<KeyT, PriorityT,  ValueT>(node);
    }

    static void SetRight(Node<KeyT, PriorityT,  ValueT>* node, Node<KeyT, PriorityT,  ValueT>* new_right) {
//        Push(node);
        if (node) {
            node->right = new_right;
        }
        if (new_right) {
            new_right->parent = node;
        }
//        UpdateNode<KeyT, PriorityT,  ValueT>(node);
    }

    static std::pair<Node<KeyT, PriorityT,  ValueT>*, Node<KeyT, PriorityT,  ValueT>*> Split(Node<KeyT, PriorityT,  ValueT>* node, const KeyT& key) { // key -> size_t idx
//        Push(node);
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
            return {node, less_tree};
        }
    }

    static Node<KeyT, PriorityT,  ValueT>* Merge(Node<KeyT, PriorityT,  ValueT>* left_root, Node<KeyT, PriorityT,  ValueT>* right_root) { // keys(left_root) < keys(right_root)
        if (!left_root) {
            return right_root;
        }
        if (!right_root) {
            return left_root;
        }
        if (OperationHeap()(left_root->priority, right_root->priority)) { // was <
//            Push(right_root);
            SetLeft(right_root, Merge(left_root, right_root->left));
            return right_root;
        } else { // left_root->priority >= right_root->priority
//            Push(left_root);
            SetRight(left_root, Merge(left_root->right, right_root));
            return left_root;
        }
    }

    static Node<KeyT, PriorityT,  ValueT>* Find(Node<KeyT, PriorityT,  ValueT>* node, const KeyT& key) {
//        Push(node);
        if (!node) {
            return nullptr;
        }
        if (node->key < key) {
            return Find(node->left, key);
        } else if (node->key > key) {
            return Find(node->right, key);
        } else {
            return node;
        }
    }

    static Node<KeyT, PriorityT,  ValueT>* Insert(Node<KeyT, PriorityT,  ValueT>* root, const KeyT& key, const PriorityT& priority, const ValueT& value) {
        auto [less_tree, ge_tree] = Split(root, key);
        auto new_node = new Node<KeyT, PriorityT,  ValueT>;
        new_node->key = key;
        new_node->priority = priority;// ?????????????????    {}?
        new_node->value = value;
        return Merge(
                Merge(less_tree, new_node), ge_tree
                );
    }

//    static Node<KeyT, PriorityT,  ValueT>* Erase(Node<KeyT, PriorityT,  ValueT>* root, const KeyT& key) {
//        auto [less_tree, ge_tree] = Split(root, key);
//        auto [equal_tree, greater_tree] = Split(ge_tree, key + 1); // key + 0:
//        /*
//            1) key + 0 should be implemented as template function GetNext<T> returning minimal
//            possible value that is greater than key (for numeric types possible
//            implementation is "key + std::numeric_limits<T>::epsilon()")
//            2) Or create a function UpperBound which finds the upper bound of passed value
//            in the treap and use it as key + 0 (I think this solution to be better one)
//        */
//        delete equal_tree;
//        return Merge(less_tree, greater_tree);
//    }

//    template <class FwdIterator>
//    static Node<KeyT, PriorityT,  ValueT>* BuildFromSorted(FwdIterator begin, FwdIterator end) {
//        // TODO
//
//        // 1. MergeSort - Ok
//        // 2. Linear-time (last_added)
//    }

public:

    Treap() = default;

    template <class FwdIterator>
    Treap(FwdIterator begin, FwdIterator end) : root_(nullptr) {
//        if (std::is_sorted(begin, end, [](const auto& x, const auto& y) {
//            return x->key < y->key;
//        })) {
//            root_ = BuildFromSorted(begin, end);
//        } else {
            for (auto it = begin; it != end; ++it) {
                auto [key, priority] = *it;
                Insert(key, priority);
            }
//        }
    }

    // TODO: the rule of 5

    Node<KeyT, PriorityT,  ValueT>* Find(const KeyT& key) const {
        return Find(root_, key); // Push?
    }

    Node<KeyT, PriorityT,  ValueT>* Insert(const KeyT& key, const PriorityT& priority, const ValueT& value) {
        if (!Find(key)) {
            root_ = Insert(root_, key, priority, value);
            return root_;
        }
        return root_;
    }

//    bool Erase(const KeyT& key) {
//        if (Find(key)) {
//            root_ = Erase(root_, key, priority);
//            return true;
//        }
//        return false;
//    }

//    size_t Size() const {
//        return Size(root_);
//    }

};


int main() {
    int cnt_pairs;
    std::cin >> cnt_pairs;
    std::vector<Node<int, int,  int>*> nodes(cnt_pairs);

    Treap<int, int, int, std::greater<int>> treap;

    for (int i = 0; i < cnt_pairs; ++i) {
        int key, priority;
        std::cin >> key >> priority;
        nodes.push_back(treap.Insert(key, priority, i));
    }

    for (int i = 0; i < cnt_pairs; ++i) {
        auto node = nodes[i];
        std::cout << node->parent->value << ' ' << node->left->value << ' ' << node->right->value << '\n';
    }

    std::cout << "Hello, World!" << std::endl;
    return 0;
}