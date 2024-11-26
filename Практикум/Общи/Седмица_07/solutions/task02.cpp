#include "Node.h"

#include <iostream>


template <typename T>
std::size_t findNodesNumber(Node<T> *btree) {
    if (btree == nullptr) return 0;

    return findNodesNumber(btree->left) + findNodesNumber(btree->right) + 1;
}

int main () {
    Node<int> *btree = new Node<int>(1,
                               new Node<int>(2,
                                              new Node<int>(3),
                                              new Node<int>(4)),
                               new Node<int>(5,
                                              new Node<int>(6),
                                              new Node<int>(7)));
    std::cout << findNodesNumber(btree) << std::endl;

    delete btree;
    return 0;
}
