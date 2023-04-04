#include <iostream>


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
T* RandomizedPartition(T* l, T* r) {
    T* i = rand() % (r-l+1) + l;
    std::swap(*i, *r);
    T x = *r;
    i = l-1;
    for (T* j = l; j < r; ++j) {
        if (*j <= x) {
            i++;
            std::swap(*i, *j);
        }
    }
    std::swap(*(i+1), *r);
    return i+1;
}

template<class T>
void QuickSort(T* l, T* r) {
    T* pirot;
    if (l < r) {
        pirot = RandomizedPartition<T>(l, r);
        QuickSort<T>(l, pirot-1);
        QuickSort<T>(pirot+1, r);
    }
}

// Если элементов много и все они равны, алгоритм работает квадратичное время
int main() {
    size_t N;
    std::cin >> N;
    const size_t size = 100000;
    Array<long long int, size> array;

    for (size_t i = 0; i < N; ++i) {
        std::cin >> array[i];
    }

    QuickSort<long long int>(array.Begin(), array.Begin()+N-1);

    for (size_t i = 0; i < N; ++i) {
        std::cout << array[i] << ' ';
    }
}