#include <iostream>
#include "Node.h"

template <class T>
void mirror(Node<T>* lst) {
    if(!lst){
        return;
    }
    Node<T>* tail = lst;
    while(tail->next){
        tail = tail->next;
    }

    Node<T>* current = tail;
    while(current) {
        tail->add(current->value);
        tail = tail->next;
        current = current->previous;
    }
}

void mirror_test1() {
    Node<int>* head = new Node<int>(1);
    head->add(2);
    head->add(3);

    std::cout << "Before:\n";
    head->print();
    mirror(head);
    std::cout << "After:\n";
    head->print();
}

void mirror_test2() {
    Node<int>* head = new Node<int>(1);

    std::cout << "Before:\n";
    head->print();
    mirror(head);
    std::cout << "After:\n";
    head->print();
}

int main() {
    mirror_test1();
    mirror_test2();
    return 0;
}
