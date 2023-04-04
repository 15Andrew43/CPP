#include <iostream>

#include <cstddef> // size_t

typedef int T;

struct Node {
	T value_;
	Node* prev;
};

class Stack {
	Node* head_ = nullptr;
	size_t size_ = 0;
public:
	void Push(T value);
	void Pop();
	T Top() const;
	T& Top();
	
	void Clear();
	bool Empty() const;
	size_t Size() const;

	Stack() = default;

	Stack& operator=(const Stack& other);

	~Stack();

	friend void rehandling(Stack& L, Stack& R);
};


class Queue {
	Stack L;
	Stack R;
	size_t size_ = 0;
public:
	void Push(T value);
	void Pop();
	T& Front1();
	T Front2();
	
	void Clear();
	bool Empty() const;
	size_t Size() const;

	Queue() = default;
	Queue(Stack& l, Stack& r);

	Queue& operator=(const Queue& other);

	~Queue();

	friend class Stack;
};

void rehandling(Stack& L, Stack& R);

bool f(T value1, T value2) {
	if (value1==9 && value2==0) {
		return true;
	} else if (value1==0 && value2==9) {
		return false;
	} else {
		return value1 < value2;
	}
}

int main() {
	Queue first;
	Queue second;
	for (int i = 0; i < 5; ++i) {
		int a;
		std::cin >> a;
		first.Push(a);
	}
	for (int i = 0; i < 5; ++i) {
		int a;
		std::cin >> a;
		second.Push(a);
	}
	int count = 0;


	while (!(first.Empty()) && !(second.Empty()) && count++ < 1000000) {
		if (f(first.Front2(), second.Front2())) {// first < second
			second.Push(first.Front2());
			second.Push(second.Front2());
			first.Pop();
			second.Pop();
		} else {
			first.Push(first.Front2());
			first.Push(second.Front2());
			first.Pop();
			second.Pop();
		}
	}


	if (first.Empty()) {
		std::cout << "second " << count; 
	} else if (second.Empty()) {
		std::cout << "first " << count; 
	} else {
		std::cout << "botva";
	}
}



// Stack
void Stack::Push(T value) {
    Node* t = new Node;
    t->value_ = value;
    t->prev = head_;
    head_ = t;
    ++size_;
}

void Stack::Pop() {
    Node* t = head_;
    head_ = head_->prev;
    delete t;
    --size_;
}

T Stack::Top() const {
    return head_->value_;
}

T& Stack::Top() {
    return head_->value_;
}

void Stack::Clear() {
    while (head_) {
        Node* t = head_;
        head_ = head_->prev;
        delete t;
    }
    size_ = 0;
}

bool Stack::Empty() const {
    return size_ == 0;
}
size_t Stack::Size() const {
    return size_;
}


Stack& Stack::operator=(const Stack& other) {
    Stack s;
    Node* ptr = other.head_;
    while (ptr) {
        s.Push(ptr->value_);
        ptr = ptr->prev;
    }
    ptr = s.head_;
    while (ptr) {
        Push(ptr->value_);
        ptr = ptr->prev;
    }
    delete ptr;
    return *this;
}

Stack::~Stack() {
    Clear();
    delete head_;
}


// Queue
void rehandling(Stack& L, Stack& R) {
	while(L.head_) {
		R.Push(L.head_->value_);
		L.Pop();
	}
}

void Queue::Push(T value) {
	L.Push(value);
	++size_;
}

void Queue::Pop() {
	if (R.Empty()) {
		rehandling(L, R);
	}
	R.Pop();
	--size_;
}

T& Queue::Front1() {
	if (R.Empty()) {
		rehandling(L, R);
	}
	return R.Top();
}

T Queue::Front2() {
	if (R.Empty()) {
		rehandling(L, R);
	}	
	return R.Top();
}


void Queue::Clear() {
	L.Clear();
	R.Clear();
	size_ = 0;
}
bool Queue::Empty() const {
	return size_ == 0;
}
size_t Queue::Size() const {
	return size_;
}

Queue::Queue(Stack& l, Stack& r) {
	L = l;
	R = r;
}

Queue& Queue::operator=(const Queue& other) {
	L = other.L;
	R = other.R;
	return *this;
}

Queue::~Queue() {
	L.Clear();
	R.Clear();
}
