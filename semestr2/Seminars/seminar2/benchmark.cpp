#include <iostream>
#include <ctime>
#include <algorithm>

class TimeBenchmark {
    const char* info_;
    clock_t start_;

public:
    TimeBenchmark(const char* info) : info_(info), start_(clock()) {
    }

    ~TimeBenchmark() {
        clock_t finish = clock();
        std::cout << info_ << ": " << double(finish - start_) / CLOCKS_PER_SEC << '\n';
    }
};

int main() {
    const size_t kSize = 100'000'000;

    int* numbers = new int[kSize];
    int* sequential_indices = new int[kSize];
    int* random_indices = new int[kSize];

    for (size_t i = 0; i < kSize; ++i) {
        sequential_indices[i] = i;
        random_indices[i] = i;
    }

    std::random_shuffle(random_indices, random_indices + kSize);

    {
        TimeBenchmark benchmark("Sequential");

        for (size_t i = 0; i < kSize; ++i) {
            numbers[sequential_indices[i]] = 1;
        }
    }

    {
        TimeBenchmark benchmark("Random");

        for (size_t i = 0; i < kSize; ++i) {
            numbers[random_indices[i]] = 2;
        }
    }
    delete[] numbers;
    delete[] sequential_indices;
    delete[] random_indices;

    return 0;
}