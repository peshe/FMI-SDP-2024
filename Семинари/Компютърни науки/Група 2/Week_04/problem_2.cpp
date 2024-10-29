#include <iostream>
#include <stack>
#include "../Week_03/BoolVector-seminar.hpp"

using BraceType = char;

BraceType getBraceType(const char c) {
	switch (c) {
		case '{':
		case '}': return 0b00;
		case '(':
		case ')': return 0b01;

		case '<':
		case '>': return 0b10;
		case '[':
		case ']': return 0b11;
		default: throw std::invalid_argument("argument is not a brace");
	}
}

bool isOpenBrace(char c) { return c == '(' || c == '{'; }
bool isClosingBrace(char c) { return c == ')' || c == '}'; }

bool checkBraces(const std::string &str) {
	std::stack<bool, BoolVector> stack;
	for (char c : str) {
		if (isOpenBrace(c)) {
			BraceType t = getBraceType(c);
			// push 2 bits
			stack.push((t & 2) >> 1);
			stack.push(t & 1);
		}
		if (isClosingBrace(c)) {
			if (!stack.empty()) {
				BraceType t = getBraceType(c);
				if (stack.top() == (t & 1)) { // check first bit
					stack.pop(); // pop so that top() is the second bit
					if (stack.top() == ((t & 2) >> 1)) // if it matches too, pop second time
					{ stack.pop(); }
					else stack.push(t & 1); // else, return to previous state
				}
			} else { return false;} // closing brace with no opening brace
		}
	}
	return stack.empty();
}

int main() {
	std::cout << std::boolalpha << checkBraces("{({}({}))()}") << std::endl; // correct
	std::cout << std::boolalpha << checkBraces("{({}({})()}") << std::endl; // incorrect
	std::cout << std::boolalpha << checkBraces("{({}(})()}") << std::endl; // incorrect
}
