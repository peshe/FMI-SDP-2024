#ifndef _TASK01_HPP_
#define _TASK01_HPP_

#include "Node.h"

#include <iostream>


template <typename T>
void printLeftParentRight(const Node<T>* btree) {
    if (btree == nullptr) return;

    printLeftParentRight(btree->left);
    std::cout << ' ' << btree->value << ' ';
    printLeftParentRight(btree->right);
}

template <typename T>
void printInOrder(const Node<T>* bst) {
    printLeftParentRight(bst);
    std::cout << std::endl;
}

#endif // _TASK01_HPP_
