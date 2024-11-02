#include <cstddef>
#include <iostream>
#include <string>
#include <vector>
#include "linked_queue.hpp"

std::vector<std::string> generate_binary(unsigned n) {
  std::vector<std::string> result;

  LinkedQueue<std::string> queue;
  queue.enqueue("1");

  for (unsigned i = 0; i < n; ++i) {
    std::string current = queue.dequeue();
    result.push_back(current);

    queue.enqueue(current + '0');
    queue.enqueue(current + '1');
  }

  return result;
}

struct Position {
  int x, y;
};

struct PositionWithDistance : public Position {
  unsigned distance;
};

int find_shortest_path(std::vector<std::vector<bool>> &board,
                       const Position &start, const Position &end) {
  LinkedQueue<PositionWithDistance> queue;
  queue.enqueue({start.x, start.y, 0});

  while (!queue.empty()) {
    PositionWithDistance current = queue.dequeue();

    if (current.x == end.x && current.y == end.y) {
      return current.distance;
    }

    board[current.x][current.y] = true;

    for (int d : {-1, 1}) {
      int new_x = current.x + d, new_y = current.y + d;

      if (new_x >= 0 && new_x < board.size() && !board[new_x][current.y]) {
        queue.enqueue({new_x, current.y, current.distance + 1});
      }

      if (new_y >= 0 && new_y < board.size() && !board[current.x][new_y]) {
        queue.enqueue({current.x, new_y, current.distance + 1});
      }
    }
  }

  return -1;
}

std::vector<int> find_first_negative(const std::vector<int> &arr,
                                     std::size_t n) {
  std::vector<int> result;
  LinkedQueue<std::size_t> queue;

  for (std::size_t i = 0; i < n; ++i) {
    queue.enqueue(i);
  }

  while (!queue.empty() && arr[queue.first()] >= 0) {
    queue.dequeue();
  }

  if (queue.empty()) {
    result.push_back(0);
  } else {
    result.push_back(arr[queue.first()]);
  }

  for (std::size_t i = n; i < arr.size(); ++i) {
    queue.enqueue(i);

    if (i - queue.first() == n) {
      queue.dequeue();
    }

    while (!queue.empty() && arr[queue.first()] >= 0) {
      queue.dequeue();
    }

    if (queue.empty()) {
      result.push_back(0);
    } else {
      result.push_back(arr[queue.first()]);
    }
  }

  return result;
}

int main() {
  std::vector<int> arr{12, -1, -7, 8, -15, 30, 16, 28};
  
  for(int n : find_first_negative(arr, 3)) {
    std::cout << n << ' ';
  }
  std::cout << '\n';

  return 0;
}