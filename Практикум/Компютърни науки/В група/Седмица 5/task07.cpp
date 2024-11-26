#include <iostream>
#include <string>
#include "SinglyLinkedListNode.hpp"

Node<int>* fromStringToSLL(const std::string& str)
{
    Node<int>* prev = nullptr;

    for (const char digit : str)
    {
        Node<int>* newDigit = new Node<int>(digit - '0');
        newDigit->next = prev;
        prev = newDigit;
    }

    return prev;
}

Node<int>* sumBigNs(Node<int>* n1, Node<int>* n2)
{
    int new_digit = n1->value + n2->value;
    Node<int>* res = new Node<int>(new_digit % 10), *it = res;
    int prenos = new_digit / 10;
    n1 = n1->next; n2 = n2->next;

    while (n1 != nullptr && n2 != nullptr)
    {
        int new_digit = n1->value + n2->value + prenos;
        Node<int>* newDigit = new Node<int>(new_digit % 10);
        it->next = newDigit;
        it = newDigit;

        n1 = n1->next;
        n2 = n2->next;
        prenos = new_digit / 10;
    }

    Node<int>* head = (n1 != nullptr ? n1 : n2);

    while (head != nullptr)
    {
        int new_digit = head->value + prenos;
        Node<int>* newDigit = new Node<int>(new_digit % 10);
        it->next = newDigit;
        it = newDigit;

        head = head->next;
        prenos = new_digit / 10;
    }
    if (prenos) {
        Node<int>* newDigit = new Node<int>(1);
        it->next = newDigit;
        it = newDigit;
    }

    return res;
}

int main()
{
    std::string number1 = "11111111";
    std::string number2 = "999";

    Node<int>* n1 = fromStringToSLL(number1);
    Node<int>* n2 = fromStringToSLL(number2);
    
    n1->print(); n2->print();

    Node<int>* result = sumBigNs(n1, n2);
    result->print();

    deallocate(n1);
    deallocate(n2);
    deallocate(result);

    return 0;
}