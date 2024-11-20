#include <iostream>
#include "DoublyLinkedListNode.hpp"

template <typename T>
void mirror(Node<T>* head)
{
    if (head == nullptr) return;

    Node<T>* it = head;
    Node<T>* last_created = new Node<T>(it->value);

    while (it->next != nullptr)
    {
        it = it->next;

        last_created->prev = new Node(it->value);
        last_created->prev->next = last_created;
        last_created = last_created->prev;
    }

    it->next = last_created;
    last_created->prev = it;
}

int main()
{
    Node<int>* head = new Node<int>(1);
    Node<int>* el1 = new Node<int>(4);
    Node<int>* el2 = new Node<int>(5);
    //Node<int>* el3 = new Node<int>(4);
    //Node<int>* el4 = new Node<int>(1);
    // Node<int>* el5 = new Node<int>(1);
    // Node<int>* el6 = new Node<int>(2);
    // Node<int>* el7 = new Node<int>(2);

    head->next = el1;
    el1->prev = head; el1->next = el2;
    el2->prev = el1; //el2->next = el3;
    //el3->prev = el2;

    head->print();
    mirror<int>(head);
    head->print();

    deallocate<int>(head);

    return 0;
}