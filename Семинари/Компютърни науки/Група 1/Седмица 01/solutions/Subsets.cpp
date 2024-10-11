#include <iostream>


void Print(int* arr, size_t size,bool* result){
    std::cout<<"{ ";
    bool printed=false;
    for(size_t i = 0; i<size; i++){
        if(result[i]){
            if(printed)std::cout<<", ";
            std::cout<<arr[i]<<" ";
            printed=true;
        }
    }
    std::cout<<"}\n";
}

void GenerateSubsets(int* arr, size_t size, bool* result, size_t index){
    if(index >= size)return Print(arr,size, result);

    result[index] = false;
    GenerateSubsets(arr, size, result, index+1);
    
    result[index] = true;
    GenerateSubsets(arr, size, result, index+1);

}


void Subsets(int* arr, size_t size){
    bool* mask = new bool[size]{false,};
    GenerateSubsets(arr,size,mask, 0);
    delete[] mask;
}


int main(){
    int arr[4]{1,2,3,4};
    Subsets(arr,4);
}