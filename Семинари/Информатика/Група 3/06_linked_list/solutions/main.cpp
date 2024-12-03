#include <iostream>

#include "LinkedList.hpp"

void testInsertFront() {
    LinkedList<int> list;
    list.insertFront(1);
    list.insertFront(2);
    list.insertFront(3);

    list.print();
}

void testInsertBack() {
    LinkedList<int> list;
    list.insertBack(1);
    list.insertBack(2);
    list.insertBack(3);

    list.print();
}

void testInsertAt() {
    LinkedList<int> list;
    list.insertBack(1);
    list.insertBack(2);
    list.insertBack(3);
    list.insertAt(11, 0);
    list.insertAt(22, 3);
    list.insertAt(33, 1);
    
    try
    {
        list.insertAt(33, 10);
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }

    list.print();
}

void testRemoveFront() {
    LinkedList<int> list;
    list.insertBack(1);
    list.insertBack(2);
    list.insertBack(3);

    list.removeFront();

    list.print();
}

void testRemoveAt() {
    LinkedList<int> list;
    list.insertBack(1);
    list.insertBack(2);
    list.insertBack(3);
    list.insertBack(4);
    list.insertBack(5);

    list.removeAt(0);
    std::cout << "Remove front:\n";
    list.print();
    list.removeAt(3);
    std::cout << "Remove back:\n";
    list.print();
    list.removeAt(1);
    std::cout << "Remove mid:\n";
    list.print();
}

int plus1(const int& i) {
    if (i == 3) {
        throw std::logic_error("Time to die");
    }
    return i + 1;
}

void testMap() {
    LinkedList<int> list;
    list.insertBack(1);
    list.insertBack(2);
    list.insertBack(3);
    list.insertBack(4);
    list.insertBack(5);

    try {
        LinkedList<int> result = list.map(plus1);
        result.print();
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
        throw;
    }
}

int main()
{
    testMap();
}
