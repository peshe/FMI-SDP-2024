#include <iostream>
#include "boolvector.hpp"


int main() {

	fmi::sdp::DynArray<bool> v(16);
	v.push_back(1);
	v.push_back(1);
	v.push_back(1);
	v.push_back(1);

	v.pop_back();
	v.push_back(1);
	v.push_back(1);
	v.push_back(1);
	v.push_back(1);

	v[5] = true;
	bool b = v[5];

	for(std::size_t i = 0; i < v.size(); ++i) {
		std::cout << v[i];
	}

	std::cout << std::endl;

	for(auto b : v) {
		std::cout << b;
	}
	std::cout << std::endl;

}
