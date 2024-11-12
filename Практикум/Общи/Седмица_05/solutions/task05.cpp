#include "Node.h"

#include <cassert>
#include <iostream>
#include <new>


template <typename T>
Node<T>* cloneReversed(Node<T>* first, Node<T>*& last) {
    if (first == nullptr) {
        last = nullptr;
        return nullptr;
    }

    if (first->next == nullptr) {
        last = new Node<T>(first->value);
        return last;
    }

    Node<T>* result = cloneReversed(first->next, last);

    try {
        last->next = new Node<T>(first->value);
        last = last->next;
        return result;
    }
    catch (std::bad_alloc& e) {
        delete result;
        throw;
    }
}

template <typename T>
Node<T>* cloneReversed(Node<T>* first) {
    Node<T>* last = nullptr;
    return cloneReversed(first, last);
}

int main () {
    Node<int>* l  = new Node<int>(1);
    l->add(2);
    l->add(3);
    l->add(4);
    l->add(5);
    l->add(6);
    l->add(7);

    Node<int>* clone = cloneReversed(l);
    l->print();
    clone->print();

    delete l;
    delete clone;
    return 0;
}
