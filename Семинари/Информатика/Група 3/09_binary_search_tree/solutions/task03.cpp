  int height(Node<T>* root) const
    {
        if (!root)
        {
            return 0;
        }

        return 1 + std::max(this->height(root->left), this->height(root->right));
    }

    bool isBalanced(Node<T>* root) const
    {
        if (!root)
        {
            return true;
        }

        return isBalanced(root->left) &&
               isBalanced(root->right) &&
               (std::abs(this->height(root->left) - this->height(root->right)) < 2);
    }

    bool isPerfectlyBalanced(Node<T>* root) const
    {
        if (!root)
        {
            return true;
        }

        return isPerfectlyBalanced(root->left) &&
               isPerfectlyBalanced(root->right) &&
               (std::abs(this->size(root->left) - this->size(root->right)) < 2);
    }