#include "week1.h"

#include <iostream>
#include <vector>

/*----------------------------------------------------------------------------*/

void combine(
  const std::vector<int>& numbers,
  std::size_t k,
  std::size_t nextI,
  std::vector<int>& combination,
  std::size_t combinationSize
)
{
  if (combinationSize == k) {
    Week1::print(combination);
  }
  else for (std::size_t i = nextI; i < numbers.size(); ++i) {
    combination[combinationSize] = numbers[i];
    combine(numbers, k, i + 1, combination, combinationSize + 1);
  }
}

void combine(const std::vector<int>& numbers, std::size_t k)
{
  if (k > numbers.size()) {
    return;
  }

  std::vector<int> combination(k);
  combine(numbers, k, 0, combination, 0);
}

void Week1::task6()
{
  std::vector<int> numbers = {1, 2, 5, 15};
  combine(numbers, 2);
}
