#include <cinttypes>
#include <iostream>
#include "bst.hpp"

int main() {
	{
		BST bst(nullptr, nullptr);
		bst.insert(1);
		bst.insert(0);
		bst.insert(2);

		bst.printGraphicDown();
		bst.printGraphic();

	}

	{
		int els[] = {2, 3, 5, 8, 12, 13};

		BST bst(els, els + 6);

		bst.print();
		std::cout << bst.contains(2) << std::endl << bst.contains(7) << std::endl;
		std::cout << std::endl;
		bst.insert(6);
		bst.print();
		std::cout << std::endl;
	}

	{

		BST bst(nullptr, nullptr);
		bst.insert(10);
		bst.insert(3);
		bst.insert(6);
		bst.insert(4);

		bst.insert(20);
		bst.insert(13);
		bst.insert(11);
		bst.insert(12);
		bst.insert(15);

		bst.printGraphic();
		std::cout << "------------------------" << std::endl;
		bst.remove(13);
		bst.printGraphic();

		bst.rebalance();
		std::cout << "------------------------" << std::endl;
		bst.printGraphicDown();
		bst.printGraphic();


	}
}
