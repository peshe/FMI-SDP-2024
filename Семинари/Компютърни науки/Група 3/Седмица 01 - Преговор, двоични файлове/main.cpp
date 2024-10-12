#include <cmath>
#include <iostream>
#include <fstream>

bool is_valid_position(unsigned n, int current_x, int current_y) {
  return current_x >= 0 && current_x < n && current_y >= 0 && current_y < n;
}

bool knight_traversal_helper(bool **board, unsigned n, int current_x,
                             int current_y, int end_x,
                             int end_y) {
  if (!is_valid_position(n, current_x, current_y) ||
      board[current_x][current_y]) {
    return false;
  }

  if (current_x == end_x && current_y == end_y) {
    return true;
  }

  board[current_x][current_y] = true;

  for (int dx = -2; dx <= 2; ++dx) {
    if (dx != 0) {
      for (int sign : {-1, 1}) {
        int dy = sign * (3 - std::abs(dx));

        if (knight_traversal_helper(board, n, current_x + dx, current_y + dy,
                                    end_x, end_y)) {
          return true;
        }
      }
    }
  }

  board[current_x][current_y] = false;

  return false;
}

bool knight_traversal(unsigned n, int start_x, int start_y,
                      int end_x, int end_y) {
  bool **board = new bool *[n];
  for (int i = 0; i < n; ++i) {
    board[i] = new bool[n];
  }

  bool result = knight_traversal_helper(board, n, start_x, start_y, end_x, end_y);

  for (int i = 0; i < n; ++i) {
    delete[] board[i];
  }
  delete[] board;

  return result;
}

void swap(int& a, int& b) {
  a ^= b;
  b ^= a;
  a ^= b;
}

bool even(int a) {
  return (a & 1) == 0;
}

int change_sign(int a) {
  return ~a + 1;
}

struct Triangle {
  double a, b, c;
};

int main() {
  int a = 6, b = 3;

  // swap(a, b);

  std::cout << change_sign(a) << '\n';
  return 0;
}