/******************************************************************
*  Sample code to the course "Data Structures And Algorithms", FMI
*
* An educational class, representing static queue implementation
*
* (cc) Petar Armyanov, FMI, 2024
*******************************************************************/
#pragma once

#ifndef _STATIC_QUEUE_HEADER_INCLUDED_
#define _STATIC_QUEUE_HEADER_INCLUDED_

#include "queue.hpp"
#include <stdexcept>

namespace fmi::sdp {

template <class DataType>
class StaticQueue : public Queue<DataType>
{
public:
    StaticQueue(size_t size = 16)
        : data(new DataType[size+1])
        , begin(0)
        , end(0)
        , size(size+1)
    {}
    StaticQueue(const StaticQueue<DataType>& rhs);

    StaticQueue<DataType>& operator=(const StaticQueue<DataType>& rhs);
    ~StaticQueue() { delete[] data; }

    void enqueue(const DataType& data) override;
    DataType dequeue() override;
    const DataType& first() const override;
    bool isEmpty() const override;
    bool isFull() const override;

    size_t count() const
    {
        return (end + size - begin) % size;
    }
private:
    DataType* data;
    size_t begin, end;

    const size_t size;
};

#include "staticQueue.inl"

}   // namespace sdp::fmi

#endif // _STATIC_QUEUE_HEADER_INCLUDED_
