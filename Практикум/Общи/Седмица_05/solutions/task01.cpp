#include "Node.h"

#include <iostream>


template <typename T>
unsigned int countOf(const Node<T>* list, const T& value) {
    unsigned result = 0u;
    while (list != nullptr) {
        if (list->value == value) ++result;
        list = list->next;
    }
    return result;
}

int main () {
    Node<int> l(1);
    l.add(2);
    l.add(3);
    l.add(1);
    l.add(1);
    std::cout << countOf(&l, 1) << std::endl;

    return 0;
}
