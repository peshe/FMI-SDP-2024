#include <iostream>
#include "SinglyLinkedListNode.hpp"

template <typename T>
Node<T>* removeAll(Node<T>* head, const T& value)
{
    while (head != nullptr && head->value == value)
    {
        Node<T>* temp = head;
        head = head->next;

        delete temp;
    }

    if (head == nullptr) return nullptr;

    Node<T>* newHead = head; // a value to be returned
    Node<T>* prev = newHead;
    head = head->next;

    while(head != nullptr)
    {
        if (head->value == value)
        {
            prev->next = head->next;

            Node<T>* temp = head;
            head = head->next;
            
            delete temp;
        }
        else
        {
            prev = head;
            head = head->next;
        }
    }

    return newHead;
}

int main()
{
    Node<int>* head =
        new Node<int>(2,
                      new Node<int>(1,
                                    new Node<int>(1, 
                                                  new Node<int>(1, nullptr))));
    head->print();
    head = removeAll<int>(head, 1);
    head->print();

    deallocate(head);

    return 0;
}