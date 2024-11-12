#include <iostream>
#include <stack>

using namespace std;

class Dequeue{
    int operations=0;
    stack<int> sFront, sBack;
    private:
    void moveItems(bool backward){
        stack<int>& s1 = backward ? sFront : sBack;
        stack<int>& s2 = backward ? sBack : sFront;
        stack<int> temp;
        size_t n = s1.size() / 2;

        /*
            В момента се прехвърлят всички елементи, което е наивно решение и получаваме O(n) сложност при премахване 
            С другите цикли получаваме амортизирана сложност O(1) за премахване на елементи
        */

        // for(int i = 0 ; i < n; i++){
        //     temp.push(s1.top());
        //     s1.pop();
        //     operations++;
        // }

        while(!s1.empty()){ 
            s2.push(s1.top());
            s1.pop();
            operations++;
        }

        // while(!temp.empty()){
        //     s1.push(temp.top());
        //     temp.pop();
        //     operations++;
        // }
        
    }    
    public:
    void push_front(int a){
        sFront.push(a);
        operations++;
        
    }
    void push_back(int a){
        sBack.push(a);
        operations++;

    }
    int pop_back(){
        if(sBack.empty())moveItems(true);
        int temp = sBack.top();
        sBack.pop();
        operations++;
        return temp;
    }
    int pop_front(){
        if(sFront.empty())moveItems(false);
        int temp = sFront.top();
        sFront.pop();
        operations++;
        return temp;

    }
    int back(){
        if(sBack.empty())moveItems(true);
        operations++;
        return sBack.top();
    }
    int front(){
        if(sFront.empty())moveItems(false);
        operations++;
        return sFront.top();

    }
    bool empty()const{
        return sFront.empty() && sBack.empty();
    }
    int getOperations()const{
        return operations;
    }
};

int main(){
    Dequeue d;
    srand(7543 * time(nullptr));

    int N = 10000000;
    int count = 0;
    for(int i = 0; i< N;i++ ){
        cout<<rand()<<" ";
        // if(d.empty()){
            if(rand()%2){
                d.push_back(i);
            }
            else d.push_front(i);
        // }
        // else{
        //     switch (rand()%4){
        //         case 0:d.push_back(i);break;
        //         case 1:d.push_front(i);break;
        //         case 2:d.pop_front();break;
        //         case 3:d.pop_back();break;
        //     }
        // }
    }
    bool turn = true;
    while(!d.empty()){
        if(turn){
            d.pop_front();
        }
        else d.pop_back();
        turn =  !turn;
    }
    cout<<(double)d.getOperations()/N<<endl;
}   