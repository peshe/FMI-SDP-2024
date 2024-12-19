#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP

#include <utility>

template <typename T>
class LinkedList {
private:
  struct Node {
    T data;
    Node* next;

    Node(const T& data, Node* const next = nullptr) : data(data), next(next) {}
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

    const T& operator*() const {
      return current->data;
    }

  private:
    friend class LinkedList<T>;

    Node* current;
  };

  LinkedList(): first(nullptr), last(nullptr), size(0) {}
  LinkedList(const LinkedList& other) : first(nullptr), last(nullptr), size(other.size) {
    if (!other.empty()) {
      first = new Node(other.first->data);
      last = first;

      Node* next = other.first->next;

      while (next) {
        last->next = new Node(next->data);
        last = last->next;
        next = next->next;
      }
    }
  }
  LinkedList<T> operator=(const LinkedList& other) {
    LinkedList<T> copy(other);
    swap(copy);

    return *this;
  }
  LinkedList(LinkedList&& other) 
  : first(other.first), last(other.last), size(other.size) {
    other.first = nullptr;
    other.last = nullptr;
  }
  LinkedList<T>& operator=(LinkedList<T>&& other) {
    LinkedList<T> copy(std::move(other));
    swap(copy);

    return *this;
  }
  ~LinkedList() {
    while (!empty()) {
      remove_first();
    }
  }

  bool empty() const {
    return size == 0;
  }

  std::size_t get_size() const { return size; }

  void insert_first(const T& data) {
    if (empty()) {
      first = new Node(data);
      last = first;
    } else {
      first = new Node(data, first);
    }

    ++size;
  }

  void insert_last(const T& data) {
    if (empty()) {
      first = new Node(data);
      last = first;
    } else {
      last->next = new Node(data);
      last = last->next;
    }

    ++size;
  }

  void insert_after(const T& data, const Iterator& position) {
    if (position == Iterator(last)) {
      insert_last(data);
    } else {
      Node* new_element = new Node(data, position.current->next);
      position.current->next = new_element;
    }

    ++size;
  }

  void insert_before(const T& data, const Iterator& position) {
    if (position == Iterator(first)) {
      insert_first(data);
    } else {
      Iterator iter = previous(position);
      insert_after(data, iter);
    }

    ++size;
  }

  void remove_first() {
    if (size == 1) {
      delete first;
      first = nullptr;
      last = nullptr;
    } else {
      Node* next = first->next;
      delete first; 
      first = next;
    }

    --size;
  }

  void remove_last() {
    if (size == 1) {
      delete first;
      first = nullptr;
      last = nullptr;
    } else {
      Node* iter = first;

      while (iter->next->next) {
        iter = iter->next;
      }

      delete last;
      last = iter;
      last->next = nullptr;
    }

    --size;
  }

  void remove_at(const Iterator& position) {
    if (position == begin()) {
      remove_first();
    } else if (position == Iterator(last)) {
      remove_last();
    } else {
      Iterator iter = previous(position);

      iter.current->next = position.current->next;
      delete position.current;
    }

    --size;
  }

  Iterator begin() const {
    return Iterator(first);
  }

  Iterator end() const {
    return Iterator(nullptr);
  }

  void reverse() {
    Node* prev = nullptr, *iter = first, *next;

    std::swap(first, last);
    
    while (iter) {
      next = iter->next;
      iter->next = prev;
      prev = iter;
      iter = next;
    }
  }

private:
  Node* first, *last;
  std::size_t size;

  void swap(LinkedList& other) {
    std::swap(first, other.first);
    std::swap(last, other.last);
    std::swap(size, other.size);
  }

  Node* previous(Node* current) {
    Node* iter = first;

    while (iter->next != current) {
      iter = iter->next;
    }

    return iter;
  }

  Iterator previous(const Iterator& current) {
    Node* iter = first;

    while (Iterator(iter->next) != current) {
      iter = iter->next;
    }

    return Iterator(iter);
  }
};

#endif