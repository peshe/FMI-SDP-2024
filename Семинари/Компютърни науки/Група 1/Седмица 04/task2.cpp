#include <iostream>
#include <stack>

void sort(std::stack<int>& s){
    std::stack<int> temp;
        int val,count;
    while(!s.empty()){
        val = s.top();
        s.pop();
        if(temp.empty() || temp.top() > val)
            temp.push(val);
        else{
            count = 0;
            while(!temp.empty() && temp.top() < val){
                s.push(temp.top());
                temp.pop();
                count++;
            }
            temp.push(val);
            for(int i=0;i<count;i++){
                temp.push(s.top());
                s.pop();
            }
        }
    }
    while(!temp.empty()){
        s.push(temp.top());
        temp.pop();
    }
    return;
} 

int main(){
    std::stack<int> s;
    s.push(5);
    s.push(2);
    s.push(3);
    s.push(1);
    s.push(1);
    s.push(4);
    s.push(6);
    s.push(7);
    s.push(0);
    sort(s);
    while(!s.empty()){
        std::cout<<s.top()<<' ';
        s.pop();
    }
}