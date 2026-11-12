#include "dyn_array.h"
#include <algorithm>
#include <cstddef>

template <typename T>
class DynArrayImpl : public DynArray<T> {
 public:
  DynArrayImpl() { MakeArray(16); }

  // TO-DO: Add "rule-of-five"

 public:
  void MakeArray(int new_capacity) override {
    /* If there is no array */
    if (array == nullptr) {
      capacity = new_capacity;
      array = new T[capacity];
    }
    /* there is already some array */
    else {
      T* new_array = new T[new_capacity];

      for (int i = 0; i < std::min(count, size_t(new_capacity)); ++i) {
        new_array[i] = std::move(array[i]);
      }

      delete[] array;
      array = new_array;

      if (new_capacity < count)
        count = new_capacity;

      capacity = new_capacity;
    }
  }

  void Append(T item) override {}

  void Insert(T item, int i) override {}

  void Remove(int i) override {}

  T GetItem(int i) const override {}

 private:
  std::size_t count;
  std::size_t capacity;
  T* array;
};