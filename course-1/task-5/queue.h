#ifndef QUEUE_H
#define QUEUE_H

template <typename T>
class Queue {
 public:
  virtual ~Queue() = default;

  // команды

  // постусловие: элемент добавлен в хвост очереди
  virtual void enqueue(T item) = 0;

  // предусловие: очередь не пустая
  // постусловие: возвращается элемент из головы очереди, удаляя его
  virtual void dequeue() = 0;

  // запросы

  virtual T size() = 0;  // количество элементов в очереди

  // запросы статусов (возможные значения статусов)
  
  virtual int get_dequeue_status() = 0;  // успешно; в очереди нет элементов
};

#endif  // QUEUE_H
