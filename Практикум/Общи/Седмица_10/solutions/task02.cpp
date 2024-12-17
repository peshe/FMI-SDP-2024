#include <cassert>
#include <cmath>

#include "Node.h"
#include "isBST.hpp"
#include "isBalanced.hpp"
#include "task01.hpp"


template <typename T>
Node<T>* dswBalance(Node<T>* root) {
    assert(isBST(root));
    Node<T>* pseudoRoot = new Node<T>;
    pseudoRoot->right = root;

    size_t treeSize = treeToVine(pseudoRoot) - 1;
    vineToTree(pseudoRoot, treeSize);

    Node<T>* result = pseudoRoot->right;
    pseudoRoot->right = nullptr;
    delete pseudoRoot;

    assert(isBST(result));
    assert(isBalanced(result));
    return result;
}

template <typename T>
size_t treeToVine(Node<T>* root) {
    assert(root != nullptr);

    Node<T>* tail = root;
    size_t treeSize = 1u;
    Node<T>* rest = root->right;

    while (rest != nullptr) {
        if (rest->left == nullptr) {
            tail = rest;
            rest = rest->right;
            ++treeSize;
        }
        else { // rest->left != nullptr
            Node<T>* temp = rest->left;
            rest->left = temp->right;
            temp->right = rest;
            rest = temp;
            tail->right = temp;
        }
    }

    return treeSize;
}

template <typename T>
void vineToTree(Node<T>* root, int size) {
    int nLeaves = size + 1 - std::pow(2, int(std::log2(size + 1)));
    compress(root, nLeaves);
    size -= nLeaves;

    while (size > 1) {
        size /= 2;
        compress(root, size);
    }
}

template <typename T>
void compress(Node<T>* root, int count) {
    Node<T>* scanner = root;

    for (int i = 0; i < count; ++i) {
        Node<T>* child = scanner->right;
        scanner->right = child->right;
        scanner = scanner->right;
        child->right = scanner->left;
        scanner->left = child;
    }
}

template <typename T>
void testAndClearBst(Node<T>* bst) {
    printInOrder(bst);
    bst = dswBalance(bst);
    printInOrder(bst);
    delete bst;
}

int main () {
    Node<int> *bst = new Node<int>(3,
                           new Node<int>(1),
                           new Node<int>(5,
                              new Node<int>(4),
                              new Node<int>(6,
                                nullptr,
                                new Node<int>(8))));
    testAndClearBst(bst);

    Node<int>* degenerateBst = new Node<int>(7,
                                    new Node<int>(6,
                                        new Node<int>(5,
                                            new Node<int>(4))));
    testAndClearBst(degenerateBst);

    return 0;
}
