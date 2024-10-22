#include <iostream>

size_t Fibonacci(size_t n){
    if(n==0)return 0;
    if(n==1)return 1;
    return Fibonacci(n-1) + Fibonacci(n-2);
}

size_t Fibonacci2(size_t n, size_t index = 1, size_t curr = 1, size_t prev = 0){
    if(index == n)return curr;
    return Fibonacci2(n,index+1,curr+prev,curr);
}
size_t FibonacciFast(size_t n){return Fibonacci2(n);}

int main(){
    std::cout<<Fibonacci(45)<<std::endl;
    std::cout<<FibonacciFast(45)<<std::endl;
}