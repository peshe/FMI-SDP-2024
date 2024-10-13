#include <iostream>
#include <vector>
#include <set>
#include "vector.h"
#include "reverse.h"
#include "zip.h"

int main() {
	// работи с различни контейнери
	const Vector<int> v{1,2,3,4};
	
	// print v
	for (auto& x : v) {
		std::cout << x << " ";
	}
	std::cout << std::endl;

	// print v in reverse
	for (auto& x : Reverse(v)) {
		std::cout << x << " ";
	}
	std::cout << std::endl;

	std::vector<int> l{5,6,7,8,9};

	// print zip(v, l)
	for (auto [u, v] : Zip(v, l)) {
		std::cout << "(" << u << ", " << v << ") ";
		v = 5;
	}
	std::cout << std::endl;

	// print the modified l
	for (auto x : l)
		std::cout << x << " ";
	std::cout << std::endl;
	
	std::set<int> s{1,3,2,4};
	
	for (auto [u, v] : Zip(Reverse(s), l)) {
		std::cout << "(" << u << ", " << v << ") ";
		//u = 5;
	}
	std::cout << std::endl;

}
