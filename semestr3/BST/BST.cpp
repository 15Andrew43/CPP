map[int] -> std::string
KeyT = int
ValueT = std::string

template <class KeyT, class PriorityT>
class Treap { // Tree + Heap, CartesianTree

    class Node {
    public:
        KeyT key;
        
        ValueT value;
        ValueT result;
        ValueT promise;

        PriorityT priority;
        Node* left;
        Node* right;
        Node* parent;

        size_t size;

        ~Node() {
            delete left;
            delete right;
        }
    };

    Node* root_;

    static size_t Size(Node* node) {
        return node ? node->size : 0;
    }

    static ValueT Result(Node* node) {
        return node ? node->result * node->promise : kNeutral; // neutral element for operation
    }

    static void UpdateNode(Node* node) {
        if (node) {
            node->size = 1 + Size(node->left) + Size(node->right);
            node->result = operation(Result(node->left),
                                     operation(node->value, Result(node->right)));
            // node->result = Result(node->left) + Result(node->right) + node->value;
        }
    }

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
        node->value = node->value * node->promise; // if promise == 1 : swap(left, right)
        node->result = node->result * node->promise;
        node->promise = 1; // neutral elem
    }

    static void SetLeft(Node* node, Node* new_left) {
        Push(node);
        if (node) {
            node->left = new_left;
        }
        if (new_left) {
            new_left->parent = node;
        }
        UpdateNode(node);
    }

    static void SetRight(Node* node, Node* new_right) {
        // TODO
    }

    static std::pair<Node*, Node*> Split(Node* node, const KeyT& key) { // key -> size_t idx
        // TODO
    }

    static Node* Merge(Node* left_root, Node* right_root) { // keys(left_root) < keys(right_root)
        if (!left_root) {
            return right_root;
        }
        if (!right_root) {
            return left_root;
        }
        if (left_root->priority < right_root->priority) {
            Push(right_root);
            SetLeft(right_root, Merge(left_root, right_root->left));
            return right_root;
        } else { // left_root->priority >= right_root->priority 
            Push(left_root);
            SetRight(left_root, Merge(left_root->right, right_root));
            return left_root;
        }
    }

    static Node* Find(Node* node, const KeyT& key) {
        // TODO
    }

    static Node* Insert(Node* root, const KeyT& key, const PriorityT& priority) {
        // TODO
    }

    static Node* Erase(Node* root, const KeyT& key) {
        auto [less_tree, ge_tree] = Split(root, key);
        auto [equal_tree, greater_tree] = Split(ge_tree, key + 1); // key + 0: 
        /*
            1) key + 0 should be implemented as template function GetNext<T> returning minimal
            possible value that is greater than key (for numeric types possible 
            implementation is "key + std::numeric_limits<T>::epsilon()")
            2) Or create a function UpperBound which finds the upper bound of passed value
            in the treap and use it as key + 0 (I think this solution to be better one)
        */
        delete equal_tree;
        return Merge(less_tree, greater_tree);
    }

    template <class FwdIterator>
    static Node* BuildFromSorted(FwdIterator begin, FwdIterator end) {
        // TODO

        // 1. MergeSort - Ok
        // 2. Linear-time (last_added)
    }

public:

    template <class FwdIterator>
    Treap(FwdIterator begin, FwdIterator end) : root_(nullptr) {
        if (std::is_sorted(begin, end, [](const auto& x, const auto& y) {
            return x->key < y->key;
        })) {

            root_ = BuildFromSorted(begin, end);
        } else {
            for (auto it = begin; it != end; ++it) {
                Insert(it->key, it->priority);
            }
        }
    }

    // TODO: the rule of 5

    bool Find(const KeyT& key) const {
        return Find(root_, key); // Push?
    }

    bool Insert(const KeyT& key, const ValueT& value, const PriorityT& priority) {
        if (!Find(key)) {
            root_ = Insert(root_, key, priority);
            return true;
        }
        return false;
    }

    bool Erase(const KeyT& key) {
        if (Find(key)) {
            root_ = Erase(root_, key, priority);
            return true;
        }
        return false;
    }

    size_t Size() const {
        return Size(root_);
    }

    ...
};
