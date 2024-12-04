#include <iostream>
#include <stdexcept>

template<class T>
class Node {
public:
    T value;
    Node<T> *left;
    Node<T> *right;
    int height;

    Node(const T &value, Node<T> *left = nullptr, Node<T> *right = nullptr, int height = 0)
            : value(value), left(left), right(right), height(height) {}
};

template<class T>
class AVLTree {
public:
    AVLTree(Node<T> *root) : treeRoot(root) {}

    AVLTree(const AVLTree &other) {
        this->treeRoot = AVLTree::clone(other.treeRoot);
    }

    AVLTree &operator=(const AVLTree &other) {
        if (this != &other) {
            Node<T> *newRoot = nullptr;
            try {
                newRoot = AVLTree::clone(other->treeRoot);
            }
            catch (const std::exception &) {
                AVLTree::free(newRoot);
            }
            AVLTree::free(this->treeRoot);
            this->treeRoot = newRoot;
        }
        return this;
    }


    ~AVLTree() {
        AVLTree::free(this->treeRoot);
    }

public:

    bool contains(const T &data) const {
        return contains(this->treeRoot, data);
    }

    void add(const T &data) {
        add(this->treeRoot, data);
    }

    void remove(const T &data) {
        remove(this->treeRoot, data);
    }

    void printDot() const {
        std::cout << "digraph G {" << std::endl;
        AVLTree::printDot(treeRoot);
        std::cout << "}" << std::endl;
    }

private:
    // https://dreampuf.github.io/GraphvizOnline/
    static void printDot(Node<T> *current) {
        if (current == nullptr) {
            return;
        }

        std::cout << (long) current << "[label=\"" << current->value << "\"]" << std::endl;

        if (current->left != nullptr) {
            std::cout << (long) current << " -> " << (long) current->left << std::endl;
        }

        if (current->right != nullptr) {
            std::cout << (long) current << " -> " << (long) current->right << std::endl;
        }

        printDot(current->left);
        printDot(current->right);
    }

    bool contains(Node<T> *root, const T &data) const {
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

    void add(Node<T> *&root, const T &data) {
        if (!root) {
            root = new Node<T>(data);
        } else if (root->value > data) {
            add(root->left, data);
        } else if (root->value < data) {
            add(root->right, data);
        }

        balance(root);
    }

    T getMin(Node<T> *root) const {
        if (!root) {
            throw std::invalid_argument("Tree is empty!");
        }

        while (root->left) {
            root = root->left;
        }

        return root->value;
    }

    void remove(Node<T> *&root, const T &data) {
        if (!root) {
            return;
        }

        if (root->value > data) {
            remove(root->left, data);
        } else if (root->value < data) {
            remove(root->right, data);
        }

            // Изтриване на листо
        else if (root->left == nullptr && root->right == nullptr) {
            delete root;
            root = nullptr;
        }

            // Изтриване на възел с един наследник отдясно
        else if (root->left == nullptr) {
            Node<T> *toDelete = root;
            root = root->right;
            delete toDelete;
            return;
        }

            // Изтриване на възел с един наследник отляво
        else if (root->right == nullptr) {
            Node<T> *toDelete = root;
            root = root->left;
            delete toDelete;
        } else {
            // Изтриване на възел с два наследника
            T minRight = getMin(root->right);
            root->value = minRight;
            remove(root->right, minRight);

            // Вариант 2
            /*T maxLeft = getMax(treeRoot->left);
            treeRoot->value = maxLeft;
            remove(treeRoot->left, maxLeft);*/
        }
        balance(root);
    }

    int getNodeHeight(Node<T> *node) const {
        if (node) {
            return node->height;
        }
        return -1;
    }

    void rightRotation(Node<T> *&root) {
        Node<T> *originalLeft = root->left;
        root->left = originalLeft->right;
        originalLeft->right = root;

        // Update heights
        root->height = std::max(getNodeHeight(root->left), getNodeHeight(root->right)) + 1;
        originalLeft->height = std::max(getNodeHeight(originalLeft->left), root->height) + 1;

        root = originalLeft;
    }

    void leftRotation(Node<T> *&root) {
        Node<T> *originalRight = root->right;
        root->right = originalRight->left;
        originalRight->left = root;

        // Update heights
        root->height = std::max(getNodeHeight(root->left), getNodeHeight(root->right)) + 1;
        originalRight->height = std::max(getNodeHeight(originalRight->left), root->height) + 1;

        root = originalRight;
    }

    void leftRightRotation(Node<T> *&root) {
        leftRotation(root->left);
        rightRotation(root);
    }

    void rightLeftRotation(Node<T> *&root) {
        rightRotation(root->right);
        leftRotation(root);
    }

    void balance(Node<T> *&root) {
        if (root == nullptr) {
            return;
        }

        if (getNodeHeight(root->left) - getNodeHeight(root->right) > ALLOWED_IMBALANCE) {
            if (getNodeHeight(root->left->left) >= getNodeHeight(root->left->right)) {
                rightRotation(root);
            } else {
                leftRightRotation(root);
            }
        }
        if (getNodeHeight(root->right) - getNodeHeight(root->left) > ALLOWED_IMBALANCE) {
            if (getNodeHeight(root->right->right) >= getNodeHeight(root->right->left)) {
                leftRotation(root);
            } else {
                rightLeftRotation(root);
            }
        }

        root->height = std::max(getNodeHeight(root->left), getNodeHeight(root->right)) + 1;
    }

private:
    static void free(Node<T> *root) {
        if (!root) {
            return;
        }

        free(root->left);
        free(root->right);
        delete root;
    }

    static Node<T> *clone(Node<T> *root) {
        if (!root) {
            return nullptr;
        }
        return new Node<T>(root->value, AVLTree::clone(root->left), AVLTree::clone(root->right));
    }

private:
    static const int ALLOWED_IMBALANCE = 1;
    Node<T> *treeRoot;
};

int main() {
    AVLTree<int> tree(nullptr);
    tree.add(1);
    tree.add(2);
    tree.add(3);
    tree.add(4);
    tree.add(5);
    tree.add(6);
    tree.add(16);
    tree.add(15);

    tree.remove(5);

    tree.printDot();

    return 0;
}
