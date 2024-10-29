#include <stdexcept>
#include "Bitset.h"

BitSet::BitSet(){m_capacity = 0; m_size = 0;}

BitSet::BitSet(size_t size):m_data((size+7) >> 3, 0){
    m_capacity = m_data.size() << 3;
    this->m_size = size;
};

void BitSet::setBit(bool b,size_t pos){
    size_t bIndex = pos >> 3;
    uint8_t bPos = pos & 7;
    uint8_t mask = 1 << bPos;
    m_data[bIndex] = (m_data[bIndex] & (~mask)) | (b << bPos);
}

bool BitSet::getBit(size_t pos) const
{
    return m_data[pos>>3] & (1<<(pos&7));
}

void BitSet::push_back(bool val){
    if(m_size >= (m_data.size() << 3)){
        m_data.push_back(0);
    }
    setBit(val,m_size++);
        
};

BitSet::Proxy BitSet::operator[](size_t index){
    if(index >= m_size)
        throw std::invalid_argument("Index out of range");
    return BitSet::Proxy(m_data.data()+(index>>3),index & 7);
}

bool BitSet::operator[](size_t index)const{
    return getBit(index);
}
   

void BitSet::pop_back(){
    m_size--;
    if(m_size < ((m_data.size() - 1) << 3)){
        m_data.pop_back();
    }
}

size_t BitSet::size()const{
    return m_size;
}
void BitSet::flip(size_t pos){
    if(pos>=m_size){
        throw std::invalid_argument("Index out of range");
    }
    size_t bIndex = pos>>3;
    uint8_t bPos = pos & 7;
    m_data[bIndex] = m_data[bIndex] ^ (1<<bPos);
}

BitSet::Iterator BitSet::begin(){
    auto it = BitSet::Iterator(*this, 0);
    return it;
}

BitSet::Iterator BitSet::end()
{
    return BitSet::Iterator(*this, m_size );
}
// void flip();
// bool all()const;
// bool any()const;
// bool none()const;

