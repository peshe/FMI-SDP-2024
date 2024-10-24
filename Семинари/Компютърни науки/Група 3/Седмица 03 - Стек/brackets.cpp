#include <cstddef>
#include <ios>
#include <iostream>
#include <string>
#include "linked_stack.hpp"

char opening(char c) {
  switch (c) {
    case ')': return '(';
    case ']': return '[';
    case '}': return '{';
    default: return '\0';
  }
}

bool is_balanced(const std::string& expression) {
  LinkedStack<char> stack;

  for (char c : expression) {
    if (c == '(' || c == '{' || c == '[') {
      stack.push(c);
    }

    if (c == ')' || c == '}' || c == ']') {
      if (stack.empty() || stack.peek() != opening(c)) {
        return false;
      }

      stack.pop();
    }
  }

  return true;
}

int main() {
  std::string expression;
  std::getline(std::cin, expression);

  std::cout << std::boolalpha << is_balanced(expression) << '\n';

  return 0;
}