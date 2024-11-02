#include <cstddef>
#include <iostream>
#include <type_traits>
#include "iterator.hpp"

template <typename T>
class Proxy {
public:
  virtual operator T&() = 0;
  virtual operator const T&() const = 0;
}; 

template <typename T>
class IdentityProxy : Proxy<T> {
public:
  IdentityProxy(T* data, std::size_t index) : value(data[index]) {}

  operator T&() {
    return value;
  }
  operator const T&() const {
    return value;
  }

private:
  T& value;
};

template <typename T, typename I> class Array {
public:
  virtual T &operator[](int index) = 0;
  virtual const T &operator[](int index) const = 0;
  virtual void push_back(const T &element) = 0;
  virtual I begin() const = 0;
  virtual I end() const = 0;
};

template <typename T, typename I, typename P = IdentityProxy<T>> class DynamicArray : public Array<T, I> {
public:
  explicit DynamicArray(std::size_t capacity = 0)
      : capacity(capacity), size(0), data(new T[capacity]) {}

  DynamicArray(const DynamicArray &other)
      : capacity(other.capacity), size(other.size),
        data(new T[other.capacity]) {
    for (std::size_t i = 0; i < other.size; ++i) {
      data[i] = other.data[i];
    }
  }

  ~DynamicArray() { delete[] data; }

  DynamicArray<T, I, P> &operator=(const DynamicArray &other) {
    DynamicArray<T, I, P> copy(other);
    swap(copy);

    return *this;
  }

  void swap(DynamicArray<T, I, P> &other) {
    std::swap(capacity, other.capacity);
    std::swap(size, other.size);
    std::swap(data, other.data);
  }

  DynamicArray(DynamicArray &&other)
      : data(std::move(other.data)), size(other.size),
        capacity(other.capacity) {}

  DynamicArray<T, I, P> operator=(DynamicArray &&other) {
    DynamicArray<T, I, P> copy(std::move(other));
    swap(copy);

    return *this;
  }

  T &operator[](int index) { 
    return P(data, index); 
  }
  
  const T &operator[](int index) const { 
    return P(data, index); 
  }

  void push_back(const T &element) {
    if (size == capacity) {
      resize();
    }

    data[size] = element;
    ++size;
  }

  I begin() const { return I(data, 0); }
  I end() const { return I(data, size); }

private:
  std::size_t capacity, size;
  T *data;

  void resize() {
    if (capacity == 0) {
      capacity = 1;
    }

    capacity *= 2;
    T *new_data = new T[capacity];
    for (std::size_t i = 0; i < size; ++i) {
      new_data[i] = data[i];
    }

    delete[] data;
    data = new_data;
  }
};

template <typename T, typename P = IdentityProxy<T>> class ForwardIterator : public Iterator<T, ForwardIterator<T, P>> {
public:
  ForwardIterator(T *data, std::size_t index) : data(data), index(index) {}

  bool operator!=(const Iterator<T, ForwardIterator<T, P>> &other) const final {
    const ForwardIterator<T, P>& other_forward = static_cast<const ForwardIterator<T, P>&>(other);
    return data + index != other_forward.data + other_forward.index;
  }

private:
  T *data;
  std::size_t index;

  ForwardIterator<T, P> next() const { return ForwardIterator(data, index + 1); }

  T &get() { return P(data, index); }
};

template <typename T>
class LoggingProxy : public Proxy<T> {
public:
  LoggingProxy(T* data, std::size_t index) : data(data), index(index) {}

  operator T&() {
    std::cout << "[INFO]: Position: " << index << ", value: " << data[index] << '\n';

    return data[index];
  }

  operator const T&() const {
    std::cout << "[INFO]: Position: " << index << ", value: " << data[index] << '\n';

    return data[index];
  }

private:
  T* data;
  std::size_t index;
};

int main() {
  DynamicArray<int, ForwardIterator<int>> arr;

  for (std::size_t i = 0; i < 5; ++i) {
    arr.push_back(i);
  }

  for (int element : arr) {
    std::cout << element << ' ';
  }

  std::cout << '\n';
  return 0;
}