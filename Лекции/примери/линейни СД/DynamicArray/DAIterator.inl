/******************************************************************
*  Sample code to the course "Data Structures And Algorithms", FMI
*
* A template class for dynamic array.
*
* Implementation file for the inner iterator class
*
* (cc) Petar Armyanov, FMI, 2024
*******************************************************************/

#ifndef _DYNAMIC_ARRAY_ITERATOR_INCLUDED__
#define _DYNAMIC_ARRAY_ITERATOR_INCLUDED__

// The iterator class must behave like a pointer.
// That is why we define:
// operator * (that extract the value from the pointee)
// operator -> to give access to a member of the pointee
// operators ++ and -- (prefix and postfix implementation
// equality operators
// comparison operators
// Also operators + and += with a number, as it is random access iterator
class DArrayIterator
{
    friend class DynArray;
public:
    const DataType& operator*() const
    {
        return *pointer;
    }
    DataType& operator*()
    {
        return *pointer;
    }

    const DataType* operator->() const
    {
        return pointer;
    }
    DataType* operator->()
    {
        return pointer;
    }

    DArrayIterator& operator++()
    {
        ++pointer;
        return *this;
    }
    DArrayIterator operator++(int)
    {
        DArrayIterator res(*this);
        ++(*this);
        return res;
    }
    DArrayIterator& operator--()
    {
        --pointer;
        return *this;
    }
    DArrayIterator operator--(int)
    {
        DArrayIterator res(*this);
        --(*this);
        return res;
    }
    DArrayIterator& operator+=(int offset)
    {
        pointer += offset;
        return *this;
    }
    DArrayIterator operator+(int offset) const
    {
        DArrayIterator res(*this);
        res += offset;
        return res;
    }

    const DataType& operator[](int offset) const
    {
        return *(pointer + offset);
    }
    DataType& operator[](int offset)
    {
        return *(pointer + offset);
    }

    bool operator==(const DArrayIterator& other) const
    {
        return pointer == other.pointer;
    }
    bool operator!=(const DArrayIterator& other) const
    {
        return !(other == *this);
    }
    bool operator<(const DArrayIterator& other) const
    {
        return pointer < other.pointer;
    }
    bool operator>(const DArrayIterator& other) const
    {
        return other < *this;
    }
    bool operator>=(const DArrayIterator& other) const
    {
        return !(*this < other);
    }
    bool operator<=(const DArrayIterator& other) const
    {
        return !(*this > other);
    }
private:
    // Private ctor, so we do not want users to create iterators
    //Note, that the default copy ctor and operator are available
    DArrayIterator(DataType* pointer) : pointer(pointer){}

    DataType* pointer;
};

#endif //_DYNAMIC_ARRAY_ITERATOR_INCLUDED__
