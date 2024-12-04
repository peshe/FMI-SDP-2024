template <typename T>
Node<T>* lca(Node<T> *current, Node<T> *first, Node<T> *second)
{
    // В празното поддърво нямат най-близък общ наследник
    if (current == nullptr)
        return nullptr;

    // Ако един от двата елемента е корен на текущото дърво, то той е и най-близкият общ наследник
    if (current == first)
        return current;
    if (current == second)
        return current;

    // Намираме най-малкия общ наследник в лявото и дясното поддърво
    Node<T> *leftLca = lca(current->left, first, second);
    Node<T> *rightLca = lca(current->right, first, second);

    // Ако и двата съществуват, това означава, че единият елемент сме го намерили в едното поддърво, а другият в другото.
    // Тоест текущият корен е най-близък общ наследник
    if (leftLca != nullptr && rightLca != nullptr)
        return current;

    // В противен случай връщаме един от двата намерени
    return leftLca != nullptr ? leftLca : rightLca;
}