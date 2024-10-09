/******************************************************************
*  Sample code to the course "Data Structures And Algorithms", FMI
*
* A template class for sorted dynamic array.
* The goal is to illustrate the idea of proxy design pattern
* and data structure augmentation.
*
* (cc) Petar Armyanov, FMI, 2024
*******************************************************************/
#pragma once

#ifndef _SORTED_ARRAY_INCLUDED__
#define _SORTED_ARRAY_INCLUDED__

#include "../DynamicArray/DynArray.hpp"

namespace fmi
{
namespace sdp
{

// Dynamic array, that stores the elements ordered in increasing order
// Requires that DataType has overloaded or native operator < 
template <class DataType>
class SortedArray
{
public:
    // The class uses internally the dynamic array and 
    // can rely on its life-cycle methods.

    // A method and operator to add an element
    void add(const DataType& elem);
    SortedArray& operator+= (const DataType& elem) 
    {
        add(elem); 
        return *this;
    }

    // Search an element by value. Uses binary search algorithm
    // Returns the index of the element or -1 if not found
    int find(const DataType& elem) const;
    
    // Remove element by index.
    // Rely on DynArray to check the validity of the argument
    void remove(size_t index) { array.remove(index); }

    // Some getters...
    bool isEmpty() const { return array.isEmpty(); }
    size_t getSize() const { return array.getSize(); }

    void clear() { array.clear(); }

private:
// the proxy is implemented in external file
// Note, that it is in a private section
#include "SortedArrayProxy.inl"

public:    
    // Some more public members

    // Read only access to an element
    const DataType& operator[](size_t index) const { return array[index]; }

    // Read/write access. Here we have to return a proxy object
    SortedArrayProxy operator[](size_t index) { return SortedArrayProxy(*this, index); }

private:
    // Helper methods to keep the array sorted

    // Move an element towards the beginning of the array
    // Used in case of decreasing the value or insert a new element
    void moveUp(size_t index);

    // Move an element towards the end of the array
    // Used in case of increasing the value
    void moveDown(size_t index);

private:
    DynArray<DataType> array;
};

#include "SortedArray.inl"

} //namespace sdp
} //namespace fmi

#endif //_SORTED_ARRAY_INCLUDED__
