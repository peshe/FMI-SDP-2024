#include "week1.h"

#include <iostream>
#include <vector>

/*----------------------------------------------------------------------------*/

void vary(
  const std::vector<int>& numbers,
  std::size_t k,
  std::vector<bool>& used,
  std::vector<int>& variation,
  std::size_t variationSize
)
{
  if (variationSize == k) {
    Week1::print(variation);
  }
  else for (std::size_t i = 0; i < used.size(); ++i) {
    if (!used[i]) {
      used[i] = true;
      variation[variationSize] = numbers[i];
      vary(numbers, k, used, variation, variationSize + 1);
      used[i] = false;
    }
  }
}

void vary(const std::vector<int>& numbers, std::size_t k)
{
  if (k > numbers.size()) {
    return;
  }

  std::vector<bool> used(numbers.size(), false);
  std::vector<int> variation(k);
  vary(numbers, k, used, variation, 0);
}

void Week1::task5()
{
  std::vector<int> numbers = {1, 2, 5, 15};
  vary(numbers, 2);
}
