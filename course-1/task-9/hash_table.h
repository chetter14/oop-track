#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <cstddef>

template <typename T>
class HashTable {
 protected:
  explicit HashTable(std::size_t max_size) : max_size_(max_size) {}

 public:
  virtual ~HashTable() = default;

  // команды

  virtual void put(const T& value) = 0;

  virtual void remove(const T& value) = 0;

  // запросы

  virtual void find(const T& value) = 0;

  virtual int size() = 0;  // количество элементов в хэш-таблице

  // запросы статусов (возможные значения статусов)

  virtual int get_put_status() = 0;
  virtual int get_find_status() = 0;

 private:
  const std::size_t max_size_;
};

#endif  // HASH_TABLE_H
