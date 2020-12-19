/*
 Вася занимается анализом данных. В этот раз ему по выборке надо понять, какому классу распределений может принадлежать выборка. Одним из графических методов такого анализа является построение гистограммы распределения.

Для построения графика такого вида нужно знать, сколько раз какой элемент встречался в выборке.

Формат ввода
В первой строке идет число N (1 ≤ N ≤ 105) — размер выборки. На следующей строке идет N целых чисел через пробел, не превышающих по модулю 109 — сама выборка.

Формат вывода
Выведите K (число различных элементов в выборке) пар чисел по одной на каждой строке. Первое число в паре — элемент выборки, второе — количество раз, сколько оно встретилось. Пары при выводе должны быть отсортированы по первому элементу (смотри пример).

Пример
Ввод	Вывод
6
5 2 3 1 4 2

 
1 1
2 2
3 1
4 1
5 1
Примечания
Задачу необходимо решать с помощью собственного ассоциативного контейнера.
 */

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

struct Bucket {
  int val_;
  size_t count_;
  bool is_free_;
  bool deleted_;

  Bucket() : val_(0), count_(0), is_free_(true), deleted_(false) {}

  explicit Bucket(int item)
      : val_(item), count_(0), is_free_(false), deleted_(false) {}

  Bucket(Bucket&& other) noexcept = default;

  Bucket(const Bucket& other) = default;

  Bucket& operator=(const Bucket& other) = default;

  Bucket& operator=(Bucket&& other) noexcept = default;

  ~Bucket() = default;
};

class HashMap {
 public:
  explicit HashMap(int size = 8) : non_empty_(0), map_(size) {}

  HashMap(const HashMap& other) = default;

  HashMap(HashMap&& other) noexcept = default;

  HashMap& operator=(const HashMap& other) = default;

  HashMap& operator=(HashMap&& other) noexcept = default;

  ~HashMap() = default;

  long double GetLoadFactor() const {
    return static_cast<long double>(non_empty_) /
           static_cast<long double>(map_.size());
  }

  void Rehash() {
    size_t new_size = map_.size() * 2;
    std::vector<Bucket> tmp = std::move(map_);
    map_ = std::vector<Bucket>(new_size);
    non_empty_ = 0;
    for (const auto& item : tmp) {
      if (!item.is_free_ && !item.deleted_) {
        Add(item);
      }
    }
  }

  size_t Add(const Bucket& item) {
    size_t h1 = hash1(item.val_);
    size_t h2 = hash2(item.val_);

    for (size_t i = 0; i < map_.size(); ++i) {
      if (map_[h1].is_free_ || map_[h1].deleted_) {
        map_[h1] = item;
        ++non_empty_;
        break;
      } else if (map_[h1].val_ == item.val_) {
        return h1;
      }

      h1 = (h1 + h2) % map_.size();
    }

    if (GetLoadFactor() >= 0.75) {
      Rehash();
    }
    return Search(item);
  }

  size_t Search(const Bucket& item) {
    size_t h1 = hash1(item.val_);
    size_t h2 = hash2(item.val_);

    for (size_t i = 0; i < map_.size(); ++i) {
      if (map_[h1].is_free_) {
        return map_.size();
      } else if (map_[h1].val_ == item.val_) {
        if (!map_[h1].deleted_) {
          return h1;
        }
      }
      h1 = (h1 + h2) % map_.size();
    }
    return map_.size();
  }

  Bucket& operator[](const Bucket& item) {
    auto idx = Add(item);
    return map_[idx];
  }

  void Print() const {
    for (const auto& item : map_) {
      std::cout << item.val_ << ' ' << item.count_ << '\n';
    }
  }

  size_t Size() const { return map_.size(); }

 protected:
  size_t non_empty_;
  std::vector<Bucket> map_;

 private:
  size_t hash1(int val) const {
    uint32_t val2 = val;/*
    val2 = ((val2 >> 16) ^ val2) * 0x119de1f3;
    val2 = ((val2 >> 16) ^ val2) * 0x119de1f3;
    val2 = (val2 >> 16) ^ val2;*/
    return val2 % Size();
  }

  size_t hash2(int val) const {
    uint32_t val2 = val;
    size_t ans = val2 % (Size() - 1);
    return ((ans % 2 == 0) ? ans + 1 : ans);
  }
};

int main() {
  int N = 0;
  std::cin >> N;
  HashMap map(N);
  std::vector<std::pair<int, size_t>> answer;

  for (int i = 0; i < N; ++i) {
    int item = 0;
    std::cin >> item;
    if (map.Search(Bucket(item)) == map.Size()) {
      answer.emplace_back(item, 0);
    }
    ++map[Bucket(item)].count_;
  }

  for (auto& pair : answer) {
    pair.second = map[Bucket(pair.first)].count_;
  }

  std::sort(
      answer.begin(), answer.end(),
      [](const std::pair<int, size_t>& lhs, const std::pair<int, size_t>& rhs) {
        return lhs.first < rhs.first;
      });

  for (const auto& pair : answer) {
    std::cout << pair.first << ' ' << pair.second << '\n';
  }

  return 0;
}