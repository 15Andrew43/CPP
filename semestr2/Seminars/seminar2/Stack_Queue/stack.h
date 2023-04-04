#ifndef STACK_H
#define STACK_H

#include <cstddef> // size_t

typedef int Type;

struct Node {
	Type value_;
	Node* prev;
};

class Stack {
	Node* head_ = nullptr;
	size_t size_ = 0;
public:
	void Push(Type value);
	void Pop();
	Type Top() const;
	Type& Top();
	
	void Clear();
	bool Empty() const;
	size_t Size() const;

//	нарушено правило трех, то есть надо написать конструктор, но какой?
	Stack() = default;
	Stack(const Stack& other);

	Stack& operator=(const Stack& other);

	~Stack();

	friend class Queue;
};

void Copy(Node* ptr, Stack& stack);

#endif