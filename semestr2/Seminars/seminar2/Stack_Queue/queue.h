#ifndef QUEUE_H
#define QUEUE_H

#include <cstddef> // size_t
#include "stack.h"

typedef int Type;


class Queue {
	Stack Left;
	Stack Right;
public:
	void Push(Type value);
	void Pop();
	Type& Front();
	Type Front() const;
	
	void Clear();
	bool Empty() const;
	size_t Size() const;
};

void Rehandling(Stack& Left, Stack& Right);

#endif