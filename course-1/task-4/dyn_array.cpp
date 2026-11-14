#include "dyn_array.h"
#include <new>
#include <utility>

// Добавил использование концептов, чтобы такие операции как
// "array[j] = std::move(array[j + 1])" и "array[count - 1] = T()"
// не выбрасивали исключений

template <typename T>
concept NothrowMoveAssignable = requires(T a, T b) {
  { a = std::move(b) } noexcept;
};

template <typename T>
concept NothrowDefaultConstructible = requires {
  { T() } noexcept;
};

template <typename T>
  requires NothrowMoveAssignable<T> && NothrowDefaultConstructible<T>
class DynArrayImpl : public DynArray<T> {
 private:
  using MAKE_ARRAY_STATUS = typename DynArray<T>::MAKE_ARRAY_STATUS;
  using APPEND_STATUS = typename DynArray<T>::APPEND_STATUS;
  using INSERT_STATUS = typename DynArray<T>::INSERT_STATUS;
  using REMOVE_STATUS = typename DynArray<T>::REMOVE_STATUS;
  using GET_ITEM_STATUS = typename DynArray<T>::GET_ITEM_STATUS;

  using DynArray<T>::MIN_CAPACITY;

 public:
  // постусловие: создан пустой массив ёмкостью MIN_CAPACITY
  DynArrayImpl() { MakeArray(MIN_CAPACITY); }

  // указываю явно, что копирование и перемещение запрещено
  // (а в принципе это стоило бы реализовать)
  DynArrayImpl(const DynArrayImpl& other) = delete;
  DynArrayImpl(DynArrayImpl&& other) = delete;

  DynArrayImpl& operator=(const DynArrayImpl& other) = delete;
  DynArrayImpl& operator=(DynArrayImpl&& other) = delete;

  ~DynArrayImpl() override { delete[] array; }

 public:
  void MakeArray(int new_capacity) override {
    if (new_capacity < MIN_CAPACITY) {
      new_capacity = MIN_CAPACITY;
    }

    make_array_status = Reallocate(new_capacity)
                            ? MAKE_ARRAY_STATUS::OK
                            : MAKE_ARRAY_STATUS::NOT_ENOUGH_MEMORY;
  }

  void Append(T item) override {
    append_status = InsertAt(std::move(item), count)
                        ? APPEND_STATUS::OK
                        : APPEND_STATUS::NOT_ENOUGH_MEMORY;
  }

  void Insert(T item, int i) override {
    if (i < 0 || i > count) {
      insert_status = INSERT_STATUS::INVALID_INDEX;
      return;
    }

    insert_status = InsertAt(std::move(item), i)
                        ? INSERT_STATUS::OK
                        : INSERT_STATUS::NOT_ENOUGH_MEMORY;
  }

  void Remove(int i) override {
    if (i < 0 || i >= count) {
      remove_status = REMOVE_STATUS::INVALID_INDEX;
      return;
    }

    /* Сжатие требуется, если после удаления буфер заполнен менее чем на 50%.
       Сжимаем до удаления: если памяти не хватит, массив останется прежним. */
    if ((count - 1) * 2 < capacity && capacity > MIN_CAPACITY) {
      int new_capacity = static_cast<int>(capacity / 1.5);
      if (new_capacity < MIN_CAPACITY) {
        new_capacity = MIN_CAPACITY;
      }

      if (!Reallocate(new_capacity)) {
        remove_status = REMOVE_STATUS::NOT_ENOUGH_MEMORY;
        return;
      }
    }

    for (int j = i; j < count - 1; ++j) {
      array[j] = std::move(array[j + 1]);
    }
    array[count - 1] = T();  // освобождаем ресурсы, которыми владел элемент
    --count;

    remove_status = REMOVE_STATUS::OK;
  }

  T GetItem(int i) override {
    if (i < 0 || i >= count) {
      get_item_status = GET_ITEM_STATUS::ERR;
      return T();
    }

    get_item_status = GET_ITEM_STATUS::OK;
    return array[i];
  }

  MAKE_ARRAY_STATUS get_make_array_status() override {
    return make_array_status;
  }
  APPEND_STATUS get_append_status() override { return append_status; }
  INSERT_STATUS get_insert_status() override { return insert_status; }
  REMOVE_STATUS get_remove_status() override { return remove_status; }
  GET_ITEM_STATUS get_get_item_status() override { return get_item_status; }

 private:
  bool InsertAt(T item, int i) {
    if (count == capacity) {
      int new_capacity = capacity * 2;
      if (new_capacity < MIN_CAPACITY) {
        new_capacity = MIN_CAPACITY;
      }

      if (!Reallocate(new_capacity)) {
        return false;
      }
    }

    for (int j = count; j > i; --j) {
      array[j] = std::move(array[j - 1]);
    }
    array[i] = std::move(item);
    ++count;

    return true;
  }

  // буфер заменяется новой ёмкостью new_capacity,
  // в него перенесены первые min(count, new_capacity) элементов;
  // возвращает false, если памяти не хватило (массив не изменён)
  bool Reallocate(int new_capacity) {
    T* new_array = new (std::nothrow) T[new_capacity];
    if (new_array == nullptr) {
      return false;
    }

    const int new_count = count < new_capacity ? count : new_capacity;
    for (int i = 0; i < new_count; ++i) {
      new_array[i] = std::move(array[i]);
    }

    delete[] array;
    array = new_array;
    count = new_count;
    capacity = new_capacity;

    return true;
  }

 private:
  int count = 0;       // количество элементов в массиве
  int capacity = 0;    // размер буфера
  T* array = nullptr;  // буфер

  // у статусов нет значения "команда ещё не вызывалась", поэтому начинаем с OK
  MAKE_ARRAY_STATUS make_array_status = MAKE_ARRAY_STATUS::OK;
  APPEND_STATUS append_status = APPEND_STATUS::OK;
  INSERT_STATUS insert_status = INSERT_STATUS::OK;
  REMOVE_STATUS remove_status = REMOVE_STATUS::OK;
  GET_ITEM_STATUS get_item_status = GET_ITEM_STATUS::OK;
};
