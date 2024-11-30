#ifndef TREE_ITERATOR_HPP
#define TREE_ITERATOR_HPP

#include "../Седмица 03 - Стек/linked_stack.hpp"

template <typename NodeT, typename V> 
class Iterator {
public:
  Iterator(NodeT *node) { windstack(node); }

  V &operator*() { return stack.peek()->value; }

  const V &operator*() const { return stack.peek()->value; }

  Iterator &operator++() {
    NodeT *current = stack.pop();

    if (current->right) {
      windstack(current->right);
    }

    return *this;
  }

  bool operator!=(const Iterator &other) const {
    return !(stack.empty() && other.stack.empty() ||
             !stack.empty() && !other.stack.empty() &&
                 stack.peek() == other.stack.peek());
  }

private:
  LinkedStack<NodeT *> stack;

  void windstack(NodeT *node) {
    while (node) {
      stack.push(node);
      node = node->left;
    }
  }
};

#endif