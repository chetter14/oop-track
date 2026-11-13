#ifndef DYN_ARRAY_H
#define DYN_ARRAY_H

template <typename T>
class DynArray {
 public:
  enum { MIN_CAPACITY = 16 };

  enum class MAKE_ARRAY_STATUS {
    OK = 0,            // последняя MakeArray() команда выполнилась успешно
    NOT_ENOUGH_MEMORY  // не удалось релоцировать массив
  };

  enum class APPEND_STATUS {
    OK = 0,            // последняя Append() команда выполнилась успешно
    NOT_ENOUGH_MEMORY  // не удалось релоцировать массив в случае переполнения буфера
  };

  enum class INSERT_STATUS {
    OK = 0,         // последняя Insert() команда выполнилась успешно
    INVALID_INDEX,  // невалидное значение индекса вставки
    NOT_ENOUGH_MEMORY  // не удалось релоцировать массив в случае переполнения буфера
  };

  enum class REMOVE_STATUS {
    OK = 0,            // последняя Remove() команда выполнилась успешно
    INVALID_INDEX,     // невалидное значение индекса удаления
    NOT_ENOUGH_MEMORY  // не удалось релоцировать массив в случае сокращения буфера
  };

  enum class GET_ITEM_STATUS {
    OK = 0,  // успешно
    ERR      // ошибка
  };

 public:
  virtual ~DynArray() = default;

 public:
  // команды

  // предусловие: размер буфера не может быть меньше MIN_CAPACITY
  // постусловие: меняет размер массива array, копируя при необходимости текущие объекты,
  // ёмкость равна new_capacity, но не меньше MIN_CAPACITY,
  // если элементов больше новой ёмкости, лишние элементы с конца отбрасываются
  virtual void MakeArray(int new_capacity) = 0;

  // постусловие: добавляется новый элемент в конец массива,
  // если места для нового эл-та нет, то увеличиваем буфер в 2 раза
  virtual void Append(T item) = 0;

  // предусловие: индекс вставки i меньше либо равен рабочему размеру массива,
  // в таком случае добавление происходит в его хвост
  // постусловие: вставляется в i-ю позицию объект item,
  // сдвигая вперёд все последующие элементы,
  // если места для нового эл-та нет, то увеличиваем буфер в 2 раза
  virtual void Insert(T item, int i) = 0;

  // предусловие: индекс удаления i не больше рабочего размера массива
  // постусловие: удаляется объект из i-й позиции,
  // если новый размер составляет менее 50% вместимости буфера, то выполняется сжатие буфера,
  // уменьшение буфера происходит в полтора раза
  // (текущее значение размера буфера делится на 1.5 и результат приводится к целому типу),
  // при этом сохраняем минимальную ёмкость 16 элементов
  virtual void Remove(int i) = 0;

  // запросы

  // предусловие: индекс находится в рамках границ массива
  virtual T GetItem(int i) = 0;

  // запросы статусов
  virtual MAKE_ARRAY_STATUS get_make_array_status() = 0;
  virtual APPEND_STATUS get_append_status() = 0;
  virtual INSERT_STATUS get_insert_status() = 0;
  virtual REMOVE_STATUS get_remove_status() = 0;
  virtual GET_ITEM_STATUS get_get_item_status() = 0;
};

#endif  // DYN_ARRAY_H
