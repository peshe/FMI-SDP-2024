int height(Node<T>* root)
{
    if (!root)
    {
        return 0;
    }

    return 1 + std::max(this->height(root->left), this->height(root->right));
}

bool isBalanced(Node<T>* root)
{
    if (!root)
    {
        return true;
    }

    return isBalanced(root->left) &&
            isBalanced(root->right) &&
            (std::abs(this->height(root->left) - this->height(root->right)) < 2);
}