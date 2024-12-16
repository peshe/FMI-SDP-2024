#include "heap.h"
size_t Heap::getParent(size_t i) const{ return (i-1)/2; };
size_t Heap::getLeftChild(size_t i) const{ return 2*i+1; };
size_t Heap::getRightChild(size_t i) const{ return 2*i+2; };

void Heap::SoakRecur(size_t i, size_t l)
{
    int Lchild = getLeftChild(i);
    int Rchild = getRightChild(i);
    int smallerChild;
    if(Lchild >= l )return;

    smallerChild = Lchild;
    if(Rchild < l && data[Lchild] > data[Rchild])
        smallerChild = Rchild;
    
    if(data[i] <= data[smallerChild])return;
    std::swap(data[i], data[smallerChild]);
    SoakRecur(smallerChild,l);
};

void Heap::Soak(size_t m) {
    SoakRecur(0,m);
};

void Heap::Heapify(size_t l){
    if(l == 0) return;
    int parent = getParent(l);
    while(parent>=0 && data[parent] > data[l]){
        std::swap(data[parent], data[l]);
        l = parent;
        parent = getParent(l);
    }
};

void Heap::BuildHeap(const std::vector<int>& other){
    for(int i = data.size()/2-1; i>=0;i--)
        SoakRecur(i,data.size());
};  

Heap::Heap(){};

Heap::Heap(size_t size)
    : data(size){};

Heap::Heap(const std::vector<int>& other):data(other){
    BuildHeap(other);
};

int Heap::getMin()const{
    return data[0];
};

int Heap::extractMin(){
    std::swap(data[0],data.back());
    Soak(data.size()-1);
    int temp = data.back();
    data.pop_back();
    return temp;
};

void Heap::insert(int el){
    data.push_back(el);
    Heapify(data.size()-1);
}
bool Heap::empty() const
{
    return data.empty();
};
