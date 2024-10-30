#include "staticStack.hpp"
#include <stdexcept>

namespace fmi::sdp {

int StaticStack::pop()
{
    if (!isEmpty()) return data[--tos];
    throw std::underflow_error("Empty stack");
}


const int& StaticStack::top() const
{
    if (!isEmpty()) return data[tos-1]; 
    throw std::underflow_error("Empty stack");
}


void StaticStack::push(int elem)
{
    if (!isFull()) data[tos++] = elem;
    else throw std::overflow_error("Stack is full");
}


bool StaticStack::isEmpty() const
{
    return tos == 0;
}


bool StaticStack::isFull() const
{
    return tos == size;
}


StaticStack::StaticStack(const StaticStack& rhs)
    : data(new int[rhs.size])
    , tos(0)
    , size(rhs.size)
{
    while (tos < rhs.tos)
        push(rhs.data[tos]);
}


StaticStack& StaticStack::operator=(const StaticStack& rhs)
{
    if (this != &rhs) {
        if (rhs.tos <= size) {
            tos = 0;
            while (tos < rhs.tos)
                push(rhs.data[tos]);
        }
        else {
            throw std::overflow_error("Not enough space");
        }
    }
    return *this;
}

}   // namespace fmi::sdp
