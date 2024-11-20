#ifndef _SINGLE_LINKED_NODE_HPP_
#define _SINGLE_LINKED_NODE_HPP_

#include <iostream>

template <class T>
class Node
{
    public:
        T value;
        Node<T> *next;

        Node(T value = T(), Node *next = nullptr)
            : value(value), next(next) {}

        void print() const 
        {
            const Node<T>* temp = this;
            
            while (temp != nullptr)
            {
                std::cout << temp->value << " -> ";
                temp = temp->next;
            }
            std::cout << "nullptr" << std::endl;
        }
};

template <typename T>
void deallocate(Node<T>* head)
{
    while (head != nullptr)
    {
        Node<T>* temp = head;
        head = head->next;
        
        delete temp;
    }
}

#endif