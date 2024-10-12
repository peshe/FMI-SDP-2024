#include <iostream>
#include <vector>

void print(const std::vector<int> &list) {
    std::cout << "{\t";
    for (std::size_t i = 0; i < list.size(); ++i) {
        std::cout << list[i] << '\t';
    }
    std::cout << "}\n";
}

void combine(
  const std::vector<int> &set,
  std::size_t k,
  std::size_t nextI,
  std::vector<int> &combination,
  std::size_t combinationSize
) {
  if (combinationSize == k) {
    print(combination);
  }
  else for (std::size_t i = nextI; i < set.size(); ++i) {
    combination[combinationSize] = set[i];
    combine(set, k, i + 1, combination, combinationSize + 1);
  }
}

void combine(const std::vector<int>& set, std::size_t k)
{
  if (k > set.size()) {
    return;
  }

  std::vector<int> combination(k);
  combine(set, k, 0, combination, 0);
}

int main() {
  std::vector<int> sampleSet = {1, 8, 3};
  combine(sampleSet, 2);
  
  return 0;
}
