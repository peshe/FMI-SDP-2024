
template <class DataType>
inline DataType StaticQueue<DataType>::dequeue()
{
    const DataType& res = first();
    begin = (begin + 1) % size;
    return res;
}

template <class DataType>
inline const DataType& StaticQueue<DataType>::first() const
{
    if (!isEmpty()) return data[begin];
    throw std::underflow_error("Empty queue");
}

template <class DataType>
inline void StaticQueue<DataType>::enqueue(const DataType& elem)
{
    if (!isFull()) {
        data[end] = elem;
        end = (end + 1) % size;
    }
    else throw std::overflow_error("Queue is full");
}

template <class DataType>
inline bool StaticQueue<DataType>::isEmpty() const
{
    return begin == end;
}

template <class DataType>
inline bool StaticQueue<DataType>::isFull() const
{
    return (end + 1) % size == begin;
}

template <class DataType>
inline StaticQueue<DataType>::StaticQueue(const StaticQueue<DataType>& rhs)
    : data(new DataType[rhs.size])
    , begin(0)
    , end(0)
    , size(rhs.size)
{
    for (size_t pos = rhs.begin; pos != rhs.end; pos = (pos + 1) % size)
        enqueue(rhs.data[pos]);
}

//Note! Only weak exception safety is guaranteed
template <class DataType>
inline StaticQueue<DataType>& StaticQueue<DataType>::operator=(const StaticQueue<DataType>& rhs)
{
    if (this != &rhs) {
        begin = end = 0;
        for (size_t pos = rhs.begin; pos != rhs.end; pos = (pos + 1) % size)
            enqueue(rhs.data[pos]);
    }
    return *this;
}
