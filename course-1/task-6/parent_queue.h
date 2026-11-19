#ifndef PARENT_QUEUE_H
#define PARENT_QUEUE_H

template <typename T>
class ParentQueue {
 protected:
  // конструктор
  // постусловие: создана пустая очередь
  ParentQueue() = default;

 public:
  virtual ~ParentQueue() = default;

  // команды

  // постусловие: элемент добавлен в хвост очереди
  virtual void add_tail(T item) = 0;

  // предусловие: очередь не пустая
  // постусловие: удалён элемент из головы очереди
  virtual void remove_front() = 0;

  // запросы

  // предусловие: очередь не пуста
  virtual T get_front() = 0;  // получить элемент из головы очереди;

  virtual int size() = 0;  // количество элементов в очереди

  // запросы статусов (возможные значения статусов)

  virtual int
  get_remove_front_status() = 0;           // успешно; в очереди нет элементов
  virtual int get_get_front_status() = 0;  // успешно; в очереди нет элементов
};

#endif  // PARENT_QUEUE_H
