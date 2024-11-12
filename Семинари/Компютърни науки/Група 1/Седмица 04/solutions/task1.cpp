#include <stack>
#include <iostream>

class StackMin{
    std::stack<int> numbers;
    std::stack<int> min;
    public:
    void push(int a){
        numbers.push(a);
        if( min.empty() || min.top() >= a)
            min.push(a);
    }
    int pop(){
        int val = numbers.top();
        numbers.pop();
        if(val == min.top())
            min.pop();
    }
    int top()const{
        return numbers.top();
    }
    bool empty()const{
        return numbers.empty();
    }
    int getMin()const{
        return min.top();
    }
};

int main(){
    StackMin s;
    s.push(5);
    s.push(2);
    s.push(3);
    s.push(1);
    s.push(1);
    s.push(4);
    s.push(6);
    s.push(7);
    s.push(0);
    while(!s.empty()){
        std::cout<<s.getMin()<<" "<< s.top()<<std::endl;
        s.pop();
    }
}