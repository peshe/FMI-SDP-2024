#include "Node.h"

#include <iostream>


template <typename T>
Node<T>* removeAll(Node<T>* list, const T& value) {
    if (list == nullptr) {
        return nullptr;
    }

    Node<T>* next = removeAll(list->next, value);

    if (list->value == value) {
        list->next = nullptr;
        delete list;

        return next;
    }

    list->next = next;
    return list;
}

int main () {
    Node<int>* l  = new Node<int>(1);
    l->add(2);
    l->add(3);
    l->add(1);
    l->add(1);
    l->print();

    l = removeAll(l, 1);
    l->print();

    delete l;
    return 0;
}
