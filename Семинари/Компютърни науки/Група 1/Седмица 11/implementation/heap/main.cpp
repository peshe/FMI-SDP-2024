#include <iostream>
#include <vector>
#include "heap.h"

using namespace std;

int main(){
    srand(time(NULL)*7543+1234);
    vector<int> numbers;
    for(int i = 0; i< 30; i++)
        numbers.push_back(rand()%100);
    Heap h(numbers);
        // h.insert(rand()%100);
    while(!h.empty()){
        cout<<h.extractMin()<<' ';
    }
}