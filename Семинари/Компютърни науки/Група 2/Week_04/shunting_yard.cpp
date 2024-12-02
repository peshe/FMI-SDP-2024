#include <cmath>
#include <iostream>

#include "sy.h"


int main() {
	auto rpn = shuntingYard("32 + 40 * 2 / (10 - 13) ^ 2 ^ 3");

	std::cout << rpn << std::endl;

	std::cout << evalRPN(rpn) << std::endl;
}
