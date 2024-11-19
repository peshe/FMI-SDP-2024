/******************************************************************
*  Sample code to the course "Data Structures And Algorithms", FMI
*
* An educational class, representing queue doubly linked list
*
* (cc) Petar Armyanov, FMI, 2024
*******************************************************************/
#pragma once

#ifndef _DLLIST_HEADER_INCLUDED_
#define _DLLIST_HEADER_INCLUDED_

#include <iostream>
#include <stdexcept>
#include <cassert>
#include <initializer_list>

template <class T>
class DLList
{
    struct Node
    {
        Node(const T& val = T{}, Node* prev = nullptr, Node* next = nullptr);
        T data;
        Node * prev, * next;
    };

public:
    // Конструктори
    DLList();
    DLList(std::initializer_list<T> values);
    DLList(const DLList& other);
    DLList(DLList&& other) noexcept;
    DLList& operator=(const DLList&rhs);
    DLList& operator=(DLList&& other) noexcept;
    ~DLList() noexcept;

    // Достъп до елементи в списъка
    T& front();
    T& back();
    T& at(size_t pos);

    class iterator;

    iterator begin();
    iterator begin() const;
    iterator end();
    iterator end() const;
    iterator get_at(size_t pos);

    // Информативни методи
    bool is_empty() const;
    size_t length() const;

    // Добавяне на елементи
    void push_front(const T& val);
    void push_end(const T& val);
    void push_at(size_t pos, const T& val);
    void push_after(iterator it, const T& val);
    void push_before(iterator it, const T& val);

    // Премахване на елементи.
    void remove_front();
    void remove_end();
    T remove_at(size_t pos);
    void remove_at(iterator it);
    void remove_after(iterator it);
    void remove_before(iterator it);

    // Алгоритми
    void reverse();

private:
    Node sentinel;
    size_t size;

    void copy(const DLList& other);
    void free();

#ifndef NDEBUG
public:
    bool isListValid() const;
    void print() const;
#endif
};

template<class T>
class DLList<T>::iterator
{
    friend class DLList<T>;

    DLList<T>::Node* ptr;
    const DLList<T>& owner;

    iterator(DLList<T>::Node* ptr, const DLList<T>& creator)
        : ptr(ptr), owner(creator) {}

public:
    bool valid() const { return ptr; }
    operator bool() const { return ptr && ptr != &(owner.sentinel); }

    T& operator*() { return ptr->data; }
    T* operator->() { return &ptr->data; }
    const T& operator*() const { return ptr->data; }
    const T* operator->() const { return &ptr->data; }

    iterator& operator++()
    {
        if(valid()) ptr = ptr->next;
        return *this;
    }
    iterator operator++(int)
    {
        iterator res = *this;
        ++*this;
        return res;
    }

    iterator& operator--()
    {
        if (valid()) ptr = ptr->prev;
        return *this;
    }
    iterator operator--(int)
    {
        iterator res = *this;
        ++*this;
        return res;
    }

    bool operator == (const iterator& rhs) const
    { return ptr == rhs.ptr; }
    bool operator != (const iterator& rhs) const
    { return !(*this == rhs); }
};

template<class T>
inline DLList<T>::Node::Node(const T& val, Node* prev, Node* next)
    :data(val), prev(prev), next(next)
{}

template<class T>
inline void DLList<T>::copy(const DLList<T>& other)
{
    Node * iter = &sentinel;
    Node * curr = other.sentinel.next;
    while (curr != &other.sentinel) {
        iter->next = new Node(curr->data, iter);
        iter = iter->next;
        curr = curr->next;
    }
    size = other.size;
    sentinel.prev = size ? iter : &sentinel;
    iter->next = &sentinel;
}

template<class T>
inline void DLList<T>::free()
{
    while(&sentinel != sentinel.next) {
        Node* detach = sentinel.next;
        sentinel.next = detach->next;
        delete detach;
    }
    sentinel.prev = &sentinel;
    size = 0;
}

template<class T>
inline DLList<T>::DLList()
    :sentinel{ {}, &sentinel, &sentinel }, size(0) {}

template<class T>
inline DLList<T>::DLList(std::initializer_list<T> values)
    :DLList()
{
    for (const T& val : values) {
        push_end(val);
    }
}

template<class T>
inline DLList<T>::DLList(const DLList& other)
    :DLList()
{
    copy(other);
}

template<class T>
inline DLList<T>::DLList(DLList&& other) noexcept
    :DLList()
{
    if (!other.is_empty()) {
        sentinel = other.sentinel;
        other.sentinel = { {}, &other.sentinel, &other.sentinel };
        sentinel.next->prev = sentinel.prev->next = &sentinel;
        std::swap(size, other.size);
    }
}

template<class T>
inline DLList<T>& DLList<T>::operator=(const DLList<T>& other)
{
    if (this != &other) {
        *this = DLList(other);
    }

    return *this;
}

template<class T>
inline DLList<T>& DLList<T>::operator=(DLList<T>&& other) noexcept
{
    if (this != &other) {
        Node otherSent = other.sentinel;
        other.sentinel = size ? sentinel : Node{ {}, &other.sentinel, &other.sentinel };
        sentinel = other.size ? otherSent : Node{ {}, &sentinel, &sentinel };
        sentinel.next->prev = sentinel.prev->next = &sentinel;
        other.sentinel.next->prev = other.sentinel.prev->next = &other.sentinel;
        std::swap(size, other.size);
    }
    return *this;
}

template<class T>
inline DLList<T>::~DLList() noexcept
{
    free();
}

template<class T>
inline T& DLList<T>::at(size_t pos)
{
    return *get_at(pos);
}

template<class T>
inline T& DLList<T>::front() 
{
    return at(0);
}

template< class T>
inline T& DLList<T>::back() 
{
    return at(size - 1);
}

template<class T>
inline size_t DLList<T>::length() const
{
    return size;
}

template<class T>
inline typename DLList<T>::iterator DLList<T>::begin()
{
    return iterator(sentinel.next, *this);
}

template<class T>
inline typename DLList<T>::iterator DLList<T>::begin() const
{
    return iterator(sentinel.next, *this);
}

template<class T>
inline typename DLList<T>::iterator DLList<T>::end()
{
    return iterator(&sentinel, *this);
}

template<class T>
inline typename DLList<T>::iterator DLList<T>::end() const
{
    return iterator(const_cast<Node*>(&sentinel), *this);
}

template<class T>
inline typename DLList<T>::iterator DLList<T>::get_at(size_t pos)
{
    if (pos >= size) {
        throw std::invalid_argument("Index out of bounds\n");
    }

    Node* it = &sentinel;
    if (pos < size / 2) {
        for (it = it->next; pos > 0; --pos, it = it->next)
            ;
    }
    else {
        for (it = it->prev; pos < size-1; ++pos, it = it->prev)
            ;
    }
    return iterator(it, *this);
}

template<class T>
inline void DLList<T>::push_at(size_t pos, const T & val)
{
    if (pos > size) {
        throw std::invalid_argument("Index out of bounds\n");
    }
    if (!pos) {
        push_front(val);
    }
    else if (pos == size) {
        push_end(val);
    }
    else {
        push_before(get_at(pos), val);
    }
}

template<class T>
inline void DLList<T>::push_after(iterator it, const T& val)
{
    if (&it.owner != this) {
        throw std::invalid_argument("Iterator from different list!\n");
    }
    if (!it.valid()) {
        throw std::invalid_argument("Invalid iterator passed!\n");
    }
    Node* node = new Node(val, it.ptr, it.ptr->next);
    node->prev->next = node;
    node->next->prev = node;
    ++size;
}

template<class T>
inline void DLList<T>::push_before(iterator it, const T& val)
{
    if (&it.owner != this) {
        throw std::invalid_argument("Iterator from different list!\n");
    }
    if (!it.valid()) {
        throw std::invalid_argument("Invalid iterator passed!\n");
    }
    Node* node = new Node(val, it.ptr->prev, it.ptr);
    node->prev->next = node;
    node->next->prev = node;
    ++size;
}

template<class T>
inline void DLList<T>::push_front(const T & val)
{
    push_after(end(), val);
}

template<class T>
inline void DLList<T>::push_end(const T & val)
{
    push_before(end(), val);
}

template<class T>
inline void DLList<T>::remove_after(iterator it)
{
    if (&it.owner != this) {
        throw std::invalid_argument("Iterator from different list!\n");
    }
    if (!it) {
        throw std::invalid_argument("Bad iterator!\n");
    }
    if (it.ptr->next == &it.owner.sentinel) {
        throw std::invalid_argument("No element after!\n");
    }

    Node* toDel = it.ptr->next;
    toDel->next->prev = toDel->prev;
    toDel->prev->next = toDel->next;
    delete toDel;
    --size;
}

template<class T>
inline void DLList<T>::remove_before(iterator it)
{
    if (&it.owner != this) {
        throw std::invalid_argument("Iterator from different list!\n");
    }
    if (!it) {
        throw std::invalid_argument("Bad iterator!\n");
    }
    if (it.ptr->prev == &it.owner.sentinel) {
        throw std::invalid_argument("No element before!\n");
    }

    Node* toDel = it.ptr->prev;
    toDel->next->prev = toDel->prev;
    toDel->prev->next = toDel->next;
    delete toDel;
    --size;
}

template<class T>
inline void DLList<T>::remove_at(iterator it)
{
    if (&it.owner != this) {
        throw std::invalid_argument("Iterator from different list!\n");
    }
    if (!it) {
        throw std::invalid_argument("Bad iterator!\n");
    }

    Node* toDel = it.ptr;
    toDel->next->prev = toDel->prev;
    toDel->prev->next = toDel->next;
    delete toDel;
    --size;
}

template<class T>
inline T DLList<T>::remove_at(size_t pos)
{
    if (is_empty() || pos >= size) {
        throw std::invalid_argument("Index out of bounds\n");
    }
    iterator it = get_at(pos);
    T store = *it;
    remove_at(it);
    return store;
}

template<class T>
inline void DLList<T>::remove_front()
{
    remove_at(0);
}

template<class T>
inline void DLList<T>::remove_end()
{
    remove_at(size - 1);
}

template<class T>
inline bool DLList<T>::is_empty() const
{
    return size == 0;
}

template<class T>
inline void DLList<T>::reverse()
{
    if (size < 2) {
        return;
    }
    for (Node* it = sentinel.next; it != &sentinel; it = it->prev){
        std::swap(it->next, it->prev);
    }
    std::swap(sentinel.prev, sentinel.next);
}

#ifndef NDEBUG
template<class T>
inline bool DLList<T>::isListValid() const
{
    const Node* it = sentinel.next;
    int cnt = 0;
    while (it != &sentinel) {
        if (it->prev->next != it) return false;
        if (it->next->prev != it) return false;
        it = it->next;
        ++cnt;
    }
    if (cnt != size) return false;

    it = sentinel.prev;
    cnt = 0;
    while (it != &sentinel) {
        if (it->prev->next != it) return false;
        if (it->next->prev != it) return false;
        it = it->prev;
        ++cnt;
    }
    if (cnt != size) return false;

    return true;
}

template<class T>
inline void DLList<T>::print() const
{
    for (const T& elem : *this) {
        std::cout << elem << " ";
    }
    std::cout << "\n";
}
#endif //NDEBUG

#endif //_DLLIST_HEADER_INCLUDED_
