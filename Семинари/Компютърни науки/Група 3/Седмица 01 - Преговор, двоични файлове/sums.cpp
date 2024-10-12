#include <cmath>
#include <cstddef>
#include <iostream>
#include <optional>
#include <string>
#include <vector>

int sum(std::vector<int> arr, std::vector<int> indices) {
  int sum = 0;
  for (int i = 0; i < indices.size(); ++i) {
    sum += arr[indices[i]];
  }

  return sum;
}

std::optional<int> subset_sum_helper(const std::vector<int> &arr,
                                     std::vector<int> &first_indices,
                                     std::vector<int> &second_indices,
                                     int current) {
  if (current == arr.size()) {
    int first_sum = sum(arr, first_indices);
    int second_sum = sum(arr, second_indices);

    if (first_sum == second_sum) {
      return first_sum;
    }

    return {};
  }

  first_indices.push_back(current);

  std::optional<int> sum_when_added_to_first =
      subset_sum_helper(arr, first_indices, second_indices, current + 1);
  if (sum_when_added_to_first.has_value()) {
    return sum_when_added_to_first;
  }

  first_indices.pop_back();
  second_indices.push_back(current);

  std::optional<int> sum_when_added_to_second =
      subset_sum_helper(arr, first_indices, second_indices, current + 1);
  if (sum_when_added_to_second.has_value()) {
    return sum_when_added_to_second;
  }

  second_indices.pop_back();

  return {};
}

std::optional<int> subset_sum(const std::vector<int> &arr) {
  std::vector<int> first_indices;
  std::vector<int> second_indices;
  return subset_sum_helper(arr, first_indices, second_indices, 0);
}

int main() {
  std::optional<int> s1 = subset_sum({1, 5, 11, 5});
  std::optional<int> s2 = subset_sum({1, 3, 5, 11});

  std::cout << (s1.has_value() ? std::to_string(s1.value()) : "false") << '\n';
  std::cout << (s2.has_value() ? std::to_string(s2.value()) : "false") << '\n';
  return 0;
}