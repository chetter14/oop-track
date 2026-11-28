#ifndef POWER_SET_H
#define POWER_SET_H

#include "hash_table.h"

template <typename T>
class PowerSet : public HashTable<T> {
 protected:
  // конструктор
  // постусловие: создано пустое множество
  explicit PowerSet(std::size_t max_size) : HashTable(max_size) {}

 public:
  virtual ~PowerSet() = default;

  // команды

  // Все команды - put и remove - в родительском АТД HashTable

  // запросы

  // постусловие: возвращено пересечение текущего множества и set2
  virtual PowerSet<T> Intersection(PowerSet<T> set2) = 0;

  // постусловие: возвращено объединение текущего множества и set2
  virtual PowerSet<T> Union(PowerSet<T> set2) = 0;

  // постусловие: возвращена разница текущего множества и set2
  virtual PowerSet<T> Difference(PowerSet<T> set2) = 0;

  // постусловие: возвращает true, если set2 есть подмножество текущего множества, иначе false
  virtual bool IsSubset(PowerSet<T> set2) = 0;

  // постусловие: возвращает true, если set2 равно текущему множеству, иначе false
  virtual bool Equals(PowerSet<T> set2) = 0;

  // запросы статусов (возможные значения статусов)
};

#endif