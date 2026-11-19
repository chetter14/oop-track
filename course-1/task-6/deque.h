#ifndef DEQUE_H
#define DEQUE_H

#include "parent_queue.h"

template <typename T>
class Deque : public ParentQueue<T> {
 protected:
  // конструктор
  // постусловие: создана пустая двусторонняя очередь
  Deque() = default;

 public:
  virtual ~Deque() = default;

  // команды

  // постусловие: элемент добавлен в голову очереди
  virtual void add_front(T item) = 0;

  // предусловие: очередь не пустая
  // постусловие: удалён элемент из хвоста очереди
  virtual void remove_tail() = 0;

  // запросы

  // предусловие: очередь не пуста
  virtual T get_tail() = 0;  // получить элемент из хвоста очереди;

  // запросы статусов (возможные значения статусов)

  virtual int get_remove_tail_status() = 0;  // успешно; в очереди нет элементов
  virtual int get_get_tail_status() = 0;     // успешно; в очереди нет элементов
};

#endif  // DEQUE_H
