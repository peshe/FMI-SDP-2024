#ifndef DYN_ARRAY_BOOL
#define DYN_ARRAY_BOOL

template<class Allocator>
class DynArray<bool, Allocator> {
private:
    static constexpr size_t BYTE_SIZE = 8;
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

    // Checks if an element exists in the array.
    bool contains(bool elem) const;

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

    // indexing operators
    bool operator[](size_t index) const;

    bool &operator[](size_t index);

// TODO: Add iterator

private:
    char *data;
    size_t size;
    size_t capacity;
    Allocator allocator;

private:
    // Calculates the size in bytes needed for n boolean values
    static size_t getByteCount(size_t n);

    // Calculates the byte position for a given position
    static size_t getBytePosition(size_t position);

    // Calculates the bit position in a byte for a given position in the array
    static size_t getBitPosition(size_t position);

    // Sets the bit value at given position in char c
    static void setBit(char &c, size_t position, bool value);

    // No boundary checks - internal use only!
    void set(size_t position, bool value);

    // Gets the bit at position in a given char
    static bool getBit(char c, size_t position);

    // No boundary checks - internal use only!
    bool getUnchecked(size_t position) const;

    // ensures there are enough space for given number of elements
    // Should be the same
    void ensureSize(size_t size);

    // changes the actual allocated space to the given number of elements
    void resize(size_t newCapacity);
};

typedef DynArray<bool, DefaultAllocator<char>> DynArrayBool;


// ///////////////
// Implementations
// ///////////////
template<class Allocator>
// static
inline size_t DynArray<bool, Allocator>::getByteCount(size_t n) {
    return n / BYTE_SIZE + (n % BYTE_SIZE != 0);
}

template<class Allocator>
// static
inline size_t DynArray<bool, Allocator>::getBytePosition(size_t position) {
    return position / BYTE_SIZE;
}

template<class Allocator>
// static
inline size_t DynArray<bool, Allocator>::getBitPosition(size_t position) {
    return position % BYTE_SIZE;
}

template<class Allocator>
// static
inline void DynArray<bool, Allocator>::setBit(char &c, size_t position, bool value) {
    if (value)
        c |= 1 << position;
    else
        c &= ~(1 << position);
}

template<class Allocator>
inline void DynArray<bool, Allocator>::set(size_t position, bool value) {
    setBit(data[getBytePosition(position)], getBitPosition(position), value);
}

template<class Allocator>
// static
inline bool DynArray<bool, Allocator>::getBit(char c, size_t position) {
    return c >> position & 1;
}

template<class Allocator>
inline bool DynArray<bool, Allocator>::getUnchecked(size_t position) const {
    return getBit(data[getBytePosition(position)], getBitPosition(position));
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
        throw;
    }
}

template <class Allocator>
inline DynArray<bool, Allocator>::DynArray(DynArray &&other)
        : data(nullptr), size(other.getSize()), capacity(other.getCapacity()) {
    std::swap(data, other.data);
    allocator.swap(other.allocator);
}

template<class Allocator>
inline DynArray<bool, Allocator> &DynArray<bool, Allocator>::operator=(const DynArray<bool, Allocator> &other) {
    if (this != &other) {
        // eventually no reallocation is done
        if (capacity < other.getSize()) {
            clear();
            ensureSize(other.getCapacity());
        }
        for (size_t i = 0; i < getByteCount(other.size); ++i) {
            data[i] = other[i];
        }
    }
    return *this;
}

template <class Allocator>
inline DynArray<bool, Allocator> &DynArray<bool, Allocator>::operator=(DynArray<bool, Allocator> &&other) {
    if (this != &other) {
        std::swap(data, other.data);
        std::swap(size, other.size);
        std::swap(capacity, other.capacity);
        allocator.swap(other.allocator);
    }
    return *this;
}

template<class Allocator>
template<class OtherType, class __>
inline DynArray<bool, Allocator>::DynArray(const DynArray<OtherType, __> &other)
        : data(nullptr), size(other.getSize()), capacity(other.getCapacity()) {
    capacity = capacity ? capacity : 1;
    data = allocator.allocArr(getByteCount(capacity));
    try {
        for (size_t i = 0; i < size; ++i) {
            set(i, bool(other[i]));
        }
    }
    catch (...) {
        allocator.freeArr(data);
        throw;
    }
}

template<class Allocator>
template<class OtherType, class __>
inline DynArray<bool, Allocator> &DynArray<bool, Allocator>::operator=(const DynArray<OtherType, __> &other) {
    //In that case two objects have different types, so
    //no need to check for self-assignment
    size = other.getSize();
    if (capacity < other.getSize()) {
        clear();
        ensureSize(other.getSize());
    }

    for (size_t i = 0; i < other.getSize(); ++i) {
        set(i, bool(other[i]));
    }

    return *this;
}

// In that case we do not need function to append vector of the same type
template<class Allocator>
template<class OtherType, class __>
inline DynArray<bool, Allocator> &DynArray<bool, Allocator>::operator+=(const DynArray<OtherType, __> &other) {
    ensureSize(size + other.getSize());
    for (size_t i = 0; i < other.getSize(); ++i) {
        set(size + i, bool(other[i]));
    }
    size += other.getSize();
    return *this;
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
    set(size, elem);
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
        return getUnchecked(index);
    }

    // In this implementation the method is designed to return false in case of out-of-range access
    return false;
}


template<class Allocator>
inline void DynArray<bool, Allocator>::remove(size_t index) {
    // As this is destructive operation, here we can not ignore out-of-range access
    if (index >= size) {
        throw std::invalid_argument("Illegal index");
    }

    for (size_t i = index; i < size - 1; ++i) {
        set(i, getUnchecked(i + 1));
    }
    --size;
}

template <class Allocator>
inline bool DynArray<bool, Allocator>::contains(bool elem) const
{
    for (size_t i = 0; i < size; ++i) {
        if (elem == getUnchecked(i)) {
            return true;
        }
    }
    return false;
}

template<class Allocator>
inline bool DynArray<bool, Allocator>::operator[](size_t index) const {
    if (index < size) return getUnchecked(index);
    throw std::invalid_argument("Illegal index");
}


template<class Allocator>
inline bool &DynArray<bool, Allocator>::operator[](size_t index) {
    throw "Not implemented: DynArray<bool, Allocator>::operator[]";
    // Some magic is needed in order to implement this - see `BoolVectorProxy` in
    // https://github.com/peshe/FMI-SDP-2024/blob/926454bdac468089b51f90b7db291400166a84db/%D0%A1%D0%B5%D0%BC%D0%B8%D0%BD%D0%B0%D1%80%D0%B8/%D0%9A%D0%BE%D0%BC%D0%BF%D1%8E%D1%82%D1%8A%D1%80%D0%BD%D0%B8%20%D0%BD%D0%B0%D1%83%D0%BA%D0%B8/%D0%93%D1%80%D1%83%D0%BF%D0%B0%202/Week_03/boolvector.hpp#L10-L24.
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

#endif // DYN_ARRAY_BOOL
