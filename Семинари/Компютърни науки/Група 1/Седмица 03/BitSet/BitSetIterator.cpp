#include "BitSet.h"
using BitIt = BitSet::Iterator;

BitIt::Iterator(BitSet& bitset, size_t pos):owner(bitset), index(pos){}
BitIt::reference BitIt::operator*(){
    return owner[index];
};
BitIt& BitIt::operator++(){
    index++;
    return *this;
};
BitIt BitIt::operator++(int){
    BitIt temp(owner, index);
    index++;
    return temp;
};
BitIt& BitIt::operator--(){
    index--;
    return *this;
};
BitIt BitIt::operator--(int){
    Iterator temp(owner, index);
    index--;
    return temp;
};
BitIt& BitIt::operator+=(difference_type n){
    index+=n;
    return *this;
};
BitIt BitIt::operator+(difference_type n) const{
    Iterator temp(owner, index+n);
    return temp;
};
BitIt& BitIt::operator-=(difference_type n){
    index-=n;
    return *this;
};
BitIt BitIt::operator-(difference_type n) const{
    Iterator temp(owner, index-n);
    return temp;
};
BitIt::difference_type BitIt::operator-(const Iterator& other) const{
    return other.index - this->index;
};
bool BitIt::operator==(const Iterator& other) const{
    return &other.owner == &owner && index == other.index;
};
bool BitIt::operator!=(const Iterator& other) const{   
    return !((*this) == other);
};
bool BitIt::operator<(const Iterator& other) const{
    
    return &other.owner == &owner && index < other.index;
};
bool BitIt::operator>(const Iterator& other) const{
    return &other.owner == &owner && index > other.index;
};
bool BitIt::operator<=(const Iterator& other) const{
    return !(*this>other);
}; 
bool BitIt::operator>=(const Iterator& other) const{
    return !(*this<other);
};
BitIt::reference BitIt::operator[](difference_type n) const {
    return *(*this + n);
}