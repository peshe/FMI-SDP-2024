#include <iostream>
#include <sstream>
#include <string>
#include "linked_stack.hpp"

int get_precedence(char c) {
  switch (c) {
    case '+': case '-':
      return 1;
    case '*': case '/':
      return 2;
    case '(':
      return 3;
    default:
      return 0;
  }
}

std::string to_rpn(const std::string& expression) {
  LinkedStack<char> operations;

  std::stringstream rpn;

  for (char c : expression) {
    if(c >= '0' && c <= '9') {
      rpn << c;
    }

    if(c == '(') {
      operations.push(c);
    }

    if (c == '+' || c == '-' || c == '*' || c == '/') {
      while (!operations.empty() && operations.peek() != '(' && get_precedence(operations.peek()) >= get_precedence(c)) {
        rpn << operations.pop();
      }

      operations.push(c);
    }

    if (c == ')') {
      while (!operations.empty() && operations.peek() != '(') {
        rpn << operations.pop();
      }

      if(!operations.empty()) {
        operations.pop();
      }
    }
  }

  while (!operations.empty()) {
    rpn << operations.pop();
  }

  return rpn.str();
}

int main() {
  std::string expression;
  std::getline(std::cin, expression);
  
  std::cout << to_rpn(expression) << '\n';

  return 0;
}