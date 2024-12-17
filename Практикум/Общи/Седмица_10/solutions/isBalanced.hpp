#ifndef _IS_BALANCED_HPP_
#define _IS_BALANCED_HPP_

#include <algorithm>
#include <cstdlib>

#include "Node.h"


template <typename T>
int height(const Node<T>* root)
{
    if (!root)
    {
        return 0;
    }

    return 1 + std::max(height(root->left), height(root->right));
}

template <typename T>
bool isBalanced(const Node<T>* root)
{
    if (!root)
    {
        return true;
    }

    return isBalanced(root->left) &&
            isBalanced(root->right) &&
            (std::abs(height(root->left) - height(root->right)) < 2);
}

#endif // _IS_BALANCED_HPP_
