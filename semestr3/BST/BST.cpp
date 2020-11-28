template <class KeyT, class PriorityT>
class Treap {

	struct Node {
		KeyT key;
		PriorityT priority;
		Node* left;
		Node* right;
		Node* parent;

		~Node() {
			delete left;
			delete right;
		}
	};

	Node* root_;

	static void SetLeft(Node* node, Node* new_left) {
		if (node) {
			node->left = new_left;
		}
		if (new_left) {
			new_left->parent = node;
		}
	}
	static void SetRight(Node* node, Node* new_right) {
	} 

	static std::pair<Node*, Node*> Split(Node* node, const KeyT& key) {...}

	static Node* Merge(Node* left_root, Node* right_root) { // keys(left) < key(right)
		if (!left_root) {
			return right_root;
		}
		if (!right_root) {
			return left_root;
		}
		if (left_root->priority < right_root->priority) {
			SetLeft(right_root, Merge(left_root, right_root->left));
			return right_root;
		} else { // left-prioruty >= right->priority
			SetRight(left_root, Merge(left_root->right, right_root));
		}
	}

	static Node* Insert(Node* root, const KeyT& key, const PriorityT& priority) {
		...
	}

	static Node* Erase(Node* root, const KeyT& key) {
		auto [less_tree, ge_tree] = Split(root, key);
		auto [equal_tree, greater_tree] = Split(ge_tree, key + 1);
		delete equal_tree;
		return Merge(less_tree, greater_tree);
	}



public:

	template <class FwdIterator>
	Treap(FwdIterator begin, FwdIterator end) : root_(nullptr) {
		if (std::is_sorted(begin, end, [](const auto& x, const auto& y){
			return x->key < y->key;
		})) {
			root_ = BuildFromSorted(begin, end);
			return ;
		}
		for (auto it = begin; it != end; ++it) {
			root_ = Insert(it->key, it->priority);
		}
	}

	bool Find(const KeyT& key) const {
		return Find(root_, key);
	}
	bool Insert(const KeyT& key, const PriorityT& priority) {
		if (!Find(key)) {
			root_ = Insert(root_, key, priority);
			return true;
		}
		return false;
	}
	bool Erase(const KeyT& key, const PriorityT& priority) {
		if (Find(key)) {
			root_ = Insert(root_, key, priority);
			return true;
		}
		return false;
	}
};