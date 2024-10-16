#include <iostream>

unsigned int fibonacci(unsigned int n)
{
  if (n < 2)
    return n;

  return fibonacci(n - 1) + fibonacci(n - 2);
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

  std::cout << fibonacci(n);
  return 0;
}