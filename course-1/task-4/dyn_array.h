#ifndef DYN_ARRAY_H
#define DYN_ARRAY_H

template <typename T>
class DynArray {
 public:
  enum class MAKE_ARRAY_STATUS {
    OK = 0,  // успешно
    ERR      // ошибка
  };

  enum class APPEND_STATUS {
    OK = 0,  // успешно
    ERR      // ошибка
  };

  enum class INSERT_STATUS {
    OK = 0,  // успешно
    ERR      // ошибка
  };

  enum class REMOVE_STATUS {
    OK = 0,  // успешно
    ERR      // ошибка
  };

  enum class GET_ITEM_STATUS {
    OK = 0,  // успешно
    ERR      // ошибка
  };

 public:
  virtual ~DynArray() = default;

 public:
  // команды
  virtual void MakeArray(int new_capacity) = 0;

  virtual void Append(T item) = 0;

  virtual void Insert(T item, int i) = 0;

  virtual void Remove(int i) = 0;

  // запросы
  virtual T GetItem(int i) = 0;

  // запросы статусов
  virtual MAKE_ARRAY_STATUS get_make_array_status() = 0;
  virtual APPEND_STATUS get_append_status() = 0;
  virtual INSERT_STATUS get_insert_status() = 0;
  virtual REMOVE_STATUS get_remove_status() = 0;
  virtual GET_ITEM_STATUS get_get_item_status() = 0;
};

#endif  // DYN_ARRAY_H
