#include "Node.h"
#include <iostream>

template<class T>
void rightRotation(Node<T> *&root) {
    Node<T> *originalLeft = root->left;
    root->left = originalLeft->right;
    originalLeft->right = root;
    root = originalLeft;
}

template<class T>
void leftRotation(Node<T> *&root) {
    Node<T> *originalRight = root->right;
    root->right = originalRight->left;
    originalRight->left = root;
    root = originalRight;
}

template<class T>
void leftRightRotation(Node<T> *&root) {
    leftRotation(root->left);
    rightRotation(root);
}

template<class T>
void rightLeftRotation(Node<T> *&root) {
    rightRotation(root->right);
    leftRotation(root);
}

// Helper functions to better visualize the tree before and after rotating
// https://dreampuf.github.io/GraphvizOnline/
template<typename T>
void printDot(Node<T> *root) {
    std::cout << "digraph G {" << std::endl;
    printDotHelper(root);
    std::cout << "}" << std::endl;
}

template<typename T>
void printDotHelper(Node<T> *current) {
    if (current == nullptr) {
        return;
    }

    std::cout << (long) current << "[label=\"" << current->value << "\"]" << std::endl;

    if (current->left != nullptr) {
        std::cout << (long) current << " -> " << (long) current->left << std::endl;
    }

    if (current->right != nullptr) {
        std::cout << (long) current << " -> " << (long) current->right << std::endl;
    }

    printDotHelper(current->left);
    printDotHelper(current->right);
}

int main() {
    auto bst = new Node<int>(50,
                             new Node<int>(17,
                                           new Node<int>(9),
                                           new Node<int>(23)),
                             new Node<int>(76));

    printDot(bst);

    rightRotation(bst);

    std::cout << "After right rotation:\n";
    printDot(bst);

    delete bst;
    return 0;
}
