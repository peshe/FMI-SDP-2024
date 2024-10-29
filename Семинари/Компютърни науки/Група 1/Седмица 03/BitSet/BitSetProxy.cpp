#include "BitSet.h"

BitSet::Proxy::Proxy(uint8_t* el, uint8_t pos):m_el(el), m_pos(pos){};

BitSet::Proxy::operator bool()const {
        return (*m_el >> m_pos) & 1;
}

bool BitSet::Proxy::operator=(bool val)
{
    uint8_t mask = 1 << m_pos;
    *m_el = (*m_el & (~mask)) | (val << m_pos);
    return *this;
}
