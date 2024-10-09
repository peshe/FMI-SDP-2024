/******************************************************************
*  Sample code to the course "Data Structures And Algorithms", FMI
*
*   A template class for sorted dynamic array.
* implementation of member functions.
*
* (cc) Petar Armyanov, FMI, 2024
*******************************************************************/

#ifndef _SORTED_ARRAY_IMPLEMENTATION_INCLUDED__
#define _SORTED_ARRAY_IMPLEMENTATION_INCLUDED__

template <class DataType>
inline void SortedArray<DataType>::add(const DataType& elem)
{
    // First append the element, using the member class method
    array += elem;
    // Then ensure the correct order
    moveUp(array.getSize() - 1);
}


// Binary search algorithm
template <class DataType>
inline int SortedArray<DataType>::find(const DataType& elem) const
{
    size_t left = 0, right = array.getSize();
    while (left < right) {
        size_t middle = left + (right-left) / 2;
        const DataType& cur = array[middle];
        if (elem < cur) right = middle;
        else if (cur < elem) left = middle + 1;
        else return (int)middle;
    }
    return -1;
}


// Move towards the beginning.
// Tries to minimize the assignments
template <class DataType>
inline void SortedArray<DataType>::moveUp(size_t index)
{
    if (index == 0 || array[index - 1] < array[index]) {
        return;
    }

    DataType data = array[index];
    while (index && data < array[index-1]) {
        array[index] = array[index - 1];
        --index;
    }
    array[index] = data;
}


// Move towards the end.
// Tries to minimize the assignments
template <class DataType>
inline void SortedArray<DataType>::moveDown(size_t index)
{
    if (index == array.getSize() - 1 || array[index] < array[index + 1]) {
        return;
    }

    DataType data = array[index];
    while (index < array.getSize() - 1 && array[index+1] < data) {
        array[index] = array[index + 1];
        ++index;
    }
    array[index] = data;
}

#endif //_SORTED_ARRAY_IMPLEMENTATION_INCLUDED__
