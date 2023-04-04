#include <iostream>

#include <utility>


template <class  T, size_t N> 
class Array {
    T buffer_[N];
public:
    T& operator[](size_t ind) {
        return buffer_[ind];
    }
    T operator[](size_t ind) const {
        return buffer_[ind];
    }

    T& Front() {
        return buffer_[0];
    }
    T Front() const {
        return buffer_[0];
    }

    T& Back() {
        return buffer_[N-1];
    }
    T Back() const {
        return buffer_[N-1];
    }

    T* Data() const {
        return buffer_; 
    }
    const T* Data() {
        return buffer_;
    }
    
    T* Begin() {
        return buffer_;
    }
    T* End() {
        return (buffer_ + N);
    }

    size_t Size() const {
        return N;
    }
    bool Empty() const {
        return N == 0;
    }

    void Fill(const T& value) {
        for (size_t i = 0; i < N; ++i) {
            buffer_[i] = value;
        }
    }
    
    void Swap(T& other) {
        std::swap(buffer_, other.buffer_);
    }

};

template<class T, size_t N>
bool operator==(Array<T, N>& lhs, Array<T, N>& rhs) {
    for (size_t i = 0; i < N; ++i) {
        if (lhs[i] != rhs[i]) {
            return false;
        }
    }
    return true;
}

template<class T, size_t N>
bool operator!=(Array<T, N>& lhs, Array<T, N>& rhs) {
    return !(lhs == rhs);
}

template<class T, size_t N>
bool operator<(Array<T, N>& lhs, Array<T, N>& rhs) {
    for (size_t i = 0; i < N; ++i) {
        if (lhs[i] >= rhs[i]) {
            return false;
        }
    }
    return true;
}

template<class T, size_t N>
bool operator>=(Array<T, N>& lhs, Array<T, N>& rhs) {
    return !(lhs < rhs);
}

template<class T, size_t N>
bool operator>(Array<T, N>& lhs, Array<T, N>& rhs) {
    return ( (lhs >= rhs) && lhs != rhs);
}

template<class T, size_t N>
bool operator<=(Array<T, N>& lhs, Array<T, N>& rhs) {
    return !(lhs > rhs);
}




template<class T>
bool BinarySearch(const T* left, const T* right, T key) {
    T* mid;
    while (left < right) {
        mid = left + (right - left) / 2;

        if (*mid == key){
            return true;
        }
		if (*mid > key){
            right = mid;
		} else {
            left = mid + 1;
		}
    }
    return false;
}

int main() {
    size_t N, K;
    const size_t size = 100000;
    std::cin >> N >> K;
    Array< long long int, size > a;
    Array< long long int, size > b;

    for (size_t i = 0; i < N; ++i) {
        std::cin >> a[i];
    }
    for (size_t i = 0; i < K; ++i) {
        std::cin >> b[i];
    }


    for (size_t i = 0; i < K; ++i) {
        if (BinarySearch<long long int>(a.Begin(), a.Begin() + N, b[i])) {
            std::cout << "YES\n";
        } else {
            std::cout << "NO\n";
        }
    }

    return 0;
}