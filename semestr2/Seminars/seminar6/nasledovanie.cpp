#include <iostream>

using namespace std;

class A {
public:
    void f() {
        cout << "A::f()\n";
    }

    virtual void g() {
        cout << "A::g()\n";
    }
};

class B : public A {
public:
    void f() {
        cout << "B::f()\n";
    }

    virtual void g() {
        cout << "B::g()\n";
    }
    
    B() = default;
    B(const A&);// если хотим делать так: B b = a
};

/*
//Stack, StackMin : piblic Stack
void Push(Stack* stack) {
    stack -> Push(value);
}
// Push(&s)
// Push(&sm)
*/

int main() {
    B b;
    b.f();  // B::f
    b.g();  // B::g

    A a = b;    // A(const A& other) -- контруктор копирования
    a.f();  // A::f
    a.g();  // A::g

    A* a_ptr = &b; // указывает на В значит
    a_ptr ->f();    // A::f
    a_ptr->g();     // B::g     !!!!!!!!!не очевидно!!!!!!!!!

    A& a_ref = b;
    a_ref.f();      // A::f
    a_ref.g();      // B::g             также как с указателями тк это почти одно и то же

//    A aa;
//    B bb = aa; // CE, так как не прописали явно
//    B* b_ptr = &aa; // ce
//    B& b_ref = aa;  // ce
    std::cout << "Hello, World!" << std::endl;
    return 0;
}