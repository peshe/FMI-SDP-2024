#include <iostream>

class Node
{
    private:
        int element;
        Node* next;

    public:
        Node(int element, Node* next)
        {
            this->element = element;
            this->next = next;
        }
        void setNext(Node* next)
        {
            this->next = next;
        }
        Node* getNext()
        {
            return next;
        }
        int getElement()
        {
            return element;
        }

};

class Queue
{
    private:
        Node* front;
        Node* back;
        int size;
    
    public:
        Queue()
        {
            front = nullptr;
            back = nullptr;
            size = 0;
        }
        void enqueue(int element)
        {
            Node* ptr = new Node(element, nullptr);
            if(back != nullptr) back->setNext(ptr);
            back = ptr;
            size++;
            if(front == nullptr)
            {
                front = back;
            }
        }
        int dequeue()
        {
            if(front == nullptr)
            {
                throw "Queue is empty";
            }
            int value = front->getElement();
            Node* el = front->getNext();
            front->setNext(nullptr);
            delete front;
            front = el;
            size--;
            return value;
        }
        int peak()
        {
            return front->getElement();
        }
        int getSize()
        {
            return size;   
        }
        bool isEmpty()
        {
            return size == 0;
        }
        void erase()
        {
            while(!isEmpty())
            {
                dequeue();
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
    std::cout << a.getSize() << std::endl;
    std::cout << a.dequeue() << std::endl;
    std::cout << a.getSize() << std::endl;
    std::cout << a.dequeue() << std::endl;
    std::cout << a.getSize() << std::endl;
    std::cout << std::boolalpha << a.isEmpty();
    a.erase();
}