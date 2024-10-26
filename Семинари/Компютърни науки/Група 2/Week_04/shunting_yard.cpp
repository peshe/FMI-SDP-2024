#include <cmath>
#include <functional>
#include <iostream>
#include <stack>
#include <stdexcept>

int getPrecedence(char c) {
	switch (c) {
		case '+': return 2;
		case '-': return 2;
		case '*': return 3;
		case '/': return 3;
		case '^': return 4;

		case '(': return 0;
		case ')': return 0;
		default: throw std::runtime_error("bad operation");
	}
}

bool isLeftAssoc(char c) { return c == '+' || c == '-' || c == '*' || c == '/'; }
bool isRightAssoc(char c) { return c == '^'; }

bool isOp(char c) { return c == '+' || c == '-' || c == '*' || c == '/' || c == '^'; }

bool isOpenBrace(char c) { return c == '('; }
bool isCloseBrace(char c) { return c == ')'; }

double (*getFunction(char c))(double, double) {
	switch (c) {
		case '+': return [](double a, double b) { return a + b; };
		case '-': return [](double a, double b) { return a - b; };
		case '*': return [](double a, double b) { return a * b; };
		case '/': return [](double a, double b) { return a / b; };
		case '^': return [](double a, double b) { return std::pow(a, b); };

		case '(': return nullptr;
		case ')': return nullptr;
		default: throw std::runtime_error("bad operation");
	}
}

std::string shuntingYard(const std::string &expression) {
	std::string		 out;
	std::stack<char> s;

	for (std::size_t i = 0; i < expression.size(); ++i) {
		char c = expression[i];
		if (std::isdigit(c)) {
			
			// адаптация за да работи с многоцифрени числа
			while(std::isdigit(expression[i])) {
				out += expression[i];
				++i;
			}
			--i;
			out += ' ';
			continue;
		}

		if (isOp(c)) {
			while (!s.empty() && ((getPrecedence(s.top()) > getPrecedence(c) && isRightAssoc(c)) ||
								  (getPrecedence(s.top()) >= getPrecedence(c) && isLeftAssoc(c)))) {
				out += s.top();
				s.pop();
			}
			s.push(c);
			continue;
		}

		if (isOpenBrace(c)) {
			s.push(c);
			continue;
		}

		if (isCloseBrace(c)) {
			while (!isOpenBrace(s.top())) {
				out += s.top();
				s.pop();
			}
			s.pop();
			continue;
		}
	}

	while (!s.empty()) {
		out += s.top();
		s.pop();
	}

	return out;
}

double evalRPN(const std::string &expression) {
	std::stack<double> s;

	for (std::size_t i = 0; i < expression.size(); ++i) {
		char c = expression[i];
		if (std::isdigit(c)) {
			int num = 0;
			while(std::isdigit(expression[i])) {
				num *= 10;
				num += expression[i] - '0';
				++i;
			}
			s.push(num); 
		}

		if (isOp(c)) {
			double right = s.top();
			s.pop();
			double left = s.top();
			s.pop();
			s.push(getFunction(c)(left, right));
		}
	}

	return s.top();
}

int main() {
	auto rpn = shuntingYard("32 + 40 * 2 / (10 - 13) ^ 2 ^ 3");

	std::cout << rpn << std::endl;

	std::cout << evalRPN(rpn) << std::endl;
}
