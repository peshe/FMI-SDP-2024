#include <iostream>
#include "SinglyLinkedListNode.hpp"

template <typename T>
unsigned int countOf(const Node<T>* head, const T& value)
{
    unsigned int counter = 0;

    while (head != nullptr)
    {
        if (head->value == value)
            ++counter;

        head = head->next;
    }

    return counter;
}

int main()
{
    Node<int> *l1 = new Node<int>(1,
                                  new Node<int>(2,
                                                new Node<int>(2,
                                                              new Node<int>(4))));

    l1->print();
    std::cout << countOf<int>(l1, 2) << std::endl;

    deallocate(l1);
    
    return 0;
}