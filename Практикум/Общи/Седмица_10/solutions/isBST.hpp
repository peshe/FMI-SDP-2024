#ifndef _IS_BST_HPP_
#define _IS_BST_HPP_

#include <algorithm>
#include <stdexcept>

#include "Node.h"


template <typename T>
T getMin(const Node<T>* root) {
    if (!root) {
        throw std::invalid_argument("Tree is empty!");
    }

    T result = root->value;

    if (root->left != nullptr) {
        result = std::min(result, getMin(root->left));
    }

    if (root->right != nullptr) {
        result = std::min(result, getMin(root->right));
    }

    return result;
}

template <typename T>
T getMax(const Node<T>* root) {
    if (!root) {
        throw std::invalid_argument("Tree is empty!");
    }

    T result = root->value;

    if (root->left != nullptr) {
        result = std::max(result, getMax(root->left));
    }

    if (root->right != nullptr) {
        result = std::max(result, getMax(root->right));
    }

    return result;
}

template <typename T>
bool isBST(const Node<T>* root) {
    if (!root) {
        return true;
    }

    bool result = true;

    if (root->left != nullptr) {
        T maxLeft = getMax(root->left);
        result = root->value > maxLeft && isBST(root->left);
    }

    if (result && root->right != nullptr) {
        T minRight = getMin(root->right);
        result = root->value < minRight && isBST(root->right);
    }

    return result;
}

#endif // _IS_BST_HPP_
