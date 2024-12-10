template <typename T>
T min(Node<T> *current)
{

    if (current->left == nullptr && current->right == nullptr)
    {
        return current->data;
    }

    if (current->left == nullptr)
    {
        T minR = min(current->right);
        return std::min(current->data, minR);
    }

    if (current->right == nullptr)
    {
        T minL = min(current->left);
        return std::min(current->data, minL);
    }

    T minL = min(current->left);
    T minR = min(current->right);

    return std::min(minL, std::min(current->data, minR));
}

template <typename T>
T max(Node<T> *current)
{

    if (current->left == nullptr && current->right == nullptr)
    {
        return current->data;
    }

    if (current->left == nullptr)
    {
        T minR = max(current->right);
        return std::max(current->data, minR);
    }

    if (current->right == nullptr)
    {
        T minL = max(current->left);
        return std::max(current->data, minL);
    }

    T minL = max(current->left);
    T minR = max(current->right);

    return std::max(minL, std::max(current->data, minR));
}


template <typename T>
bool isBST(Node<T> *current)
{
    // Празното дърво е наредено
    if (current == nullptr)
        return true;

    T maxLeft = current->left != nullptr ? max(current->left) : current->data;
    T minRight = current->right != nullptr ? min(current->right) : current->data;

    // Едно дърво е наредено, ако:
    return current->data >= maxLeft &&  // коренът е по-голям от всички елементи в лявото поддърво
           current->data <= minRight && // коренът е по-малък от всички елементи в дясното поддърво
           isBST(current->left) &&      // лявото поддърво е наредено
           isBST(current->right);       // дясното поддърво е наредено
}