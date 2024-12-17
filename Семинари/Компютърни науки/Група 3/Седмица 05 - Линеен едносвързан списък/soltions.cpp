#include <cstddef>
#include <iostream>
#include <type_traits>
#include <utility>
#include "linked_list.hpp"

int main() {
  LinkedList<int> list;

  for (int i : {1, 2, 3, 4, 5}) {
    list.insert_last(i);
  }

  list.reverse();

  LinkedList<int> list2(list);

  LinkedList<int>::Iterator it = list.begin();
  ++it;

  list.insert_after(9, it);

  list.remove_at(it);

  for (int i : list) {
    std::cout << i << ' ';
  }
  std::cout << '\n';
  for (int i : list2) {
    std::cout << i << ' ';
  }
  std::cout << '\n';

  return 0;
}