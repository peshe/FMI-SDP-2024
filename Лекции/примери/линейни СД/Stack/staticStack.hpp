/******************************************************************
*  Sample code to the course "Data Structures And Algorithms", FMI
*
* An educational class, representing static stack implementation
*
* (cc) Petar Armyanov, FMI, 2024
*******************************************************************/
#pragma once

#ifndef _STATIC_STACK_HEADER_INCLUDED_
#define _STATIC_STACK_HEADER_INCLUDED_

namespace fmi::sdp {

class StaticStack
{
public:
    StaticStack(size_t size = 16)
        : data(new int[size])
        , tos(0)
        , size(size)
    {}
    StaticStack(const StaticStack& rhs);

    // As the size is constant we have to ensure the destination stack can take all the elements!
    StaticStack& operator=(const StaticStack& rhs);
    ~StaticStack() { delete[] data; }

    void push(int elem);
    int pop();
    const int& top() const;
    bool isEmpty() const;
    bool isFull() const;

private:
    int* data;
    size_t tos;

    const size_t size;
};

}   // namespace fmi::sdp

#endif // _STATIC_STACK_HEADER_INCLUDED_
