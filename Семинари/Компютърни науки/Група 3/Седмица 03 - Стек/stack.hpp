#ifndef STACK_HPP
#define STACK_HPP

template <typename T>
class Stack {
public:
  virtual void push(const T& element) = 0;
  virtual T pop() = 0;
  virtual const T& peek() const = 0;
  virtual bool empty() const = 0;
};

#endif