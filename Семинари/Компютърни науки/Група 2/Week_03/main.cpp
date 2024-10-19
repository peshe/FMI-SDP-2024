#include <iostream>
#include "boolvector.hpp"

int main() {
	BoolVector v(16);

	v[5] = true;
	v.push_back(1);
	v.push_back(1);
	v.push_back(1);
	v.push_back(1);

	v.push_back(1);
	v.push_back(1);
	v.push_back(1);
	v.push_back(1);

	v.push_back(0);
	v.push_back(0);
	v.push_back(1);
	v.push_back(0);

	v.push_back(1);
	v.push_back(1);
	v.push_back(0);
	v.push_back(0);

	v[4] = true;

	BoolVector u(8);
	v += u;

	for (std::size_t i = 0; i < v.size(); ++i) {
		std::cout << v[i];
	};
	std::cout << std::endl;
}
