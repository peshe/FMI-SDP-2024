template <class T>
class Node {
public:
    T value;
    Node<T>* left;
    Node<T>* right;

    Node(const T& value, Node<T>* left = nullptr, Node<T>* right = nullptr)
        : value(value), left(left), right(right)
    { }
};

template <class T>
class BTSree {
public:
    BTSree(Node<T>* root) : root(root) {}

    BTSree(const BSTree& other) {
        this->root = BSTree::clone(other.root);
    }

    BSTree& operator=(const BSTree& other) {
        if (this != &other) {
            Node<T>* newRoot = nullptr;
            try
            {
                newRoot = BSTree::clone(other->root);
            }
            catch (const std::exception&)
            {
                BSTree::free(newRoot);
            }
            BSTree::free(this->root);
            this->root = newRoot;
        }
        return this;
    }


    ~BSTree() {
        BSTree::free(this->root);
    }

public:

    bool contains(const T& data) const {
        return contains(this->root, data);
    }

    const T& min() const {
        return getMin(this->root);
    }

    const T& max() const {
        return getMax(this->root);
    }

    void add(const T& data) {
        add(this->root, data);
    }

    void printDot() const {
        std::cout << "digraph G {" << std::endl;
        BSTree::printDot(root);
        std::cout << "}" << std::endl;
    }

    int getHeight() const {
        return BSTree::getHeight(this->root);
    }


public:
    // https://dreampuf.github.io/GraphvizOnline/
    static void printDot(Node<T>* current)
    {

        if (current == nullptr)
        {
            return;
        }

        std::cout << (long)current << "[label=\"" << current->value << "\"]" << std::endl;

        if (current->left != nullptr)
        {
            std::cout << (long)current << " -> " << (long)current->left << std::endl;
        }

        if (current->right != nullptr)
        {
            std::cout << (long)current << " -> " << (long)current->right << std::endl;
        }

        printDot(current->left);
        printDot(current->right);
    }

    static int getHeight(Node<T>* root) {
        if (!root) {
            return 0;
        }

        return 1 + std::max(BSTree::getHeight(root->left), BSTree::getHeight(root->right));
    }

    bool contains(Node<T>* root, const T& data) const {
        if (!root) {
            return false;
        }

        if (root->value == data) {
            return true;
        }

        if (root->value > data) {
            return contains(root->left, data);
        }

        return contains(root->right, data);
    }

    T getMin(Node<T>* root) const {
        if (!root) {
            throw std::invalid_argument("Tree is empty!");
        }
        
        while (root->left) {
            root = root->left;
        }

        return root->value;
    }

    T getMax(Node<T>* root) const {
        if (!root) {
            throw std::invalid_argument("Tree is empty!");
        }
        
        while (root->right) {
            root = root->right;
        }

        return root->value;
    }

    void add(Node<T>*& root, const T& data) {
        if (!root) {
            root = new Node<T>(data);
        }

        if (root->value > data) {
            add(root->left, data);
            return;
        }

        if (root->value < data) {
            add(root->right, data);
            return;
        }

        return;
    }

    void remove(Node<T>*& root, const T& data) {
        if (!root) {
            return;
        }

        if (root->data > data) {
            remove(root->left, data);
            return;
        }

        if (root->data < data) {
            remove(root->right, data);
            return;
        }

        // Изтриване на листо
        if (root->left == nullptr && root->right == nullptr) {
            delete root;
            root = nullptr;
            return;
        }

        // Изтриване на възел с един наследник отдясно
        if (root->left == nullptr) {
            Node<T>* toDelete = root;
            root = root->right;
            delete toDelete;
            return;
        }

        // Изтриване на възел с един наследник отляво
        if (root->right == nullptr) {
            Node<T>* toDelete = root;
            root = root->left;
            delete toDelete;
            return;
        }

        // Изтриване на възел с два наследника
        T minRight = getMin(root->right);
        root->value = minRight;
        remove(root->right, minRight);

        // Вариант 2
        /*T maxLeft = getMax(root->left);
        root->value = maxLeft;
        remove(root->left, maxLeft);*/
    }

    bool isBalanced(Node<T>* root) const {
        if (!root) {
            return true;
        }

        return isBalanced(root->left) &&
            isBalanced(root->right) &&
            std::abs(BTSree::getHeight(root->left) - BTSree::getHeight(root->right)) < 2;
    }

private:
    static void free(Node<T>* root) {
        if (!root) {
            return;
        }

        free(root->left);
        free(root->right);
        delete root;
    }

    static Node<T>* clone(Node<T>* root) {
        if (!root) {
            return nullptr;
        }
        return new Node<T>(root->value, BSTree::clone(root->left), BSTree::clone(root->right));
    }

private:
    Node<T>* root;
};
