#include "week1.h"

#include <iostream>

/*----------------------------------------------------------------------------*/

template <typename T>
void swap(T* lhs, T* rhs)
{
  T buffer = *lhs;
  *lhs = *rhs;
  *rhs = buffer;
}

template <typename T>
void swap(T& lhs, T& rhs)
{
  T buffer = lhs;
  lhs = rhs;
  rhs = buffer;
}

void Week1::task1()
{
  int a = 0, b = 0;
  std::cout << "Enter two integers:\t";
  std::cin >> a >> b;
  swap(&a, &b);
  std::cout << "Swapped using pointers:\t" << a << " " << b << std::endl;

  std::string c, d;
  std::cout << "Enter two strings:\t";
  std::cin >> c >> d;
  swap(c, d);
  std::cout << "Swapped using references:\t" << c << " " << d << std::endl;
}
