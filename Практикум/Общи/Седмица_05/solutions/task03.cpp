#include "Node.h"

#include <iostream>


template <typename T>
Node<T>* removeNthThenEveryKth(Node<T>* list, size_t n, size_t k) {
    if (list == nullptr) {
        return nullptr;
    }

    if (n <= 1) {
        Node<T>* next = list->next;
        list->next = nullptr;
        delete list;

        return removeNthThenEveryKth(next, k, k);
    }

    list->next = removeNthThenEveryKth(list->next, n - 1, k);
    return list;
}

template <typename T>
Node<T>* removeKth(Node<T>* list, size_t k) {
    return removeNthThenEveryKth(list, k, k);
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

    l = removeKth(l, 3);
    l->print();

    delete l;
    return 0;
}
