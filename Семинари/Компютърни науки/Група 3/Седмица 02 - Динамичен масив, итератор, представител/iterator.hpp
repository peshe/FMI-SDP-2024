#ifndef ITERATOR_HPP
#define ITERATOR_HPP

template <typename T, typename I> class Iterator {
public:
  I &operator++() { return (I&)*this = next(); }

  T &operator*() { return get(); }

  const T &operator*() const { return get(); }

  virtual bool operator!=(const Iterator &other) const = 0;

private:
  virtual I next() const = 0;
  virtual T &get() = 0;
};

#endif