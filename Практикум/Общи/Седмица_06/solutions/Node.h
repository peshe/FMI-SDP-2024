#ifndef _NODE_T_H_
#define _NODE_T_H_

#include <iostream>


template <typename T>
class Node {
public:
    T value;  // Стойност, съхранена във възела.
    Node* next; // Указател към евентуалния следващ елемент.
    Node* prev; // Указател към евентуалния предишен елемент.

    Node(T value = T(), Node* prev = nullptr, Node* next = nullptr)
      : value(value), prev(prev), next(next)
    { }

    ~Node() {
      // std::cout << "Deleting " << value << "; prev is " << prev;
      // std::cout << "; next is " << next << std::endl;

      if (prev != nullptr) {
        prev->next = nullptr;
        delete prev;
      }

      if (next != nullptr) {
        next->prev = nullptr;
        delete next;
      }
    }

    void addAtEnd(T value) {
      Node* last = this;
      while (last->next != nullptr) {
        last = last->next;
      }
      last->next = new Node(value, last);
    }

    void remove() {
      if (prev) {
        prev->next = next;
      }
      if (next) {
        next->prev = prev;
      }
      prev = nullptr;
      next = nullptr;
      delete this;
    }

    void printFromStart() const {
      const Node* current = this;
      while (current->prev != nullptr) {
        current = current->prev;
      }

      while (current->next != nullptr) {
        std::cout << current->value << " <-> ";
        current = current->next;
      }
      std::cout << current->value << std::endl;
    }
};

#endif // _NODE_T_H_
