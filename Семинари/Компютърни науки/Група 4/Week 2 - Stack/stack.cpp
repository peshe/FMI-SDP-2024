#include <iostream>

class Stack
{
    private:
        const int CAPACITY = 256;
        int size = 0;
        int arr[CAPACITY];

    public:
        void push(int el)
        {
            arr[size++] = el;
        }
        int pop()
        {
            return arr[--size];
        }
        int top()
        {
            return arr[size - 1];
        }
        int size()
        {
            return size;
        }
        bool empty()
        {
            return size == 0;
        }
}