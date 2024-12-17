template<class T>
std::vector<T> treeToVector(Node<T> *root) {
    std::vector<T> result;
    treeToVectorHelper(root, result);
    return result;
}

template<class T>
void treeToVectorHelper(Node<T> *root, std::vector<T> &result) {
    if (!root) {
        return;
    }

    treeToVectorHelper(root->left, result);
    result.push_back(root->value);
    treeToVectorHelper(root->right, result);
}
