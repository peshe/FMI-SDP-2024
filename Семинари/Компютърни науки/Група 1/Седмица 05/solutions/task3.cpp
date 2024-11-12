#include <iostream>
#include <queue>
using namespace std;

template <typename T>
class PriorityQueue{
    const size_t P;
    queue<T>* data;
    queue<T>* getHightestPriority()const{
        int index = P-1;
        while(data[index].empty())
            index--;
        
        return (index < 0? nullptr : &data[index]);

    }
    public:
    PriorityQueue(size_t priorities = 1):P(priorities),data(new queue<T>[priorities]){};
    bool isEmpty()const{
        return getHightestPriority() == nullptr;
    }
    void enqueue(const T& el, size_t priority){
        if(priority > P)
            throw invalid_argument("Invalid priority");
        data[priority].push(el);
    }
    T dequeue(){
        queue<T>* it = getHightestPriority();
        if(!it)
            throw underflow_error("The queue is empty");
        
        T temp = it->front();
        it->pop();
        
        return temp;
    }
    T& front()const{
        queue<T>* it = getHightestPriority();
        if(!it)
            throw underflow_error("The queue is empty");
        return it->front();
    }
};

int main(){ 
}