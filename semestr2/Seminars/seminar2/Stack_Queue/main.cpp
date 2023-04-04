#include <iostream>

#include "queue.h"

#include "exception.h"

int main() {
/*
	Stack stack;
	stack.Push(1543);
	stack.Push(179);
	stack.Push(57);

	std::cout << (bool)stack.Empty() << "\n";

	std::cout << stack.Size() << "\n";

	stack.Clear();

	std::cout << (bool)stack.Empty() << "\n";

	Stack s1;
	s1.Push(1);
	s1.Push(2);
	s1.Push(3);
	s1.Push(12);
	Stack s2;
	s2 = s1;
	std::cout << s2.Size() << '\n';
	std::cout << s2.Top() << '\n';
	s2.Pop();
	std::cout << s2.Top() << '\n';
	s2.Top() = 1534;
	std::cout << s2.Top() << '\n';

	std::cout << "=====================================================\n";

	Queue q;
	q.Push(1);
	q.Push(2);
	q.Push(3);
	std::cout << q.Front() << '\n';
	q.Pop();
	std::cout << q.Front() << '\n';
	std::cout << q.Size() << '\n';
	q.Push(4);
	std::cout << q.Size() << '\n';
	std::cout << q.Front() << '\n';
	q.Clear();
	std::cout << q.Empty() << '\n';

	q.Push(11);
	q.Push(12);
	q.Push(13);
	std::cout << q.Size() << '\n';
	q.Front() = 1000;
	std::cout << q.Front() << '\n';
	q.Pop();
	std::cout << q.Front() << '\n';
	q.Pop();
	std::cout << q.Front() << '\n';
	q.Push(1234567);
	std::cout << q.Front() << '\n';
	q.Pop();
	std::cout << q.Front() << '\n';
	*/
	Stack stack;
	stack.Push(1543);
	stack.Push(179);
	stack.Push(57);

	for (int i = 0; i < 4; ++i) {
		try {
			std::cout << stack.Top() << '\n';
			stack.Pop();
		} catch (Exception& ex) {
			std::cout << ex.what() << '\n';
		}
	}
	std::cout << "---------------------------------------------------\n";
	Queue queue;
	queue.Push(1);
	queue.Push(2);
	queue.Push(3);

	for (int i = 0; i < 4; ++i) {
		try {
			std::cout << queue.Front() << '\n';
			queue.Pop();
		} catch (Exception& ex) {
			std::cout << ex.what() << '\n';
		}
	}
}