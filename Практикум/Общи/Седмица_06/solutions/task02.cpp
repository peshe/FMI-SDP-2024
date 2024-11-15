#include "Node.h"

#include <iostream>


template <typename T>
void mirror(Node<T>* lst) {
    if (lst == nullptr) return;

    Node<T>* current = lst;
    while (current->next != nullptr) {
        current = current->next;
    }

    Node<T>* tail = current;
    do {
        tail->next = new Node<T>(current->value, tail);
        tail = tail->next;
        current = current->prev;
    } while (current != nullptr);
}

int main () {
    Node<int> l(1);
    l.addAtEnd(4);
    l.addAtEnd(5);
    l.printFromStart();

    mirror(&l);
    l.printFromStart();

    return 0;
}
