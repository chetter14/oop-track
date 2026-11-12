#ifndef TWO_WAY_LIST_H
#define TWO_WAY_LIST_H

#include "parent_list.h"

template <typename T>
class TwoWayList : public ParentList<T> {
 public:
  enum class LEFT_STATUS {
    OK = 0,        // последний left() выполнился успешно
    NO_PREV_NODES  // слева от курсора нет узлов (некуда перемещаться)
  };

 public:
  virtual ~TwoWayList() = default;

 public:
  // команды

  // предусловие: левее курсора есть элемент;
  // постусловие: курсор сдвинут на один узел влево
  virtual void left() = 0;

  // запросы статусов

  virtual LEFT_STATUS get_left_status() = 0;
};

#endif  // TWO_WAY_LIST_H
