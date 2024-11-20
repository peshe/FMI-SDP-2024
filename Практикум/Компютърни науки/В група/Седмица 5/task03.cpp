#include <iostream>
#include <cstddef>
#include "SinglyLinkedListNode.hpp"

template <typename T>
Node<T>* removeKth(Node<T>* head, std::size_t k)
{
    if (head == nullptr || k == 0) return nullptr;
    if (k == 1)
    {
        deallocate(head);

        return nullptr;
    }

    std::size_t counter = 1;
    Node<T>* prev = head;
    Node<T>* it = head->next;

    while (it != nullptr)
    {
        ++counter;

        if (counter == k)
        {
            prev->next = it->next;

            Node<T>* temp = it;
            it = it->next;

            delete temp;

            counter = 0;
        }
        else
        {
            prev = it;
            it = it->next;
        }
    }

    return head;
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
    std::size_t k = 3;
    
    head->print();
    head = removeKth<int>(head, k);
    head->print();

    deallocate(head);

    return 0;
}