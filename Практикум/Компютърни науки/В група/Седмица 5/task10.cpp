#include <iostream>
#include "SinglyLinkedListNode.hpp"

template <typename T>
Node<T>* getMiddle(Node<T>* head)
{
    Node<T>* slow = head;
    Node<T>* fast = head;

    while (fast != nullptr && fast->next != nullptr)
    {
        slow = slow->next;
        fast = fast->next->next;
    }

    return slow;
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
    std::cout << getMiddle(head)->value << std::endl;
    std::cout << getMiddle(head->next)->value << std::endl;

    deallocate(head);

    return 0;
}