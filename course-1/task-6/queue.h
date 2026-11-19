#ifndef QUEUE_H
#define QUEUE_H

#include "parent_queue.h"

template <typename T>
class Queue : public ParentQueue<T> {
 public:
  virtual ~Queue() = default;
};

#endif  // QUEUE_H
