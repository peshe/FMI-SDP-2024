#ifndef LINKED_STACK_HPP
#define LINKED_STACK_HPP

#include <utility>
#include "stack.hpp"

template <typename T>
class LinkedStack : public Stack<T> {
public:
  LinkedStack() : top(nullptr) {}
  LinkedStack(const LinkedStack& other) : top(nullptr) {
    if (other.top == nullptr) {
      return;
    }

    top = new Node(other.top->data);
    Node* current = top;

    Node* next = other.top->next;

    while (next) {
      current->next = new Node(next->data);
      current = current->next;
      next = next->next;
    }
  }

  LinkedStack<T>& operator=(const LinkedStack& other) {
    LinkedStack<T> copy(other);
    swap(copy);

    return *this;
  }

  LinkedStack(LinkedStack<T>&& other) : top(other.top) {
    other.top = nullptr;
  }

  LinkedStack<T>& operator=(LinkedStack&& other) {
    LinkedStack<T> copy(std::move(other)); 
    swap(copy);

    return *this;
  }

  ~LinkedStack() {
    while (!empty()) {
      pop();
    }
  }

  void push(const T& element) {
    top = new Node(element, top);
  }

  // unsafe if stack is empty
  T pop() {
    T data = top->data;
    Node *next = top->next;

    delete top;
    top = next;

    return data;
  }

  // unsafe if stack is empty
  const T& peek() const {
    return top->data;
  }

  bool empty() const {
    return top == nullptr;
  }

private:
  struct Node {
    T data;
    Node* next;

    Node(const T& data, Node* const next = nullptr) : data(data), next(next) {}
  };

  Node* top;

  void swap(LinkedStack& other) {
    std::swap(top, other.top);
  }
};

#endif