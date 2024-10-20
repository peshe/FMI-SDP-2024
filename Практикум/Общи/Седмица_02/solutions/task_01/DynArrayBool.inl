#ifndef DYN_ARRAY_BOOL
#define DYN_ARRAY_BOOL

template<class Allocator>
class DynArray<bool, Allocator> {
private:
    static const int BYTE_SIZE = 8;
public:
////
// Class life-cycle members

    // Ctor that sets the initial capacity
    explicit DynArray(size_t initialCapacity = 16);

    // copy ctor
    DynArray(const DynArray &other);

    // assignment operator
    DynArray &operator=(const DynArray &other);

    // A constructor, that creates an array as a copy.
    template<class OtherType, class __>
    DynArray(const DynArray<OtherType, __> &other);

    // Assignment operator.
    template<class OtherType, class __>
    DynArray<bool, Allocator> &operator=(const DynArray<OtherType, __> &other);

    // dtor
    ~DynArray();

////
// Move semantics
    // Move ctor
    // Should be the same
    DynArray(DynArray &&other);

    // Move assignment
    // Should be the same
    DynArray &operator=(DynArray &&other);

////
// Addition, removal and search of elements

    // Appends an array to the current.
    template<class OtherType, class __>
    DynArray<bool, Allocator> &operator+=(const DynArray<OtherType, __> &other);

    // Appends an element at the end of the array.
    DynArray<bool, Allocator> &operator+=(bool data);

    void append(bool elem);

    // Removes an element at given position
    void remove(size_t index);

    // Returns a copy of the element at a given position.
    bool get(size_t index) const;

    // Removes all elements in the array.
    void clear();

////
// Information methods
    // the number of elements in the array
    // Should be the same
    size_t getSize() const;

    // the actual allocated size of the array
    // Should be the same
    size_t getCapacity() const;

    // checks if there are elements in the array
    // Should be the same
    bool isEmpty() const;


////
// Access operators and iterators

    // An indexing operators
    const bool &operator[](size_t index) const;

    bool &operator[](size_t index);

// TODO: Add iterator
private:
    char *data;
    size_t size;
    size_t capacity;
    Allocator allocator;

private:
    // Calculates the size in bytes needed for n boolean values
    size_t getByteCount(size_t n) const;

    // Calculates the byte position for a given position
    size_t getBytePosition(size_t position) const;

    // Calculates the bit position in a byte for a given position in the array
    size_t getBitPosition(size_t position) const;

    // Sets the bit value at given position in char c
    void setBit(char &c, int position, bool value);

    // Gets the bit at position in a given char
    bool getBit(char c, int position) const;

    // ensures there are enough space for given number of elements
    // Should be the same
    void ensureSize(size_t size);

    // changes the actual allocated space to the given number of elements
    void resize(size_t newCapacity);
};


// ///////////////
// Implementations
// ///////////////
template<class Allocator>
size_t DynArray<bool, Allocator>::getByteCount(size_t n) const {
    if (n % BYTE_SIZE == 0) {
        return n / BYTE_SIZE;
    }
    return n / BYTE_SIZE + 1;
}

template<class Allocator>
size_t DynArray<bool, Allocator>::getBytePosition(size_t position) const {
    return position / BYTE_SIZE;
}

template<class Allocator>
size_t DynArray<bool, Allocator>::getBitPosition(size_t position) const {
    return position % BYTE_SIZE;
}

template<class Allocator>
void DynArray<bool, Allocator>::setBit(char &c, int position, bool value) {
    if (value)
        c |= 1 << position;
    else
        c &= ~(1 << position);
}

template<class Allocator>
bool DynArray<bool, Allocator>::getBit(char c, int position) const {
    return c >> position & 1;
}

template<class Allocator>
inline DynArray<bool, Allocator>::DynArray(size_t initialCapacity)
        : data(nullptr), size(0), capacity(initialCapacity) {
    // Ensure object correctness with an exception
    if (initialCapacity <= 0) {
        throw std::invalid_argument("Illegal initial size");
    }

    // If the memory can not be allocated an exception will be thrown
    data = allocator.allocArr(getByteCount(capacity));
}

template<class Allocator>
inline DynArray<bool, Allocator>::~DynArray() {
    clear();
    allocator.printStatistics();
}

template<class Allocator>
inline DynArray<bool, Allocator>::DynArray(const DynArray &other)
        : data(nullptr), size(other.getSize()), capacity(other.getCapacity()) {
    capacity = capacity ? capacity : 1;
    data = allocator.allocArr(getByteCount(capacity));

    try {
        for (size_t i = 0; i < getByteCount(size); ++i)
            data[i] = other.data[i];
    }
    catch (...) {
        allocator.freeArr(data);
    }
}

template<class Allocator>
inline DynArray<bool, Allocator> &DynArray<bool, Allocator>::operator=(const DynArray<bool, Allocator> &other) {
    if (this != &other) {
        // eventually no reallocation is done
        if (capacity < other.getSize()) {
            clear();
            ensureSize(other.getCapacity());
        }
        for (std::size_t i = 0; i < getByteCount(other.size); ++i) {
            data[i] = other[i];
        }
    }
    return *this;
}

template<class Allocator>
template<class OtherType, class __>
inline DynArray<bool, Allocator>::DynArray(const DynArray<OtherType, __> &other)
        : data(nullptr), size(other.getSize()), capacity(other.getCapacity()) {
    throw "Not implemented";
    // TODO: Implement
}

template<class Allocator>
template<class OtherType, class __>
inline DynArray<bool, Allocator> &DynArray<bool, Allocator>::operator=(const DynArray<OtherType, __> &other) {
    throw "Not implemented";
    // TODO: Implement
}

// In that case we do not need function to append vector of the same type
template<class Allocator>
template<class OtherType, class __>
inline DynArray<bool, Allocator> &DynArray<bool, Allocator>::operator+=(const DynArray<OtherType, __> &other) {
    throw "Not implemented";
    // TODO: Implement
}


// In that case we do not need function to append element of different type
template<class Allocator>
inline DynArray<bool, Allocator> &DynArray<bool, Allocator>::operator+=(bool elem) {
    append(elem);
    return *this;
}


template<class Allocator>
inline void DynArray<bool, Allocator>::append(bool elem) {
    ensureSize(size + 1);
    setBit(data[getBytePosition(size)], getBitPosition(size), elem);
    ++size;
}

template<class Allocator>
inline size_t DynArray<bool, Allocator>::getSize() const {
    return size;
}


template<class Allocator>
inline size_t DynArray<bool, Allocator>::getCapacity() const {
    return capacity;
}


template<class Allocator>
inline bool DynArray<bool, Allocator>::isEmpty() const {
    return size == 0;
}

template<class Allocator>
inline void DynArray<bool, Allocator>::clear() {
    allocator.freeArr(data);
    data = nullptr;
    capacity = size = 0;
}


template<class Allocator>
inline bool DynArray<bool, Allocator>::get(size_t index) const {
    if (index < size) {
        return getBit(data[getBytePosition(index)], getBitPosition(index));
    }

    // In this implementation the method is designed to return
    //default-constructed element in case of out-of-range access
    return bool();
}


template<class Allocator>
inline void DynArray<bool, Allocator>::remove(size_t index) {
    // As this is destructive operation, here we can not ignore out-of-range access
    if (index >= size) {
        throw std::invalid_argument("Illegal index");
    }

    for (size_t i = index; i < size - 1; ++i) {
        setBit(data[getBytePosition(i)], getBitPosition(i),
               getBit(data[getBytePosition(i + 1)], getBitPosition(i + 1)));
    }
    --size;
}

template<class Allocator>
inline const bool &DynArray<bool, Allocator>::operator[](size_t index) const {
    if (index < size) return getBit(data[getBytePosition(index)], getBitPosition(index));
    throw std::invalid_argument("Illegal index");
}


template<class Allocator>
inline bool &DynArray<bool, Allocator>::operator[](size_t index) {
    if (index < size) return getBit(data[getBytePosition(index)], getBitPosition(index));
    throw std::invalid_argument("Illegal index");
}


template<class Allocator>
inline void DynArray<bool, Allocator>::ensureSize(size_t size) {
    // As it is internal helper, assert is the better way to check.
    assert(!data || capacity != 0);

    size_t newSize = data ? capacity : 1;

    while (newSize < size) {
        newSize *= 2;
    }

    // Note that in case of same or smaller size nothing is changed
    if (newSize != capacity) {
        resize(newSize);
    }
}

template<class Allocator>
inline void DynArray<bool, Allocator>::resize(size_t newCapacity) {
    char *newData = allocator.allocArr(getByteCount(newCapacity));

    try {
        for (size_t i = 0; i < getByteCount(this->size) && i < getByteCount(newCapacity); ++i) {
            newData[i] = data[i];
        }
    }
    catch (...) {
        allocator.freeArr(newData);
        throw;
    }

    allocator.freeArr(data);
    data = newData;
    capacity = newCapacity;
    size = size < capacity ? size : capacity;
}


template<class Allocator>
inline DynArray<bool, Allocator> operator+(const DynArray<bool, Allocator> &array, const bool &data) {
    return DynArray<bool, Allocator>(array) += data;
}


template<class OtherType, class Allocator1, class Allocator2>
inline DynArray<bool, Allocator1>
operator+(const DynArray<bool, Allocator1> &array, const DynArray<OtherType, Allocator2> &other) {
    return DynArray<bool, Allocator1>(array) += other;
}

#endif