#pragma once

#ifndef HEAP_HEADER
#define HEAP_HEADER

#include <vector>
#include <stddef.h>

class Heap{//Min heap
    private:
    std::vector<int> data;
    size_t getParent(size_t i)const;
    size_t getLeftChild(size_t i)const;
    size_t getRightChild(size_t i)const;
    void SoakRecur(size_t i,size_t l);
    void Soak(size_t m);
    void Heapify(size_t l);
    void BuildHeap(const std::vector<int>& other);
    public:
    Heap();
    Heap(size_t size);
    Heap(const std::vector<int>& other);
    int getMin()const;
    int extractMin();
    void insert(int el);
    bool empty()const;
};

#endif