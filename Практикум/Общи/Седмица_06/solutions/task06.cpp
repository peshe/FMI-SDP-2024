#include <iostream>

template <typename T>
class Node {
public:
    T value;  // Стойност, съхранена във възела.
    // Указател към следващия елемент. Винаги го има, като при списък с един елемент сочи `this`.
    Node* next;

    Node(T value = T(), Node* next = nullptr)
      : value(value), next(next)
    {
        if (next == nullptr) {
            this->next = this;
        }
    }

    ~Node() {
      Node* current = next;
      while (current != nullptr && current != this) {
        Node* toDelete = current;
        current = current->next;
        toDelete->next = nullptr;
        // std::cout << "Deleting " << toDelete->value << "; next is " << current << std::endl;
        delete toDelete;
      }
    }

    void add(T value) {
      Node* last = next;
      while (last->next != this) {
        last = last->next;
      }
      last->next = new Node(value, this);
    }

    void print() const {
      const Node* current = this;
      while (current->next != this) {
        std::cout << current->value << " -> ";
        current = current->next;
      }
      std::cout << current->value << std::endl;
    }
};

template <typename T>
unsigned int countOf(const Node<T>* list, const T& value) {
    if (list == nullptr) return 0u;

    unsigned result = 0u;
    const Node<T>* current = list;

    do {
        if (current->value == value) ++result;
        current = current->next;
    } while (current != list);

    return result;
}

template <typename T>
Node<T>* removeAll(Node<T>* list, const T& value) {
    Node<T>* current = list;
    while (current->next != list) {
        if (current->next->value == value) {
            Node<T>* toDelete = current->next;
            current->next = toDelete->next;
            toDelete->next = nullptr;
            delete toDelete;
        } else {
            current = current->next;
        }
    }

    if (list->value == value) {
        current->next = list->next;
        list->next = nullptr;
        delete list;

        if (list == current) {
            return nullptr;
        }
        return current->next;
    }
    return list;
}

template <typename T>
void print(const Node<T>* list) {
    std::cout << "Printing list at address " << list << ':' << std::endl;
    if (list != nullptr) {
        list->print();
    }
}

int main () {
    auto* l = new Node<int>(1);
    l->add(2);
    l->add(3);
    l->add(1);
    l->add(1);
    l->print();
    std::cout << countOf(l, 1) << " times 1" << std::endl;

    l = removeAll(l, 1);
    print(l);

    l = removeAll(l, 2);
    print(l);

    l = removeAll(l, 3);
    print(l);

    return 0;
}
