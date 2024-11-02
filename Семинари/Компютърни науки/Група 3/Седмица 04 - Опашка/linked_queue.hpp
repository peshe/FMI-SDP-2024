#ifndef LINKED_QUEUE_HPP
#define LINKED_QUEUE_HPP

#include <utility>
#include "queue.hpp"

template <typename T> class LinkedQueue : public Queue<T> {
public:
  LinkedQueue() : front(nullptr), back(nullptr) {}
  LinkedQueue(const LinkedQueue &other) : front(nullptr), back(nullptr) {
    if (!other.empty()) {
      Node *first_element = new Node(other.first()), *next = other.front->next;
      front = first_element;
      back = first_element;

      while (next) {
        back->next = new Node(next->data);
        back = back->next;
        next = next->next;
      }
    }
  }
  LinkedQueue<T> &operator=(const LinkedQueue<T> &other) {
    LinkedQueue<T> copy(other);
    swap(copy);

    return *this;
  }
  LinkedQueue(LinkedQueue &&other) : front(other.front), back(other.back) {
    other.front = nullptr;
    other.back = nullptr;
  }
  LinkedQueue<T> &operator=(LinkedQueue &&other) {
    LinkedQueue<T> copy(std::move(other));
    swap(copy);

    return *this;
  }
  ~LinkedQueue() {
    while (!empty()) {
      dequeue();
    }
  }

  void enqueue(const T &element) {
    Node *new_element = new Node(element);

    if (empty()) {
      front = new_element;
      back = new_element;

      return;
    }

    back->next = new_element;
    back = back->next;
  }

  T dequeue() {
    if (front == back) {
      back = nullptr;
    }

    T data = front->data;
    Node *next = front->next;

    delete front;

    front = next;
    return data;
  }

  const T &first() const { return front->data; }

  bool empty() const { return front == nullptr; }

private:
  struct Node {
    T data;
    Node *next;

    Node(const T &data, Node *const next = nullptr) : data(data), next(next) {}
  };

  Node *front, *back;

  void swap(LinkedQueue<T> &other) {
    std::swap(front, other.front);
    std::swap(back, other.back);
  }
};

#endif