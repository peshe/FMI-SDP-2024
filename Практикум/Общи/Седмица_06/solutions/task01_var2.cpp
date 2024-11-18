#include <iostream>
#include "Node.h"

template<class T>
void removeConsecutiveDuplicates(Node<T>* lst) {
    if(!lst) {
        return;
    }
    Node<T>* current = lst->next;
    while(current) {
        if(current->previous->value == current->value) {
            Node<T>* nextToTraverse = current->next;
            current->previous->next = nextToTraverse;
            if(nextToTraverse) {
                nextToTraverse->previous = current->previous;
            }

            // If we're using the implementation with the dtor, don't forget to add this
            current->next = nullptr;
            delete current;

            current = nextToTraverse;
        }
        else {
            current = current->next;
        }
    }
}

void task1_test1() {
    // 1, 1, 2, 2, 1, 1, 2, 2, 2, 2, 1, 2, 1, 2
    Node<int>* head = new Node<int>(1);
    head->add(1);
    head->add(2);
    head->add(2);
    head->add(1);
    head->add(1);
    head->add(2);
    head->add(2);
    head->add(2);
    head->add(2);
    head->add(1);
    head->add(2);
    head->add(1);
    head->add(2);

    std::cout << "Before:\n";
    head->print();
    removeConsecutiveDuplicates(head);
    std::cout << "After:\n";
    head->print();
}

void task1_test2() {
    Node<int>* head = new Node<int>(1);
    std::cout << "Before:\n";
    head->print();
    removeConsecutiveDuplicates(head);
    std::cout << "After:\n";
    head->print();
}

void task1_test3() {
    Node<int>* head = new Node<int>(1);
    head->add(1);
    std::cout << "Before:\n";
    head->print();
    removeConsecutiveDuplicates(head);
    std::cout << "After:\n";
    head->print();
}

int main() {
    task1_test1();
    task1_test2();
    task1_test3();
    return 0;
}
