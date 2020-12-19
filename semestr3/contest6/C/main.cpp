#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <random>
#include <unordered_set>

uint64_t GetNextPow2(uint64_t n) {
    uint64_t cur_n = 1;
    while (cur_n < n) {
        cur_n *= 2;
    }
    return cur_n;
}

template <class KeyT, class ValueT, class PriorityT>
class Treap { // Tree + Heap, CartesianTree

    class Node {
    public:
        KeyT key;
        ValueT value;
        ValueT result;
//    int promise;
        PriorityT priority;

        Node* left = nullptr;
        Node* right = nullptr;
        Node* parent = nullptr;

        size_t size = 1;

        ~Node() {
            delete left;
            delete right;
        }
    };

    Node* root_ = nullptr;
    static const ValueT kNeutral = 0;

    static size_t Size(Node* node) {
        return node ? node->size : 0;
    }

    static ValueT Result(Node* node) {
//        return node ? node->result * node->promise : kNeutral; // neutral element for operation
        return node ? node->result : kNeutral; // neutral element for operation
    }

    static void UpdateNode(Node* node) {
        if (node) {
            node->size = 1 + Size(node->left) + Size(node->right);
//            node->result = operation(Result(node->left),
//                                     operation(node->value, Result(node->right)));
             node->result = Result(node->left) + Result(node->right) + node->value;
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

    static std::pair<Node*, Node*> Split(Node* node, const KeyT& key) { // key -> size_t idx
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

    static Node* Find(Node* node, const KeyT& key) {
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

    static std::pair<Node*, Node*> Insert(Node* root, const KeyT& key, const PriorityT& priority) {
        auto [less_tree, ge_tree] = Split(root, key);
        Node* new_node = new Node{key, key, key, priority};
        return {
                Merge(
                        Merge(less_tree, new_node), ge_tree
                )
                , new_node
        };
    }

    static Node* Erase(Node* root, const KeyT& key) {
        if (Find(root, key) == nullptr) {
            return root;
        }
        auto [less_tree, ge_tree] = Split(root, key);
        auto [equal_tree, greater_tree] = Split(ge_tree, key + 1); // key + 0:
        delete equal_tree;
        return Merge(less_tree, greater_tree);
    }

    static KeyT Next(Node*& root, const KeyT& key) {
        KeyT new_key = key + 1; // ??????????????????????????????????????????????????????
        auto [less_tree, ge_tree] = Split(root, new_key);
        auto cur_tree = ge_tree;
        while (cur_tree && cur_tree->left) {
            cur_tree = cur_tree->left;
        }
        root = Merge(less_tree, ge_tree);
        return (cur_tree ? cur_tree->key : -1);
    }

    static KeyT Prev(Node*& root, const KeyT& key) {
        KeyT new_key = key; // ???????????????????????????????????????????????????????????????
        auto [less_tree, ge_tree] = Split(root, new_key);
        auto cur_tree = less_tree;
        while (cur_tree && cur_tree->right) {
            cur_tree = cur_tree->right;
        }
        root = Merge(less_tree, ge_tree);
        return (cur_tree ? cur_tree->key : -1);
    }

    static KeyT Get(Node* node, const int& idx) {
        if (node == nullptr) {
            return -1;
        } else if (Size(node->left) == idx) {
            return node->key;
        } else if (Size(node->left) < idx) {
            return Get(node->right, idx - Size(node->left) - 1);
        } else {
            return Get(node->left, idx);
        }
    }

    template <class FwdIterator>
    static Node* BuildFromSorted(FwdIterator begin, FwdIterator end) {
        int cnt_elements = end - begin;
        int next_pow2 = GetNextPow2(cnt_elements);
        std::vector<Node*> treaps(next_pow2, nullptr);
        for (auto it = begin; it != end; ++it) {
            treaps[it - begin] = new Node{it->key, it->priority};
        }
        while (next_pow2 > 1) {
            for (int i = 0; i < next_pow2; i += 2) {
                treaps[i / 2] = Merge(treaps[i], treaps[i + 1]);
            }
            next_pow2 /= 2;
        }
        return treaps[0];
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
                Insert(it->key, it->priority);
            }
        }
    }
    ~Treap() {
        delete root_;
    }
    Treap(const Treap& other) {
        root_ = Copy(other.root_);
    }
    Treap(Treap&& other) {
        root_ = other.root_;
        other.root_ = nullptr;
    }
    Treap operator=(const Treap& other) {
        delete root_;
        root_ = Copy(other.root_);
        return *this;
    }

    size_t Size() const {
        return Size(root_);
    }
    ValueT Result() const {
        return Result(root_);
    }

    bool Find(const KeyT& key) const {
        return Find(root_, key);
    }

    std::pair<Node*, Node*> Insert(const KeyT& key, const PriorityT& priority) {
        auto nodes = Insert(root_, key, priority);
        root_ = nodes.first;
        return nodes;
    }

    void Erase(const KeyT& key) {
        root_ = Erase(root_, key);
    }

    KeyT Next(const KeyT& key) {
        return Next(root_, key);
    }

    KeyT Prev(const KeyT& key) {
        return Prev(root_, key);
    }

    KeyT Get(const KeyT& key) {
        return Get(root_, key);
    }

    ValueT RMQ(const KeyT& left_key, const KeyT& right_key) {
        auto [less_tree, ge_tree] = Split(root_, left_key);
        auto [left_to_right_tree, greater_tree] = Split(ge_tree, right_key + 1);
        ValueT answer = Result(left_to_right_tree);
        Merge(less_tree, Merge(left_to_right_tree, greater_tree));
        return answer;
    }
};

std::random_device rd;  //Will be used to obtain a seed for the random number engine
std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
std::uniform_int_distribution<> distrib(0, 1000000000);

uint64_t GetRandProirity(std::vector<uint64_t>& numbers) {
//    uint64_t idx = distrib(gen) % numbers.size();
//    int idx = rand() % numbers.size();
//    std::swap(numbers[idx], numbers.back());
//    numbers.pop_back();
    return distrib(gen);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    const uint64_t module = 1000000000;
// ========= for random =====================
    const uint64_t max_elements = 300001;
    std::vector<uint64_t> numbers;
    for (uint64_t i = 0; i < max_elements; ++i) {
        numbers.push_back(i);
    }
// ==========================================

    uint64_t cnt_operations;
    std::cin >> cnt_operations;
    Treap<uint64_t , uint64_t , uint64_t> treap;

    char operation;
    uint64_t key;
    uint64_t res_rmq = 0;
    std::unordered_set<uint64_t > set(max_elements);
    for (uint64_t i = 0; i < cnt_operations; ++i) {
        std::cin >> operation;
        if ('+' == operation) {
            std::cin >> key;
            uint64_t right_key = (key + res_rmq) % module;
//            if (!treap.Find(right_key)) {
            if (set.find(right_key) == set.end()) {
//                std::cout << "pep " << key + res_rmq << '\n';
                treap.Insert(right_key, GetRandProirity(numbers));
                set.insert(right_key);
            }
            res_rmq = 0;
        } else { // if ('?' == operation) {
            uint64_t left_key, right_key;
            std::cin >> left_key >> right_key;
            std::cout << (res_rmq = treap.RMQ(left_key, right_key)) << '\n';
        }
    }
    return 0;
}
