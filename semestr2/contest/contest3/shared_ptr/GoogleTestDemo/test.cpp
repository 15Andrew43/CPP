//
// Created by Андрей Боровец on 22.05.2020.
//

#include <gtest/gtest.h>

#include "../shared_ptr.h"

TEST(SharedPtr, Constructors) { // NOLINT
    SharedPtr<int> a;
    SharedPtr<int> b(nullptr);

    int* ptr = new int(35);
    SharedPtr<int> c(ptr);
    SharedPtr<int> d(c);


    ASSERT_EQ(a.Get(), nullptr);
    ASSERT_EQ(b.Get(), nullptr);
    ASSERT_EQ(c.Get(), ptr);
    ASSERT_EQ(d.Get(), ptr);

    SharedPtr<int> e(std::move(d));

    ASSERT_EQ(c.Get(), ptr);
    ASSERT_EQ(d.Get(), nullptr); // NOLINT check moved valid state
    ASSERT_EQ(e.Get(), ptr);
}

TEST(SharedPtr, Assignment) { // NOLINT
    SharedPtr<int> a;
    SharedPtr<int> b;

    auto ptr = new int(11);
    { // value assignment
    a = SharedPtr<int>(ptr);
    ASSERT_EQ(a.Get(), ptr);
    }

    ptr = new int(13);
    { // reassigning
    a = SharedPtr<int>(ptr);
    ASSERT_EQ(a.Get(), ptr);
    }

    { // copy assignment
    b = a;
    ASSERT_EQ(b.Get(), ptr);
    ASSERT_EQ(a.Get(), ptr);
    }

    { // copy is independent
    b = SharedPtr<int>(nullptr);
    ASSERT_EQ(a.Get(), ptr);
    ASSERT_EQ(b.Get(), nullptr);
    }

    { // move
    b = std::move(a);
    ASSERT_EQ(a.Get(), nullptr); // NOLINT check moved valid state
    ASSERT_EQ(b.Get(), ptr);
    }

    { // self-assignment
    b = b;
    ASSERT_EQ(b.Get(), ptr);
    }
}

TEST(SharedPtr, Swap) { // NOLINT
    SharedPtr<double> a;
    auto ptr = new double(15.43);
    SharedPtr<double> b(ptr);


    a.Swap(b);
    ASSERT_EQ(a.Get(), ptr);
    ASSERT_EQ(b.Get(), nullptr);

    a.Swap(a);
    ASSERT_EQ(a.Get(), ptr);
    }

    TEST(SharedPtr, UseCount) { // NOLINT
    std::cout << "PEP\n";
    SharedPtr<int> a;
    SharedPtr<int> b(new int(6));
    ASSERT_EQ(a.UseCount(), 0);
    ASSERT_EQ(b.UseCount(), 1);

    a = b;
    ASSERT_EQ(a.UseCount(), 2);
    ASSERT_EQ(b.UseCount(), 2);

    { // copy/move
    SharedPtr<int> c(a);
    ASSERT_EQ(a.UseCount(), 3);
    ASSERT_EQ(b.UseCount(), 3);
    ASSERT_EQ(c.UseCount(), 3);

    SharedPtr<int> d(std::move(c));
    ASSERT_EQ(a.UseCount(), 3);
    ASSERT_EQ(b.UseCount(), 3);
    ASSERT_EQ(c.UseCount(), 0); // NOLINT check moved valid state
    ASSERT_EQ(d.UseCount(), 3);
    }

    ASSERT_EQ(a.UseCount(), 2);
    ASSERT_EQ(b.UseCount(), 2);

    a = nullptr;
    ASSERT_EQ(a.UseCount(), 0);
    ASSERT_EQ(b.UseCount(), 1);
    }

    TEST(SharedPtr, Reset) { // NOLINT
    { // reset empty
    SharedPtr<int> a;
    a.Reset();
    ASSERT_EQ(a.UseCount(), 0);

    a.Reset(new int);
    ASSERT_EQ(a.UseCount(), 1);

    a.Reset();
    ASSERT_EQ(a.UseCount(), 0);
    }

    { // reset shared
    auto ptr1 = new int(5);
    SharedPtr<int> a(ptr1);
    SharedPtr<int> b = a;

    b.Reset();
    ASSERT_EQ(a.UseCount(), 1);
    ASSERT_EQ(a.Get(), ptr1);
    ASSERT_EQ(b.UseCount(), 0);

    b = a;
    auto ptr2 = new int(7);
    a.Reset(ptr2);
    ASSERT_EQ(a.UseCount(), 1);
    ASSERT_EQ(a.Get(), ptr2);
    ASSERT_EQ(b.UseCount(), 1);
    ASSERT_EQ(b.Get(), ptr1);
    }
}

TEST(SharedPtr, Operators) { // NOLINT
    { // operator*
        SharedPtr<int> a(new int(19));
        ASSERT_EQ(*a, 19);
    }

    { // operator->
        auto ptr = new int(11);
        SharedPtr<SharedPtr<int>> a(new SharedPtr<int>(ptr));
        ASSERT_EQ(a->UseCount(), 1);
        ASSERT_EQ(a->Get(), ptr);
    }

    { // operator bool
        SharedPtr<int> a;
        if (a) {
            ASSERT_TRUE(false);
        }

        SharedPtr<int> b = nullptr;
        if (b) {
            ASSERT_TRUE(false);
        }

        SharedPtr<int> c(new int(6));
        if (c) {
            ASSERT_TRUE(true);
        }
    }
}

TEST(WeakPtr, Constructors) { // NOLINT
    SharedPtr<int> shared(new int);
    WeakPtr<int> a;
    WeakPtr<int> b(a);
    WeakPtr<int> c(shared);
    WeakPtr<int> d(std::move(b));
}

TEST(WeakPtr, UseCountAndExpired) { // NOLINT
    { // Empty
        WeakPtr<int> a;
        WeakPtr<int> b(a);
        WeakPtr<int> c(std::move(b));

        ASSERT_EQ(a.UseCount(), 0);
        ASSERT_EQ(b.UseCount(), 0); // NOLINT check moved valid state
        ASSERT_EQ(c.UseCount(), 0);
        ASSERT_TRUE(a.Expired());
        ASSERT_TRUE(b.Expired());
        ASSERT_TRUE(c.Expired());
    }

    WeakPtr<int> a;
    {
        SharedPtr<int> ptr1(new int(1));
        auto ptr2 = ptr1;
        auto ptr3 = ptr2;
        a = ptr2;
        WeakPtr<int> b = ptr3;

        ASSERT_EQ(a.UseCount(), 3);
        ASSERT_EQ(b.UseCount(), 3);
        ASSERT_EQ(ptr1.UseCount(), 3);
        ASSERT_EQ(ptr2.UseCount(), 3);
        ASSERT_EQ(ptr3.UseCount(), 3);
        ASSERT_FALSE(a.Expired());
        ASSERT_FALSE(b.Expired());

        ptr1.Reset();
        ptr3.Reset();
        ASSERT_EQ(a.UseCount(), 1);
        ASSERT_EQ(b.UseCount(), 1);
        ASSERT_EQ(ptr1.UseCount(), 0);
        ASSERT_EQ(ptr2.UseCount(), 1);
        ASSERT_EQ(ptr3.UseCount(), 0);
        ASSERT_FALSE(a.Expired());
        ASSERT_FALSE(b.Expired());
    }
    ASSERT_TRUE(a.Expired());
}

TEST(WeakPtr, Reset) { // NOLINT
    WeakPtr<int> a;
    a.Reset();
    ASSERT_EQ(a.UseCount(), 0);
    ASSERT_TRUE(a.Expired());

    SharedPtr<int> ptr(new int);
    WeakPtr<int> b = ptr;
    a = b;
    b.Reset();
    ASSERT_EQ(ptr.UseCount(), 1);
    ASSERT_EQ(a.UseCount(), 1);
    ASSERT_EQ(b.UseCount(), 0);
    ASSERT_TRUE(b.Expired());
    ASSERT_FALSE(a.Expired());

    SharedPtr<int> empty_ptr;
    WeakPtr<int> c = empty_ptr;
    ASSERT_TRUE(c.Expired());

    empty_ptr.Reset(new int);
ASSERT_TRUE(c.Expired());
}

TEST(WeakPtr, Lock) { // NOLINT
    WeakPtr<int> a;
    a.Reset();
    ASSERT_EQ(a.Lock().Get(), nullptr);

    {
        auto p = new int;
        SharedPtr<int> ptr(p);
        WeakPtr<int> b = ptr;
        a = b;
        b.Reset();
        ASSERT_EQ(b.Lock().Get(), nullptr);
        ASSERT_EQ(a.Lock().Get(), p);
    }

    {
        auto p = new int;
        SharedPtr<int> ptr(p);
        WeakPtr<int> b = ptr;
        auto ptr_tmp = b.Lock();

        ptr.Reset();
        ASSERT_EQ(ptr_tmp.Get(), p);
        ASSERT_EQ(ptr_tmp.UseCount(), 1);
    }
}

TEST(SharedPtr, ConstructFromWeak) { // NOLINT
    auto* x = new SharedPtr<int>(new int(0));
    WeakPtr<int> y(*x);
    delete x;
    ASSERT_TRUE(y.Expired());
    ASSERT_THROW(SharedPtr<int> z(y), BadWeakPtr);
}

#ifdef MS_IMPLEMENTED

struct A {
    int x;
    double y;

    explicit A(int x = 0, double y = 0.0) : x(x), y(y) {
    }
};

TEST(SharedPtr, MakeSharedBase) { // NOLINT
    {
        SharedPtr<A> a = MakeShared<A>();
        ASSERT_EQ(a->x, 0);
        ASSERT_EQ(a->y, 0.0);
    }

    {
        SharedPtr<A> a = MakeShared<A>(11);
        ASSERT_EQ(a->x, 11);
        ASSERT_EQ(a->y, 0.0);
    }

    {
        SharedPtr<A> a = MakeShared<A>(12, 0.5);
        ASSERT_EQ(a->x, 12);
        ASSERT_EQ(a->y, 0.5);
    }
}

#endif
