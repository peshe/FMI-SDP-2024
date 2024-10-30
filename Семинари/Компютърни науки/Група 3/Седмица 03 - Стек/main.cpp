#include <iostream>
#include <vector>
#include "linked_stack.hpp"

struct State {
  std::size_t begin, end;
  bool merge;

  State(std::size_t begin, std::size_t end, bool merge = false) : begin(begin), end(end), merge(merge) {}
};

template <typename T>
void merge(std::vector<T>& arr, std::size_t begin, std::size_t middle, std::size_t end) {
  std::vector<T> first, second;
  std::size_t first_size = middle - begin + 1;
  std::size_t second_size = end - middle;

  for (std::size_t i = 0; i < first_size; ++i) {
    first.push_back(arr[begin + i]);
  }

  for (std::size_t i = 0; i < second_size; ++i) {
    second.push_back(arr[middle + 1 + i]);
  }

  std::size_t i = 0, j = 0, k = begin;

  while (i < first_size && j < second_size) {
    if (first[i] < second[j]) {
      arr[k] = first[i];
      i++;
    } else {
      arr[k] = second[j];
      j++;
    }
    k++;
  }

  while (i < first_size) {
    arr[k] = first[i];
    k++; i++;
  }

  while (j < second_size) {
    arr[k] = second[j];
    k++; j++;
  }
}

template <typename T>
void merge_sort(std::vector<T>& arr, std::size_t begin, std::size_t end) {
  LinkedStack<State> stack;

  stack.push(State(begin, end));

  while (!stack.empty()) {
    State current_state = stack.pop();

    std::size_t middle = (current_state.end + current_state.begin) / 2;

    if (current_state.merge) {
      merge(arr, current_state.begin, middle, current_state.end);
    } else {
      stack.push(State(current_state.begin, current_state.end, true));

      if (middle + 1 < current_state.end) {
        stack.push(State(middle + 1, current_state.end));
      }

      if (current_state.begin < middle) {
        stack.push(State(current_state.begin, middle));
      }
    }
  }
}

int main() {
  std::vector<int> arr = {2, 15, 1, 30, 4, 193, 6, 255, 4};

  merge_sort(arr, 0, arr.size() - 1);

  for (int element : arr) {
    std::cout << element << ' ';
  }
  std::cout << '\n';
  return 0;
}