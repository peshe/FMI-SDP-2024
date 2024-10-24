#include <iostream>

int binarySearch(int* arr,int l,int r,int val){
    int m = (r+l)/2;
    if(r<l)return -1;
    if(arr[m] > val)return binarySearch(arr,l,m-1,val);
    if(arr[m] < val)return binarySearch(arr,m+1,r,val);
    return binarySearch(arr,l,m-1,val);
    // return std::min((unsigned)m,(unsigned)binarySearch(arr,l,m-1,val)); To get the minumum index
}

int main(){
    int arr[10]{1,1,3,5,8,13,21,34,55,89};
    std::cout<<binarySearch(arr,0,9,3)<<std::endl;
    std::cout<<binarySearch(arr,0,9,2)<<std::endl;
    std::cout<<binarySearch(arr,0,9,21)<<std::endl;
    std::cout<<binarySearch(arr,0,9,55)<<std::endl;
    std::cout<<binarySearch(arr,0,9,89)<<std::endl;
    std::cout<<binarySearch(arr,0,9,1)<<std::endl;
}