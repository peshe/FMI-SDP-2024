#include "Node.h"

#include <iostream>


template <typename T>
Node<T>* reverse(Node<T>* list) {
    if (list == nullptr || list->next == nullptr) {
        return list;
    }

    Node<T>* result = reverse(list->next);
    list->next->next = list;
    list->next = nullptr;

    return result;
}

int main () {
    Node<int>* l  = new Node<int>(1);
    l->add(2);
    l->add(3);
    l->add(4);
    l->add(5);
    l->add(6);
    l->add(7);
    l->print();

    l = reverse(l);
    l->print();

    delete l;
    return 0;
}
