#include <iostream>

void PrintArr(char* arr, int size){
    for(int i=0;i<size;i++)
        std::cout<<arr[i]<<" ";
        std::cout<<std::endl;

}

void Permutations(char* arr,int size, int index){
    if(index >= size)
        PrintArr(arr,size);

    for(int i = index; i<size;i++){
        std::swap(arr[i], arr[index]);
        Permutations(arr,size, index+1);
        std::swap(arr[i], arr[index]);
    }
}


int main(){
    char arr[20] = {'A','B','C','D','\0'};
    Permutations(arr,4,0);

}