#include <iostream>
#include <stack>

using namespace std;

template <typename T>
class Queue{
    stack<T> sFront, sBack;
    void moveItems(){
        while(!sBack.empty()){
            sFront.push(sBack.top());
            sBack.pop();
        }
    }
    bool needsMoving()const{
        return sFront.empty() && !sBack.empty();
    }

    public:
    bool isEmpty()const{
        return sFront.empty() && sBack.empty();
    }
    void enqueue(const T& el){
        sBack.push(el);
    }
    T dequeue(){
        T temp = front();
        sFront.pop();
        return temp;
    }
    T& front()const{
        if(isEmpty()){
                throw std::underflow_error("There are no items in the queue");
        }    
        if(needsMoving())
            moveItems();
        return sFront.top();
    }
    size_t size()const{
        return sFront.size() + sBack.size();
    }
};

int main() {
}