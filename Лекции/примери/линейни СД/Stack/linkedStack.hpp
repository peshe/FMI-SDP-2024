/******************************************************************
*  Sample code to the course "Data Structures And Algorithms", FMI
*
* An educational class, representing linked stack implementation
*
* (cc) Petar Armyanov, FMI, 2024
*******************************************************************/
#pragma once

#ifndef _LINKED_STACK_HEADER_INCLUDED_
#define _LINKED_STACK_HEADER_INCLUDED_

#include <stdexcept>
#include <cassert>

namespace fmi::sdp {

template <typename DataType>
class LinkedStack
{
public:
    LinkedStack();
    LinkedStack(const LinkedStack<DataType>& stack);
    ~LinkedStack();
    LinkedStack<DataType>& operator= (const LinkedStack<DataType>& rhs);

    void push(const DataType& elem);
    DataType pop();
    const DataType& top() const;
    bool isEmpty() const;

private:
    struct node
    {
        DataType data;
        node* next;

        node(const DataType& d, node* n = nullptr)
            : data(d)
            , next(n)
        {}
    } *tos;

private:
    void clear();
    void copy(const node* top);
};


#include "LinkedStack.inl"

} // namespace fmi::sdp

#endif  //_LINKED_STACK_HEADER_INCLUDED_
