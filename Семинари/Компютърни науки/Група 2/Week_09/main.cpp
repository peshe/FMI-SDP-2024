#include <iostream>
#include "bst.hpp"

int main() {
	int els[] = {2, 3, 5, 8, 12, 13};

	BST bst(els, els + 6);

	bst.print();
	// std::cout << bst.contains(2) << std::endl << bst.contains(7) << std::endl;
	std::cout << std::endl;
	bst.insert(6);
	bst.print();
}
