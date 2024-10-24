#include <iostream>

const int capacity = 256;
class Queue
{
    private:
        int arr[capacity];
        int back;
        int front;

    public:
        Queue()
        {
            front = 0;
            back = 0;
        }
        void enqueue(int element)
        {
            arr[back] = element;
            back++;
            back %= capacity;

        }
        int dequeue()
        {
            int tmp = arr[front];
            front++;
            front%=256;
            return tmp;
        }
        int peak()
        {
            return arr[front];
        }
        bool isEmpty()
        {
            return front == back;
        }
        int size()
        {
            if(back < front)
            {
                return back + capacity - front;
            }
            else
            {
                return back - front;
            }
        }

};
int main()
{
    Queue a;
    a.enqueue(5);
    a.enqueue(6);
    a.enqueue(7);
    std::cout << a.dequeue() << std::endl;
    std::cout << a.size() << std::endl;
    std::cout << a.dequeue() << std::endl;
    std::cout << a.size() << std::endl;
    std::cout << a.dequeue() << std::endl;
    std::cout << a.size() << std::endl;
    std::cout << std::boolalpha << a.isEmpty();
}