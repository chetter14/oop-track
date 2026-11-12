#ifndef PARENT_LIST_H
#define PARENT_LIST_H

template <typename T>
class ParentList {
 public:
  virtual ~ParentList() = default;

 public:
  // команды

  // предусловие: список не пуст;
  // постусловие: курсор установлен на первый узел в списке
  virtual void head() = 0;

  // предусловие: список не пуст;
  // постусловие: курсор установлен на последний узел в списке
  virtual void tail() = 0;

  // предусловие: правее курсора есть элемент;
  // постусловие: курсор сдвинут на один узел вправо
  virtual void right() = 0;

  // предусловие: список не пуст;
  // постусловие: следом за текущим узлом добавлен
  // новый узел с заданным значением
  virtual void put_right(T value) = 0;

  // предусловие: список не пуст;
  // постусловие: перед текущим узлом добавлен
  // новый узел с заданным значением
  virtual void put_left(T value) = 0;

  // предусловие: список пуст;
  // постусловие: в списке один узел
  virtual void add_to_empty(T value) = 0;

  // предусловие: список не пуст;
  // постусловие: текущий узел удалён,
  // курсор смещён к правому соседу, если он есть,
  // в противном случае курсор смещён к левому соседу,
  // если он есть
  virtual void remove() = 0;

  // постусловие: список очищен от всех элементов
  virtual void clear() = 0;

  // постусловие: новый узел добавлен в хвост списка
  virtual void add_tail(T value) = 0;

  // постусловие: в списке удалены все узлы с заданным значением
  virtual void remove_all(T value) = 0;

  // предусловие: список не пуст;
  // постусловие: значение текущего узла заменено на новое
  virtual void replace(T value) = 0;

  // постусловие: курсор установлен на следующий узел
  // с искомым значением, если такой узел найден
  virtual void find(T value) = 0;

  // запросы

  virtual T get() = 0;  // предусловие: список не пуст
  virtual bool is_head() = 0;
  virtual bool is_tail() = 0;
  virtual bool is_value() = 0;
  virtual int size() = 0;

  // запросы статусов (возможные значения статусов)

  virtual int get_head_status() = 0;          // успешно; список пуст
  virtual int get_tail_status() = 0;          // успешно; список пуст
  virtual int get_right_status() = 0;         // успешно; правее нету элемента
  virtual int get_put_right_status() = 0;     // успешно; список пуст
  virtual int get_put_left_status() = 0;      // успешно; список пуст
  virtual int get_add_to_empty_status() = 0;  // успешно
  virtual int get_remove_status() = 0;        // успешно; список пуст
  virtual int get_replace_status() = 0;       // успешно; список пуст
  virtual int get_find_status() = 0;          // следующий найден;
      // следующий не найден; список пуст
  virtual int get_get_status() = 0;  // успешно; список пуст
};

#endif  // PARENT_LIST_H
