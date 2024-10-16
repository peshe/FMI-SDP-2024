#include <iostream>

unsigned int factorial(unsigned int n)
{
  if (n == 0)
    return 1;

  return n * factorial(n - 1);
}

int main()
{
  int n;
  std::cin >> n;
  if (!std::cin)
  {
    std::cerr << "error: input failed" << std::endl;
    return 1;
  }
  if (n < 0)
  {
    std::cerr << "error: input should be a natural number" << std::endl;
    return 2;
  }

  std::cout << factorial(n);
  return 0;
}