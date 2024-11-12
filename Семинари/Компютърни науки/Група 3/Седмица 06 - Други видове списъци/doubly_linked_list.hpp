#ifndef DOUBLY_LINKED_LIST_HPP
#define DOUBLY_LINKED_LIST_HPP

#include <utility>

template <typename T>
class DoublyLinkedList {
public:
  DoublyLinkedList() : first(nullptr), last(nullptr), size(0) {}
  
  DoublyLinkedList(const DoublyLinkedList& other) : first(nullptr), last(nullptr), size(other.size) {
    if (!other.empty()) {
      first = new Node(other.first->data);
      last = first;

      Node* next = other.first->next;

      while (next) {
        last->next = new Node(next->data, last);
        last = last->next;
        next->next = next;
      }
    }
  }

  DoublyLinkedList<T>& operator=(const DoublyLinkedList<T>& other) {
    DoublyLinkedList<T> copy(other);
    swap(copy);

    return *this;
  }

  DoublyLinkedList(DoublyLinkedList&& other) : first(other.first), last(other.last), size(other.size) {
    other.first = nullptr;
    other.last = nullptr;
    other.size = 0;
  }

  DoublyLinkedList<T>& operator=(DoublyLinkedList&& other) {
    DoublyLinkedList<T> copy(std::move(other));
    swap(copy);

    return *this;
  }

  ~DoublyLinkedList() {
    while (!empty()) {
      remove_first();
    }
  }

  bool empty() const {
    return first == nullptr;
  }

  std::size_t get_size() const {
    return size;
  }

  void insert_last(const T& data) {
    if (empty()) {
      last = new Node(data);
      first = last;
    } else {
      last->next = new Node(data, last);
      last = last->next;
    }

    ++size;
  }

  void insert_first(const T& data) {
    if (empty()) {
      first = new Node(data);
      last = first;
    } else {
      first->prev = new Node(data, nullptr, first);
      first = first->prev;
    }

    ++size;
  }
  
  void remove_first() {
    if (first == last) {
      delete first;
      first = last = nullptr;
    } else {
      Node *next = first->next;
      next->prev = nullptr;
      delete first;
      first = next;
    }

    --size;
  }

  void remove_last() {
    if (first == last) {
      delete first;
      first = last = nullptr;
    } else {
      Node* prev = last->prev;
      prev->next = nullptr;
      delete last;
      last = prev;
    }

    --size;
  }

private:
  struct Node {
    T data;
    Node *prev, *next;

    Node(const T& data, Node* const prev = nullptr, Node* const next = nullptr)
      : data(data), prev(prev), next(next) {}
  };

public:
class Iterator {
  public:
    Iterator(Node* const current) : current(current) {}

    bool operator!=(const Iterator& other) const {
      return current != other.current;
    }

    bool operator==(const Iterator& other) const {
      return !(*this != other);
    }

    Iterator& operator++() {
      current = current->next;
      return *this;
    }

    Iterator& operator--() {
      current = current->prev;
      return *this;
    }

    const T& operator*() const {
      return current->data;
    }

  private:
    friend class DoublyLinkedList<T>;

    Node* current;
  };

  Iterator begin() const {
    return Iterator(first);
  }

  Iterator end() const {
    return Iterator(nullptr);
  }

  Iterator last_i() const {
    return Iterator(last);
  }

  void insert_before(const T& data, const Iterator& position) {
    if (position == begin()) {
      insert_first(data);
      return;
    }

    Node* prev = position.current->prev;
    position.current->prev = prev->next = new Node(data, prev, position.current);

    ++size;
  }

  bool is_palyndrome() const {
    Node *first_it = first, *last_it = last;
    while (first_it != last_it && first_it->prev != last_it && first_it->data == last_it->data) {
      first_it = first_it->next;
      last_it = last_it->prev;
    }

    return first_it == last_it || first_it->prev == last_it;
  }

private:
  Node *first, *last;
  std::size_t size;

  void swap(DoublyLinkedList& other) {
    std::swap(first, other.first);
    std::swap(last, other.last);
    std::swap(size, other.size);
  }
};

#endif