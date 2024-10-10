#include "week1.h"

#include <iostream>
#include <vector>

/*----------------------------------------------------------------------------*/

void Week1::print(const std::vector<int>& numbers)
{
  for (std::size_t i = 0; i < numbers.size(); ++i) {
    std::cout << numbers[i] << ' ';
  }
  std::cout << '\n';
}

/*----------------------------------------------------------------------------*/


void permute(
  const std::vector<int>& numbers,
  std::vector<bool>& used,
  std::vector<int>& permutation,
  std::size_t permutationSize
)
{
  if (permutationSize == numbers.size()) {
    Week1::print(permutation);
  }
  else for (std::size_t i = 0; i < used.size(); ++i) {
    if (!used[i]) {
      used[i] = true;
      permutation[permutationSize] = numbers[i];
      permute(numbers, used, permutation, permutationSize + 1);
      used[i] = false;
    }
  }
}

void permute(const std::vector<int>& numbers)
{
  std::vector<bool> used(numbers.size(), false);
  std::vector<int> permutation(numbers.size());
  permute(numbers, used, permutation, 0);
}

void Week1::task4()
{
  std::vector<int> numbers = {1, 2, 5, 15};
  permute(numbers);
}
