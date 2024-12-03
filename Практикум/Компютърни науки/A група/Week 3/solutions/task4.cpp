#include <iostream>
#include <stack>
#include <vector>

using namespace std;



int main(){
    int N,x;
    cin>>N;
    vector<int> arr;
    for(int i= 0; i<N;i++){
        cin>>x;
        arr.push_back(x);
    }

    stack<int> s;
    vector<int> res;

    for(int i= 0;i<N;i++){
        while(!s.empty() && arr[s.top()]<= arr[i])
            s.pop();
        if(s.empty())res.push_back(i+1);
        else res.push_back(i-s.top());
        s.push(i);
    }
    for(int i :res)
        cout<<i<<" ";
}
/*
7  
80 60 70 60 75 85 100
*/
