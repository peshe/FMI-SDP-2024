/******************************************************************
*  Sample code to the course "Data Structures And Algorithms", FMI
*
* A template class for dynamic array.
*
* A main test file
*
* (cc) Petar Armyanov, FMI, 2024
*******************************************************************/

#include "DynArray.hpp"
#include <iostream>

using std::endl;
using std::cout;

using namespace fmi::sdp;

int main()
{
    using intAlloc = DebugCountAllocator<int>;
    using shortAlloc = DebugCountAllocator<short>;
    using floatAlloc = DebugCountAllocator<float>;


// test the constructors
    DynArray<int, intAlloc> intArray;
    DynArray<short, shortAlloc> shortArray(3);
    assert(intArray.getSize() == 0);
    assert(shortArray.getSize() == 0);
    assert(shortArray.getCapacity() == 3);

// test addition
    for (int i = 0; i < 10; ++i) {
        intArray.append(i);
    }
    assert(intArray.getSize() == 10);
    assert(intArray[3] == 3);

// test the inner iterator class
    for (DynArray<int, intAlloc>::DArrayIterator it = intArray.begin(); it != intArray.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    for (const int& val : intArray) {
        cout << val << " ";
    }
    cout << endl;

// test the += operator with a single element
    for (short i = 100; i < 120; ++i) {
        shortArray += i;
    }
    assert(shortArray.getSize() == 20);

// assign values from array with different type
    intArray = shortArray;
    assert(intArray.getSize() == shortArray.getSize());
    int tt = 0;
    for (DynArray<int, intAlloc>::DArrayIterator it = intArray.begin(); it != intArray.end(); ++it) {
        cout << *it << " ";
        assert(*it == shortArray[tt++]);
    }
    cout << endl;


// append different types
    intArray += shortArray;
    for (size_t i = 0; i < intArray.getSize(); ++i) {
        // test the operator []
        cout << intArray[i] << " ";
        assert(intArray[i]==shortArray[i%shortArray.getSize()]);
    }
    cout << endl;

// test the clear method
    intArray.clear();
    assert(intArray.isEmpty());

// copy ctor test with different types
    DynArray<float, floatAlloc> testArray(shortArray);
    cout << testArray[5] << endl;

// test search and remove
    assert(shortArray.contains(111));
    size_t old_size = shortArray.getSize();
    shortArray.remove(11);
    assert(!shortArray.contains(111));
    assert(shortArray.getSize() == old_size - 1);

    for (size_t i = 0; i < shortArray.getSize(); ++i) {
        cout << shortArray.get(i) << " ";
    }
    cout << endl;

// copy ctor with same type and operator + with different types
    DynArray<int, intAlloc> big = intArray + shortArray;
    cout << big.getSize() << endl;

    big += 'a';
    cout << big[big.getSize() - 1] << endl;

// assignment the same types
    intArray = big;
    cout << intArray[big.getSize() - 1] << endl;
    cout << big[big.getSize() - 1] << endl;

    return 0;
}
