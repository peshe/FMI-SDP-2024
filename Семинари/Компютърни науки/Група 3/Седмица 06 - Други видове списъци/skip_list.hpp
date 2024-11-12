#ifndef SKIP_LIST_HPP
#define SKIP_LIST_HPP

#include <cstddef>
#include <random>
#include <type_traits>
#include <vector>

template <typename T>
class SkipList {
public:
  /*
    The head is an auxiliary element to which the elements at each
    level are attached. Otherwise inserting the initial element and 
    removing the first element become too complex. 
  */
  SkipList() : current_level(0), head(new Node(T())) {}
  
  SkipList(const SkipList<T>& other) : current_level(0), head(new Node(T())) {
    /* 
      This approach does not copy the structure of the list. Think 
      how you can copy the structure from `other`.
    */
    for (const T& element : other) {
      insert(element);
    }
  }

  SkipList<T>& operator=(const SkipList& other) {
    SkipList<T> copy(other);
    swap(copy);

    return *this;
  }

  SkipList(SkipList&& other) : current_level(other.current_level), head(other.head) {
    other.head = nullptr;
    other.current_level = 0;
  }

  SkipList<T>& operator=(SkipList&& other) {
    SkipList<T> copy(std::move(other));
    swap(copy);

    return *this;
  }

  ~SkipList() {
    Node* current = head;
    while (current) {
      Node* next = current->forward[0];
      delete current;
      current = next;
    }
  }

  void insert(const T& data) {
    std::vector<Node*> previous(current_level + 1, nullptr);
    Node* current = head;
    
    /*
      Go from the highest level and traverse each level until a
      greater or equal element is found - then go to the lower level.
    */
    for (int i = current_level; i >= 0; --i) {
      while (current->forward[i] && current->forward[i]->data < data) {
        current = current->forward[i];
      }

      /* 
        Save which was the last smaller element on each level, so
        we can insert the element after it, if it is promoted to
        that level.
      */
      previous[i] = current;
    }

    // Get the level to which the element is promoted
    std::size_t new_level = generate_level();
    Node* new_element = new Node(data, new_level);


    if (new_level > current_level) {
      head->forward.resize(new_level + 1, nullptr);
      for (std::size_t i = current_level + 1; i <= new_level; ++i) {
        previous.push_back(current);
      }

      current_level = new_level;
    }

    /* 
      Insert the element at the correct position up to
      the level at which it is promoted.
    */
    for (std::size_t i = 0; i <= new_level; ++i) {
      if (previous[i]->forward.size() <= i) {
        previous[i]->forward.resize(i + 1, nullptr);
      } 
      
      new_element->forward[i] = previous[i]->forward[i];
      previous[i]->forward[i] = new_element;
    }
  }
  
  bool search(const T& data) {
    Node* current = head;

    /*
      Go from the highest level and traverse each level. If at
      some point an equal element is found, return true. Else if
      a greater element is found or the end is reached, go to the
      lower level.
    */
    for (int i = current_level; i >= 0; --i) {
      while (current->forward[i] && current->forward[i]->data < data) {
        current = current->forward[i];
      }

      if (current->forward[i] && current->forward[i]->data == data) {
        return true;
      }
    }

    return false;
  }

  void remove(const T& data) {
    std::vector<Node*> previous(current_level + 1, nullptr);
    Node* current = head;
    
    /*
      Go from the highest level and traverse each level until a
      greater or equal element is found - then go to the lower level.
    */
    for (int i = current_level; i >= 0; --i) {
      while (current->forward[i] && current->forward[i]->data < data) {
        current = current->forward[i];
      }

      previous[i] = current;
    }

    current = current->forward[0];

    if (current && current->data == data) {
      /*
        Traverse the levels again and point the elements
        before the current to point at the element after
        the current.
      */
      for (int i = 0; i <= current_level; i++) {
        if (previous[i]->forward[i] != current) {
          break;
        }

        previous[i]->forward[i] = current->forward[i];
      }

      delete current;

      // Reduce the current level if there are empty levels
      while (current_level > 0 && head->forward[current_level] == nullptr) {
        current_level--;
      }
    }
  }

private:
  struct Node {
    T data;
    std::vector<Node*> forward;

    Node(const T& data, std::size_t level = 0) : data(data), forward(level + 1, nullptr) {}
  };

public:
  class Iterator {
  public:
    Iterator(Node* node) : current(node) {}

    int operator*() const {
      return current->data;
    }

    Iterator& operator++() {
      if (current) {
        current = current->forward[0];
      }
      return *this;
    }

    bool operator!=(const Iterator& other) const {
      return current != other.current;
    }
    
  private:
    Node* current;
  };

  Iterator begin() const {
    return Iterator(head->forward[0]);
  }

  Iterator end() const {
    return Iterator(nullptr);
  }
 
private:
  static constexpr double PROBABILITY = 0.5;

  std::size_t current_level;
  Node* head;
  std::random_device rd;

  std::size_t generate_level() {
    std::size_t level = 0;

    // This is the C++ way of generating random values
    std::mt19937 generator(rd());
    std::uniform_real_distribution<double> promote_distribution(0.0, 1.0);

    while (promote_distribution(generator) < PROBABILITY) {
      ++level;
    }

    return level;
  }

  void swap(SkipList& other) {
    std::swap(current_level, other.current_level);
    std::swap(head, other.head);
    // random_device can't be swapped, but this is not a problem
  }
};

#endif