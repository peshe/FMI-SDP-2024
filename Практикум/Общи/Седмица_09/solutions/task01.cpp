T getMin(Node<T>* root) {
    if (!root) {
        throw std::invalid_argument("Tree is empty!");
    }

    if (!root->left && root->right == nullptr) {
        return root->value;
    }

    if (!root->left) {
        T minRight = getMin(root->right);
        return std::min(root->value, minRight);
    }

    if (!root->right) {
        T minLeft = getMin(root->left);
        return std::min(root->value, minLeft);
    }

    T minLeft = getMin(root->left);
    T minRight = getMin(root->right);

    return std::min(minLeft, std::min(minRight, root->value));
}

T getMax(Node<T>* root) {
    if (!root) {
        throw std::invalid_argument("Tree is empty!");
    }

    if (!root->left && root->right == nullptr) {
        return root->value;
    }

    if (!root->left) {
        T maxRight = getMax(root->right);
        return std::max(root->value, maxRight);
    }

    if (!root->right) {
        T maxLeft = getMax(root->left);
        return std::max(root->value, maxLeft);
    }

    T maxLeft = getMax(root->left);
    T maxRight = getMax(root->right);

    return std::max(maxLeft, std::max(maxRight, root->value));
}

bool isBST(Node<T>* root) const {
    if (!root) {
        return true;
    }

    T maxLeft = root->left != nullptr ? getMax(root->left) : root->value;
    T minRight = root->right != nullptr ? getMin(root->right) : root->value;

    if (!root->left) {
        return root->value < minRight &&
            isBST(root->left) &&
            isBST(root->right);
    }

    if (!root->right) {
        return root->value > maxLeft &&
            isBST(root->left) &&
            isBST(root->right);
    }

    return root->value < minRight &&
        root->value > maxLeft &&
        isBST(root->left) &&
        isBST(root->right);
}
