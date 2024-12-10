#include "BST.hpp"

#include <cassert>


template <typename T>
class Set
{
public:
    virtual bool contains(const T& data) const = 0;
    virtual void add(const T& data) = 0;
    virtual void remove(const T& data) = 0;
    virtual int size() const = 0;
    virtual bool empty() const = 0;
};


template <typename T>
class TreeSet : public Set<T>
{
public:
    virtual bool contains(const T& data) const;
    virtual void add(const T& data);
    virtual void remove(const T& data);
    virtual int size() const;
    virtual bool empty() const;

private:
    fmi::sdp::BST<T> container;
};


template <typename T>
/*virtual*/ bool TreeSet<T>::contains(const T& data) const {
    return container.find(data);
}

template <typename T>
/*virtual*/ void TreeSet<T>::add(const T& data) {
    if (!contains(data)) {
        container.insert(data);
    }
}

template <typename T>
/*virtual*/ void TreeSet<T>::remove(const T& data) {
    container.remove(data);
    assert(!contains(data));
}

template <typename T>
/*virtual*/ int TreeSet<T>::size() const {
    return container.getSize();
}

template <typename T>
/*virtual*/ bool TreeSet<T>::empty() const {
    return size() == 0;
}
