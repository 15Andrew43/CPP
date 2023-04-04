#ifndef OPTIONAL_H
#define OPTIONAL_H

class BadOptionalAccess; // implement

template <class T>
class Optional {
    bool has_value_;
    char object_[sizeof(T)]; // <- raw memory (not dynamic!) for object (char[sizeof(T)] or read about std::aligned_storage)

public:
     Optional() = default;

     Optional(const Optional& other) : has_value_(other.has_value_),  {

     }

    Optional(T value);

    Optional(Optional&& other) noexcept;

    Optional& operator=(Optional other) noexcept;

    ~Optional();

    const T* operator->() const noexcept;

    T* operator->() noexcept;

    const T& operator*() const noexcept;

    T& operator*() noexcept;

    explicit operator bool() const noexcept;

    bool HasValue() const noexcept;

    T& Value(); // throws BadOptional Access if HasValue() == false

    const T& Value() const; // throws BadOptional Access if HasValue() == false

    T ValueOr(T default_value) const;

    void Swap(Optional& other) noexcept;

    void Reset() noexcept; // destructs contained object if any

//    template <class... Args>
//    T& Emplace(Args&&... args);
};

// #define EMPLACE_IMPLEMENTED

#endif // OPTIONAL_H
