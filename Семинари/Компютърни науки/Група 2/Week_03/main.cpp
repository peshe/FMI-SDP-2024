#include <iostream>
#include "BoolVector.hpp"

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

	for(std::size_t i = 0; i < v.size(); ++i) {
		std::cout << v[i];
	};
	std::cout << std::endl;

}
