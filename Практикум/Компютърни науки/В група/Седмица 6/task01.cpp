#include <iostream>
#include "DoublyLinkedListNode.hpp"

template <typename T>
void removeConsecutiveDubplicates(Node<T>* head)
{
    if (head == nullptr || head->next == nullptr)
        return;
    
    Node<T>* it = head;
    
    while (it != nullptr)
    {
        //std::cout << "it: " << it->value << ' ';
        if (it->prev != nullptr && it->value == it->prev->value)
        {
            Node<T>* temp = it;
            it->prev->next = it->next;

            // The following check is for the last element
            if (it->next != nullptr)
                it->next->prev = it->prev;

            it = it->prev;

            temp->prev = temp->next = nullptr;
            //std::cout << "temp: " << temp->value;
            delete temp;
        }
        else
        {
            it = it->next;
        }
        //std::cout << std::endl;
    }
}

int main()
{
    Node<int>* head = new Node<int>(1);
    Node<int>* el1 = new Node<int>(1);
    Node<int>* el2 = new Node<int>(2);
    Node<int>* el3 = new Node<int>(2);
    Node<int>* el4 = new Node<int>(1);
    Node<int>* el5 = new Node<int>(1);
    Node<int>* el6 = new Node<int>(2);
    Node<int>* el7 = new Node<int>(2);

    head->next = el1;
    el1->prev = head; el1->next = el2;
    el2->prev = el1; el2->next = el3;
    el3->prev = el2; el3->next = el4;
    el4->prev = el3; el4->next = el5;
    el5->prev = el4; el5->next = el6;
    el6->prev = el5; el6->next = el7;
    el7->prev = el6;

    head->print();
    removeConsecutiveDubplicates<int>(head);
    head->print();

    deallocate<int>(head);

    return 0;
}