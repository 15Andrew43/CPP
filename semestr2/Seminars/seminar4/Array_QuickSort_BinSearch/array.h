#ifndef ARRAY_H
#define ARRAY_H

#include <utility> // size_t

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
	for (int i = 0; i < N; ++i) {
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

#endif // ARRAY_H