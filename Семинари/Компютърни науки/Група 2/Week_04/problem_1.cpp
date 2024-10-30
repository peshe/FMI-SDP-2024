#include <ios>
#include <iostream>
#include <stack>
#include <stdexcept>
#include "../Week_03/BoolVector-seminar.hpp"

using BraceType = char;

BraceType getBraceType(const char c) {
	switch (c) {
		case '{':
		case '}': return 0;
		case '(':
		case ')': return 1;

		case '<':
		case '>': return 2;
		case '[':
		case ']': return 3;
		default: throw std::invalid_argument("argument is not a brace");
	}
}
bool isOpenBrace(char c) { return c == '(' || c == '{'; }
bool isClosingBrace(char c) { return c == ')' || c == '}'; }

bool checkBraces(const std::string &str) {
	std::stack<bool, BoolVector> stack;
	for (char c : str) {
		if (isOpenBrace(c)) { stack.push(getBraceType(c)); }
		if (isClosingBrace(c)) {
			if (!stack.empty() && stack.top() == getBraceType(c)) { stack.pop(); }
			if(stack.empty()) return false; // forgot it earlier
		}
	}
	return stack.empty();
}

int main() {
	std::cout << std::boolalpha << checkBraces("{({}({}))()}") << std::endl;
	std::cout << std::boolalpha << checkBraces("{({}({})()}") << std::endl;
}
