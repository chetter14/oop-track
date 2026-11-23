#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <cstddef>

template <typename T>
class HashTable {
 protected:
  // конструктор
  // постусловие: создана пустая хэш-таблица
  explicit HashTable(std::size_t max_size) : max_size_(max_size) {}

  const std::size_t max_size_;

 public:
  // команды

  // предусловие: в хэш-таблице ещё есть свободное место
  // постусловие: элемент добавлен в хэш-таблицу
  virtual void put(T value) = 0;

  // постусловие: удалён элемент из хэш-таблицы
  virtual void remove(T value) = 0;

  // запросы

  // постусловие: значение найдено (или не найдено) в хэш-таблице
  virtual void find(T value) = 0;

  virtual int size() = 0;  // количество элементов в хэш-таблице

  // запросы статусов (возможные значения статусов)

  virtual int
  get_put_status() = 0;  // успешно; хэш-таблица уже макс размера; ошибка при разрешении коллизий
  virtual int
  get_find_status() = 0;  // элемент найден; элемента нет в хэш-таблице
};

#endif  // HASH_TABLE_H
