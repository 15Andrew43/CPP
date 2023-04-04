#ifndef ARRAY_H
#define ARRAY_H

#include <utility> // size_t

template <class  T, size_t N> 
class Array {
	T buffer_[N];

public:
	// operaotor[], front, back, data, empty, size, fill, swap
	T& operator[](size_t ind) {
		return buffer_[ind];
	}
	T operator[](size_t ind) {
		return buffer_[ind];
	}

	T& Front() {
		return buffer_[0];
	}
	T Front() {
		return buffer_[0];
	}

	T& Back() {
		return buffer_[N-1];
	}
	T Back() {
		return buffer_[N-1];
	}

	T* Data() {
		return buffer_; 
	}
	const T* Data() {
		return buffer_;
	}
	
	bool Empty() const {
		return N == 0;
	}
	size_t Size() {
		return N;
	}

	void Swap(T& other) {
		std::swap(buffer_, oher.buffer_);
	}

};



#endif ARRAY_H