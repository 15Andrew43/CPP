#ifndef UNIQUE_PTR_H
#define UNIQUE_PTR_H

#include <utility>



#include <algorithm>

template <typename T>
class UniquePtr {
    T* ptr_;
public:
    UniquePtr() : ptr_(nullptr) {}
    explicit UniquePtr(T* ptr) : ptr_(ptr) {}
    ~UniquePtr() {
        delete ptr_;
    }
    UniquePtr(const UniquePtr&) = delete;
    UniquePtr&operator=(const UniquePtr&) = delete;
    UniquePtr(UniquePtr&& other) {
        ptr_ = other.ptr_;
        other.ptr_ = nullptr;
    }
    UniquePtr&operator=(UniquePtr&& other) {
        if (this == &other) {
            return *this;
        }
//        delete ptr_;
        ptr_ = other.ptr_;
        other.ptr_ = nullptr;
        return *this;
    }
    T* Release() {
        T* old_ptr = ptr_;
        ptr_ = nullptr;
        return old_ptr;
    }
    void Reset(T* new_ptr = nullptr) {
        ptr_ = new_ptr;
    }
    void Swap(UniquePtr<T>& other) {
        T* tmp = std::move(ptr_);
        ptr_ = std::move(other.ptr_);
        other.ptr_ = std::move(tmp);
    }
    T* Get() const {
        return ptr_;
    }
    T& operator*() const {
        return *ptr_;
    }
    T* operator->() const {
        return ptr_;
    }
    operator bool() const {
        if (ptr_) {
            return true;
        }
        return false;
    }
};

#endif // UNIQUE_PTR_H
