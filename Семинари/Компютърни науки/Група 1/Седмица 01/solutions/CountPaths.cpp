#include <iostream>

int CountPaths(int x, int y){// task 1
    if(x<0)return 0;
    if(y<0)return 0;
    if(!x && !y) return 1;
    return CountPaths(x-1,y) + CountPaths(x,y-1);
}

int main(){
    std::cout<<CountPaths(3,3)<<std::endl;
}