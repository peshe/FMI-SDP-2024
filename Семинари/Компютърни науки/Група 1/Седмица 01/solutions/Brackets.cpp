#include <iostream>

void Brackets(int index, int opened, char* result, int size){
    if(index==size && !opened)std::cout<<result<<std::endl;
    if(index==size)return;

    result[index] = '(';
    Brackets(index+1, opened+1, result,size);
    if(opened){
        result[index] = ')';
        Brackets(index+1, opened - 1, result, size);
    }
}

void GenerateBrackets(int size){
    char *s = new char[size+1];
    s[size] = 0;
    Brackets(0, 0, s, size);
    delete[] s;
}

int main(){
        
    GenerateBrackets(6);
    
}