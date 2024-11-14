
#include <iostream>
#include "llist.h"

int main() {
	Allocator<LList<int>::Node> allocator(1'000'000);

	{
		LList<int> ll(allocator);
		ll.push_back(1);
		ll.push_back(2);
		ll.push_back(3);
		ll.push_back(4);

		LList<int> ll2 = LList<int>(ll);

		std::cout << "Hello World" << std::endl;
		ll.print(std::cout);
	}
	allocator.checkForLeaks();
	//
}
