#include <vector>
#include <iostream>
#include "BST.h"

using namespace std;

int main(){
    BST tree,t2;
    srand(time(nullptr)*7543+12345);
    std::vector<int> numbers{10, 48, 71, 72, 37, 53, 65, 54, 19, 70, 73, 25, 13, 7, 39, 59, 48, 18, 61, 8};
    
    for(int i = 0 ; i< 20 ;i++){
        tree.insert(numbers[i]);
    } 
    // tree.print();
    
    for(BST::Iterator it = tree.begin(); it ; it++){
        cout<<*it<<" ";  
    }
    cout<<endl;
    tree.print();
}