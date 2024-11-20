#include <iostream>
#include "DoublyLinkedListNode.hpp"

template <typename T>
void deallocateCyclic(Node<T>* head)
{
    if (head == nullptr) return;
    if (head->prev == nullptr && head->next == nullptr)
    {
        delete head;
        return;
    }

    Node<T>* it = head->next;
    
    while (it != head)
    {
        Node<T>* temp = it;
        it = it->next;

        temp->prev = temp->next = nullptr;
        delete temp;
    }
    
    delete it;
}

template <typename T>
unsigned int countOf(const Node<T>* lst, const T& value)
{
    if (lst == nullptr) return 0;

    unsigned int counter = (lst->value == value ? 1 : 0);

    if (lst->prev == nullptr && lst->next == nullptr)
    {
        return counter;
    }

    Node<T>* it = lst->next;
    while(it != lst)
    {
        if (it->value == value)
            ++ counter;
        it = it->next;
    }

    return counter;
}

template <typename T>
Node<T>* removeAll(Node<T>* lst, const T& value)
{
    if (lst == nullptr) return nullptr;
    if (lst->prev == nullptr && lst->next == nullptr)
    {
        if (lst->value == value)
        {
            delete lst;
            lst = nullptr;
        }
        return lst;
    }

    Node<T>* it = lst->next;

    while (it != lst)
    {
        if (it->value == value)
        {
            Node<T>* temp = it;
            it->prev->next = it->next;
            it->next->prev = it->prev;

            it->prev = it->next = nullptr;
            delete temp;
        }
        else
        {
            it = it->next;
        }
    }

    if (it->value == value)
    {
        Node<T>* temp = it;
        it->prev->next = it->next;
        it->next->prev = it->prev;

        it->prev = it->next = nullptr;
        delete temp;
    }

    return it;
}

int main()
{
    Node<int>* head = new Node<int>(1);
    Node<int>* el1 = new Node<int>(1);
    Node<int>* el2 = new Node<int>(1);
    Node<int>* el3 = new Node<int>(4);

    head->prev = el3; head->next = el1;
    el1->prev = head; el1->next = el2;
    el2->prev = el1; el2->next = el3;
    el3->prev = el2; el3->next = head;

    std::cout << countOf<int>(head, 1) << std::endl;
    std::cout << countOf<int>(head, 2) << std::endl;
    std::cout << countOf<int>(head, 3) << std::endl;
    std::cout << countOf<int>(head, 4) << std::endl;
    
    deallocateCyclic<int>(head);

    return 0;
}