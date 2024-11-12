#include <iostream>
#include <queue>

using namespace std;

class MinQueue{
    deque<int> minQ;
    queue<int> data;
    public:

    void enqueue(int el){
        data.push(el);
        while(!minQ.empty() && minQ.back()>el)
            minQ.pop_back();
        minQ.push_back(el);
    };
    int dequeue(){
        if(data.front() == minQ.front())
            minQ.pop_front();
        int temp = data.front();
        data.pop();
        return temp;
    };
    int front()const{
        return data.front();
    };
    bool empty()const{
        return data.empty();
    };
    int getMin()const{
        return minQ.front();
    };
};

int main(){
    MinQueue mq;
    mq.enqueue(0);
    mq.enqueue(3);
    mq.enqueue(2);
    mq.enqueue(4);
    mq.enqueue(1);
    mq.enqueue(5);
    mq.enqueue(3);
    mq.enqueue(1);
    mq.enqueue(2);
    mq.enqueue(3);

    while(!mq.empty()){
        cout<<mq.front()<<" "<<mq.getMin()<<endl;
        mq.dequeue();
    }
}