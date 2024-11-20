#include <iostream>
#include <new>
#include "SinglyLinkedListNode.hpp"

template <typename T>
Node<T>* cloneReversed(Node<T>* head)
{
    if (head == nullptr || head->next == nullptr) return head;
    
    Node<T>* it = head;
    Node<T>* prev = nullptr;

    while (it != nullptr)
    {
        try
        {
            Node<T>* newNode = new Node<T>(it->value);
            newNode->next = prev;
            prev = newNode;
            it = it->next;
        }
        catch (const std::bad_alloc& e)
        {
            deallocate(prev);

            throw e;
        }
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
    head = cloneReversed<int>(head);
    head->print();

    deallocate(head);
    return 0;
}