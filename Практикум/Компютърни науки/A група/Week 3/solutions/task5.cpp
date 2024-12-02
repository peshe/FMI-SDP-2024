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
    int Max = 0,total=0,sum = 0;
    for(int i = 1; i < N; i++ ){
        if(arr[i] > arr[Max]){
            total += (i-Max-1)*std::min(arr[i],arr[Max]); 
            total -= sum;
            Max = i;
            sum=0;
        }
        else sum+=arr[i];
    }
    
    Max = N-1;
    sum=0;
    for(int i = Max-1; i >= 0 ; i-- ){
        if(arr[i] >= arr[Max]){
            total += (Max-i-1)*std::min(arr[i],arr[Max]); 
            total -= sum;
            Max = i;
            sum=0;
        }
        else sum+=arr[i];
    }
    cout<<total;
}
/*
12
0 1 0 2 1 0 1 3 2 1 2 1
*/