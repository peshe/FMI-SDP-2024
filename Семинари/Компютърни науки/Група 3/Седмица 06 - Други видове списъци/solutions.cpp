#include "circular_linked_list.hpp"
#include <cstddef>
#include <iostream>
#include <optional>
#include <utility>

int main() {
  int k = 3;
  CircularLinkedList<std::string> list;
  for (const std::string& name : {"Gosho", "Pesho", "Tosho", "Ivan", "Dragan", "Petkan", "Asen"}) {
    list.insert_last(name);
  }

  while (list.get_size() != 1) {
    for (std::size_t i = 0; i < k-1; ++i) {
      list.advance_first();
    }
    list.remove_first();
  }

  std::cout << list.first() << '\n';
  
  return 0;
}