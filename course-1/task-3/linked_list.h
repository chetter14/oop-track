#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "parent_list.h"

template <typename T>
class LinkedList : public virtual ParentList<T> {
  // Никакого дополнительного функционала тут не нужно. Уже всё необходимое указано в ParentList.
 public:
  virtual ~LinkedList() = default;
};

#endif  // LINKED_LIST_H
