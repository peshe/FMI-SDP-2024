#include <algorithm>
#include <cstddef>
#include <iostream>
#include <iterator>
#include <vector>
#include "queue.hpp"
#include "queue_with_stacks.hpp"

struct HammingQueue {
  QueueWithStacks<unsigned> queue;
  unsigned number;
};

std::vector<unsigned> generate_hamming_numbers(unsigned n) {
  std::vector<unsigned> result(n);

  QueueWithStacks<unsigned> q2;
  q2.enqueue(1);
  QueueWithStacks<unsigned> q3;
  q3.enqueue(1);
  QueueWithStacks<unsigned> q5;
  q5.enqueue(1);

  HammingQueue queues[] = {{q2, 2}, {q3, 3}, {q5, 5}};
  for (std::size_t i = 0; i < n; ++i) {
    unsigned min = std::min_element(std::begin(queues), std::end(queues), [](const HammingQueue& h1, const HammingQueue& h2){
      return h1.queue.first() < h2.queue.first();
    })->queue.first();
    result[i] = min;

    for (HammingQueue& h : queues) {
      if (h.queue.first() == min) {
        h.queue.dequeue();
      }

      h.queue.enqueue(h.number * min);
    }
  }

  return result;
}

int main() {
  unsigned n;
  std::cin >> n;

  for (unsigned number : generate_hamming_numbers(n)) {
    std::cout << number  << ' ';
  }
  std::cout << '\n';

  return 0;
}