#ifndef SHARED_PTR_H
#define SHARED_PTR_H

#include <cstdio>
#include <algorithm>
#include <string>

class BadWeakPtr {
    std::string message_ = "BAD WEAK POINTER\n";
public:
    BadWeakPtr() = default;
    BadWeakPtr(const std::string message) : message_(message) {}
    std::string what() {
        return message_;
    }
};

struct Counter {
    size_t cnt_ = 0;
    size_t weak_cnt_ = 0;
};

template <class T>
class WeakPtr;

template <class T>
class SharedPtr {
    T* ptr_;
    Counter* counter_;
public:
    SharedPtr() : ptr_(nullptr) {}
    SharedPtr(T* ptr) : ptr_(ptr), counter_(new Counter{1, 0}) {}
    SharedPtr(const SharedPtr& other) : ptr_(other.ptr_), counter_(other.counter_) {
        ++counter_->cnt_;
    }
    SharedPtr&operator=(const SharedPtr& other) {
        ptr_ = other.ptr_;
        counter_ = other.counter_;
        ++counter_->cnt_;
        return *this;
    }
    SharedPtr(SharedPtr&& other) : ptr_(other.ptr_), counter_(other.counter_) {
        other.ptr_ = nullptr;
        other.counter_ = nullptr;
        std::cout << "bruh\n";
    }
    SharedPtr&operator=(SharedPtr&& other) {
        ptr_ = other.ptr_;
        counter_ = other.counter_;
        other.ptr_ = nullptr;
        other.counter_ = nullptr;
        ++counter_->cnt_;
        return *this;
    }
    SharedPtr(const WeakPtr<T>& other) {
        if (counter_->cnt_ == 0) {
            throw BadWeakPtr();
        }
        *this = other.Lock();
    }
    void Reset(T* ptr = nullptr) {
        if (ptr_ != ptr) {
            ~SharedPtr();
            ptr_ = ptr;
            if (ptr) {
                counter_ = new Counter{1, 0};
            }
        }
    }
    void Swap(SharedPtr& other) {
        if (this != &other) {
            SharedPtr tmp = std::move(other);
            std::cout << "--------------------------\n";
            other = std::move(*this);
            (*this) = std::move(tmp);
        }
    }
    T* Get() const {
        return ptr_;
    }
    size_t UseCount() const  {
        return counter_->cnt_;
    }
    T& operator*() const {
        return *ptr_;
    }
    T* operator->() {
        return ptr_;
    }
    operator bool() const {
        if (ptr_) {
            return true;
        }
        return false;
    }
    ~SharedPtr() {//                   weak ptr
        if (ptr_) {
            std::cout << counter_->cnt_ << '\n';
            std::cout << *ptr_ << '\n';
            if (counter_->cnt_ > 1) {
                std::cout << "+=+=+=+=+\n";
                --counter_->cnt_;
            } else {
                std::cout << "destructor[\n";
                delete ptr_;
                ptr_ = nullptr;
                if (counter_->cnt_ == 1)
                    --counter_->cnt_;
                else {
                    delete counter_;
                }
            }
        }
    }

    friend WeakPtr<T>;
};

template <class T>
class WeakPtr {
    T* ptr_;
    Counter* counter_;
public:
    WeakPtr() : ptr_(nullptr) {}
    WeakPtr(T* ptr) : ptr_(ptr), counter_(new Counter{0, 1}) {}
    WeakPtr(const WeakPtr& other) : ptr_(other.ptr_), counter_(other.counter_) {
        ++counter_->weak_cnt_;
    }
    WeakPtr&operator=(const WeakPtr& other) {
        ptr_ = other.ptr_;
        counter_ = other.counter_;
        ++counter_->weak_cnt_;
        return *this;
    }
    WeakPtr(WeakPtr&& other) : ptr_(std::move(other.ptr_)), counter_(std::move(other.counter_)) {}
    WeakPtr&operator=(WeakPtr&& other) {
        ptr_ = std::move(other.ptr_);
        counter_ = std::move(other.counter_);
        ++counter_->weak_cnt_;
        return *this;
    }
    WeakPtr(const SharedPtr<T>& ptr) : ptr_(ptr.ptr_), counter_(ptr.counter_) {
        ++counter_->weak_cnt_;
    }
    void Swap(WeakPtr& other) {
        WeakPtr tmp = std::move(other);
        other = std::move(*this);
        (*this) = std::move(tmp);
    }
    void Reset() {
    }
    size_t UseCount() const {
        return counter_->cnt_;
    }
    bool Expired() const {
        return counter_->cnt_ == 0;
    }
    SharedPtr<T> Lock() const {
        if (Expired()) {
            return nullptr;
        }
        return SharedPtr<T>(ptr_);
    }

};


//#define MS_IMPLEMENTED


#endif // SHARED_PTR_H
