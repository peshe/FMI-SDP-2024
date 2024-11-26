#include <iostream>
#include "SinglyLinkedListNode.hpp"

template <typename T>
Node<T>* reverse(Node<T>* head)
{
    if (head == nullptr || head->next == nullptr) return head;
    Node<T>* prev = nullptr;

    while (head != nullptr)
    {
        Node<T>* temp = head;
        
        head = head->next;
        temp->next = prev;
        prev = temp;
        
    }

    return prev;
}

int main()
{
    Node<int>* head =
        new Node<int>(1,
                      new Node<int>(2,
                                    new Node<int>(3, 
                                                  new Node<int>(4,
                                                                new Node<int>(5,
                                                                              new Node<int>(6,
                                                                                  new Node<int>(7)))))));
    head->print();
    head = reverse<int>(head);
    head->print();

    deallocate(head);

    return 0;
}