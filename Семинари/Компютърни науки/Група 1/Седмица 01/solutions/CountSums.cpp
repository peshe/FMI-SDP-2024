#include <iostream>

int countSumsCalc(int num,int maxnum){
    if(num == 0) return 1;
    int total = 0;
    for(int i=maxnum;i<=num;i++){
        total+=countSumsCalc(num-i,i);
    }
    return total;
}

int countSums(int n){
    return countSumsCalc(n,1);
}
    
int main(){
    std::cout<<countSums(10)<<std::endl;

}