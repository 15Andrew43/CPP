#include <iostream>

#include "queue.h"

#include <utility>

#include "exception.h"

void Rehandling(Stack& Left, Stack& Right) {
	while(Left.Size()) {
		Right.Push(Left.Top());
		Left.Pop();
	}
}

void Queue::Push(Type value) {
	Left.Push(value);
}

void Queue::Pop() {
	if (Size() == 0) {
		throw LogicError("Logic Error: you can't use Pop() in queue, because size = 0");
	}
	if (Right.Empty()) {
		Rehandling(Left, Right);
	}
	Right.Pop();
}

Type& Queue::Front() {
	if (Size() == 0) {
		throw LogicError("Logic Error: you can't use Front() in queue, because size = 0");
	}
	if (Right.Empty()) {
		Rehandling(Left, Right);
	}
	return Right.Top();
}

Type Queue::Front() const {
	if (Size() == 0) {
		throw LogicError("Logic Error: you can't use Front() in queue, because size = 0");
	}
	if (Right.Empty()) {
		Node* ptr = Left.head_;
		while (ptr -> prev) {
			ptr = ptr -> prev;
		}
		return ptr -> value_;
	}	
	return Right.Top();
}

void Queue::Clear() {
	Left.Clear();
	Right.Clear();
}
bool Queue::Empty() const {
	return Left.size_ + Right.size_== 0;
}
size_t Queue::Size() const {
	return Left.size_ + Right.size_;
}