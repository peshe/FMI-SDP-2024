#include <iostream>
#include <stack>
#include <queue>
using namespace std;

template<typename T>
class QueueWithHistory{
    struct Operation{
        enum operationType{
            ENQUEUE,
            DEQUEUE
        };
        operationType s;
        T el;
    };
    stack<Operation> undo,redo;
    deque<T> q;
    
    void clearRedo(){
        while(!redo.empty())
            redo.pop();
    }

    public:
    T& front(){
        return q.front();
    }
    bool empty(){
        return q.empty();
    }
    void enqueue(const T& el){
        q.push_back(el);
        undo.push({ENQUEUE, el});
    }
    T dequeue(){
        T temp = q.front();
        q.pop_front();
        undo.push({DEQUEUE, temp});
        return temp;
    }
    void undo(){
        if(undo.empty())
            throw invalid_argument("There are no operations to undo");
        
        Operation op = undo.top();
        undo.pop();
        
        if(op.s == DEQUEUE){
            redo.push(op);
            q.push_front(op.el);
        }
        else{
            redo.push(op);
            q.pop_back();
        } 
    }
    void redo(){
        if(redo.empty())
            throw invalid_argument("There are no operations to redo");
        
        Operation op = redo.top();
        redo.pop();
        
        if(op.s == DEQUEUE){
            undo.push(op);
            q.pop_front();
        }
        else{
            undo.push(op);
            q.push_back(op.el);
        }
    }
};


int main(){

}