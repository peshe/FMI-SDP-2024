#ifndef QUEUE_WITH_STACKS_HPP
#define QUEUE_WITH_STACKS_HPP

#include "../Седмица 03 - Стек/linked_stack.hpp"
#include "queue.hpp"

template <typename T>
class QueueWithStacks : public Queue<T> {
public:
  bool empty() const {
    return top.empty() && bottom.empty();
  }

  void enqueue(const T& element) {
    if (bottom.empty()) {
      bottom.push(element);
    } else {
      top.push(element);
    }
  }

  T dequeue() {
    T result = bottom.pop();
    
    if (bottom.empty()) {
      move_to_bottom();
    }

    return result;
  }

  const T& first() const {
    return bottom.peek();
  }

private:
  LinkedStack<T> bottom;
  LinkedStack<T> top;

  void move_to_bottom() {
    while (!top.empty()) {
      bottom.push(top.pop());
    }
  }
};

#endif