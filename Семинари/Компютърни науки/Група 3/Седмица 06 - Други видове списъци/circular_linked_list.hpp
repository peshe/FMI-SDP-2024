#ifndef CIRCULAR_LINKED_LIST_HPP
#define CIRCULAR_LINKED_LIST_HPP

#include <utility>

template <typename T>
class CircularLinkedList {
public:
  CircularLinkedList() : last(nullptr), size(0) {}

  CircularLinkedList(const CircularLinkedList& other) : last(nullptr), size(other.size) {
    if (!other.empty()) {
      insert_last(other.last->next->data);
      Node *next = other.last->next->next;

      while (next != other.last->next) {
        insert_last(next->data);
        next = next->next;
      }
    }
  }

  CircularLinkedList<T>& operator=(const CircularLinkedList& other) {
    CircularLinkedList<T> copy(other);
    swap(copy);

    return *this;
  }

  CircularLinkedList(CircularLinkedList&& other) : last(other.last), size(other.size) {
    other.last = nullptr;
    size = 0;
  }

  CircularLinkedList<T>& operator=(CircularLinkedList&& other) {
    CircularLinkedList<T> copy(std::move(other));
    swap(copy);

    return *this;
  }

  ~CircularLinkedList() {
    while (!empty()) {
      remove_first();
    }
  }

  bool empty() const {
    return last == nullptr;
  }

  std::size_t get_size() const {
    return size;
  }

  void insert_first(const T& data) {
    if (empty()) {
      last = new Node(data);
      last->next = last;
    } else {
      last->next = new Node(data, last->next);
    }

    ++size;
  }

  void insert_last(const T& data) {
    insert_first(data);
    last = last->next;
  }

  void remove_first() {
    if (last == last->next) {
      delete last;
      last = nullptr;
    } else {
      Node* next = last->next->next;
      delete last->next;
      last->next = next;
    }

    --size;
  }

  void remove_last() {
    if (last == last->next) {
      delete last;
      last = nullptr;
    } else {
      Node* first = last->next;
      
      while (first->next != last) {
        first = first->next;  
      }

      first->next = last->next;
      delete last;
      last = first;
    }

    --size;
  }

  void advance_first() {
    last = last->next;
  }

  const T& first() const {
    return last->next->data;
  }

private:
  struct Node {
    T data;
    Node* next;

    Node(const T& data, Node* const next = nullptr) : data(data), next(next) {} 
  };

  Node* last;
  std::size_t size;

  void swap(CircularLinkedList& other) {
    std::swap(last, other.last);
    std::swap(size, other.size);
  }
};

#endif