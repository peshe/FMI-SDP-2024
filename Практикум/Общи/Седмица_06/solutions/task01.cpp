#include "Node.h"

#include <iostream>


template <typename T>
void removeConsecutiveDuplicates(Node<T>* lst) {
    if (lst == nullptr) return;

    Node<T>* current = lst;
    while (current->prev != nullptr) {
        current = current->prev;
    }

    while (current->next != nullptr) {
        if (current->value == current->next->value) {
            current->next->remove();
        }
        else {
            current = current->next;
        }
    }
}

int main () {
    Node<int> l(1);
    l.addAtEnd(1);
    l.addAtEnd(2);
    l.addAtEnd(2);
    l.addAtEnd(1);
    l.addAtEnd(1);
    l.addAtEnd(2);
    l.addAtEnd(2);
    l.addAtEnd(2);
    l.addAtEnd(2);
    l.addAtEnd(1);
    l.addAtEnd(2);
    l.addAtEnd(1);
    l.addAtEnd(2);
    l.printFromStart();

    removeConsecutiveDuplicates(&l);
    l.printFromStart();

    return 0;
}
