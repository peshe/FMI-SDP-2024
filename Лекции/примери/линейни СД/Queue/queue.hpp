/******************************************************************
*  Sample code to the course "Data Structures And Algorithms", FMI
*
* An educational class, representing queue interface class
*
* (cc) Petar Armyanov, FMI, 2024
*******************************************************************/
#pragma once

#ifndef _QUEUE_HEADER_INCLUDED_
#define _QUEUE_HEADER_INCLUDED_

namespace fmi::sdp {

template <class DataType>
class Queue
{
public:
    virtual ~Queue() {};
    virtual DataType dequeue() = 0;
    virtual void enqueue(const DataType& data) = 0;
    virtual const DataType& first() const = 0;
    virtual bool isEmpty() const = 0;
    virtual bool isFull() const = 0;
};

}   // namespace fmi::sdp

#endif // _QUEUE_HEADER_INCLUDED_
