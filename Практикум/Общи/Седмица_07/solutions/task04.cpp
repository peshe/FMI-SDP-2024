#include "Node.h"

#include <iostream>


Node<unsigned>* generateBTree(unsigned min, unsigned max) {
    if (min > max) return nullptr;

    Node<unsigned>* left = generateBTree(2 * min, max);
    Node<unsigned>* right = generateBTree(2 * min + 1, max);
    return new Node<unsigned>(min, left, right);
}

Node<unsigned int>* generateBTree(unsigned int n) {
    return generateBTree(1, n);
}

template <typename T>
void printLeftParentRight(const Node<T>* btree) {
    if (btree == nullptr) return;

    printLeftParentRight(btree->left);
    std::cout << ' ' << btree->value << ' ';
    printLeftParentRight(btree->right);
}

int main () {
    Node<unsigned int> *btree = generateBTree(9);
    printLeftParentRight(btree);

    delete btree;
    return 0;
}
