#ifndef POWER_SET_H
#define POWER_SET_H

#include "hash_table.h"

template <typename T>
class PowerSet : public HashTable<T> {
 protected:
  // конструктор
  // постусловие: создано пустое множество
  PowerSet() : HashTable() {}

 public:
  virtual ~PowerSet() = default;

  // команды

  // запросы

  virtual PowerSet<T> Intersection(PowerSet<T> set2) = 0;

  virtual PowerSet<T> Union(PowerSet<T> set2) = 0;

  virtual PowerSet<T> Difference(PowerSet<T> set2) = 0;

  virtual bool IsSubset(PowerSet<T> set2) = 0;

  virtual bool Equals(PowerSet<T> set2) = 0;

  // запросы статусов (возможные значения статусов)
};

#endif