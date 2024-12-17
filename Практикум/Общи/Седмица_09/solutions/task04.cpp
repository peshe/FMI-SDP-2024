template<class T>
Node<T> *naiveBuild(const std::vector<T> &input) {
    if (input.empty()) {
        return nullptr;
    }

    Node<T> *result = new Node<T>(input[0]);
    for (std::size_t i = 1; i < input.size(); ++i) {
        add(result, input[i]);
    }
    return result;
}

template<class T>
Node<T> *recursiveBuildHelper(const std::vector<T> &input,
                              int start, int end) {
    if (start > end) return nullptr;

    int mid = start + (end - start) / 2;

    Node<T> *root = new Node(input[mid]);
    root->left = recursiveBuildHelper(input, start, mid - 1);
    root->right = recursiveBuildHelper(input, mid + 1, end);

    return root;
}

template<class T>
Node<T> *betterBuild(const std::vector<T> &input) {
    if (input.empty()) {
        return nullptr;
    }
    return recursiveBuildHelper(input, 0, input.size() - 1);
}
