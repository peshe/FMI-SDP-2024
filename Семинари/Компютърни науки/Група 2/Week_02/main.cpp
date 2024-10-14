#include <iostream>
#include <vector>
#include "vector.h"
#include "reverse.h"
#include "zip.h"
#include "t_name.h"

int main() {
	// works with different containers
	const Vector<int> v{1,2,3,4};
	std::vector<int> l{5,6,7,8,9};
	
	// print v
	for (auto& x : v) {
		std::cout << x << " ";
	}
	std::cout << std::endl;


	// print v in reverse
	std::cout << TYPE_NAME(Reverse(v)) << std::endl;
	for (auto& x : Reverse(v)) {
		std::cout << x << " ";
	}
	std::cout << std::endl;


	// print zip(v, l)
	std::cout << TYPE_NAME(Zip(v, l)) << std::endl;
	for (auto [u, v] : Zip(v, l)) {
		std::cout << "(" << u << ", " << v << ") ";
		v = 5;
	}
	std::cout << std::endl;


	// print the modified l
	for (auto x : l)
		std::cout << x << " ";
	std::cout << std::endl;
	
	
	std::cout << TYPE_NAME(Zip(Reverse(Vector{1,3,2,4}), l)) << std::endl;

	// more complex case
	for (auto [u, v] : Zip(Reverse(Vector{1,3,2,4}), l)) {
		std::cout << "(" << u << ", " << v << ") " << std::flush;
		u = 5;
	}
	std::cout << std::endl;

}
