#include <iostream>
#include <vector>
#include <string>

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
class BTree {
public:
    BTree(Node<T>* root) : root(root) {}

    BTree(const BTree& other) {
        this->root = BTree::clone(other.root);
    }

    BTree& operator=(const BTree& other) {
        if (this != &other) {
            Node<T>* newRoot = nullptr;
            try
            {
                newRoot = BTree::clone(other->root);
            }
            catch (const std::exception&)
            {
                BTree::free(newRoot);
            }
            BTree::free(this->root);
            this->root = newRoot;
        }
        return this;
    }


    ~BTree() {
        BTree::free(this->root);
    }

public:
    unsigned int countNodes() const {
        return BTree::countNodes(this->root);
    }

    unsigned int countLeaves() const {
        return BTree::countLeafNodes(this->root);
    }

    void printInorder() const {
        BTree::printInorder(this->root, std::cout);
    }

    unsigned int getHeight() const {
        return BTree::getHeight(this->root);
    }

    bool isSymmetric() const {
        return BTree::isSymmetric(this->root);
    }

    T sumElements(unsigned int level) {
        return BTree::sumElementsAtLevel(this->root, level);
    }

    std::vector<T> getElementsAtLevel(unsigned int level) {
        std::vector<T> result;
        BTree::getElementsAtLevel(this->root, level, result);
        return result;
    }

public:
    void addPath(const T& value, const std::string& path) {
        BTree::addPath(this->root, value, path);
    }

public:
    static unsigned int countNodes(Node<T>* root) {
        if (!root) {
            return 0;
        }

        return 1 + BTree::countNodes(root->left) + BTree::countNodes(root->right);
    }

    static unsigned int countLeafNodes(Node<T>* root) {
        if (!root) {
            return 0;
        }

        if (root->left == nullptr && root->right == nullptr) {
            return 1;
        }

        return BTree::countLeafNodes(root->left) + BTree::countLeafNodes(root->right);
    }

    static void printInorder(Node<T>* root, std::ostream& output) {
        if (!root) {
            return;
        }
        BTree::printInorder(root->left, output);
        output << root->value << '\t';
        BTree::printInorder(root->right, output);
    }

    static unsigned int getHeight(Node<T>* root) {
        if (!root) {
            return 0;
        }

        return 1 + std::max(BTree::getHeight(root->left), BTree::getHeight(root->right));
    }

    static bool symmetricHelper(Node<T>* left, Node<T>* right) {
        if (!left && !right)
        {
            return true;
        }

        if (!left || !right) {
            return false;
        }

        return left->value == right->value 
            && symmetricHelper(left->left, right->right) 
            && symmetricHelper(left->right, right->left);
    
    }
    static bool isSymmetric(Node<T>* root) {
        if (!root) {
            return true;
        }
        return symmetricHelper(root->left, root->right);
    }

    static T sumElementsAtLevel(Node<T>* root, unsigned int level) {
        if (!root) {
            return T();
        }
        
        if (level == 1) {
            return root->value;
        }

        return sumElementsAtLevel(root->left, level - 1) + sumElementsAtLevel(root->right, level - 1);
    }

    static void getElementsAtLevel(Node<T>* root, unsigned int level, std::vector<T>& result) {
        if (!root) {
            return;
        }
        if (level == 1) {
            result.push_back(root->value);
            return;
        }

        getElementsAtLevel(root->left, level - 1, result);
        getElementsAtLevel(root->right, level - 1, result);
    }

    static void addPath(Node<T>*& root, const T& value, const std::string& path) {
        if (!root) {
            if (path.empty()) {
                root = new Node<T>(value);
                return;
            }
            throw std::logic_error("Invalid path!");
        }

        if (path.empty()) {
            throw std::logic_error("Invalid path! Collision");
        }

        if (path[0] == 'L') {
            addPath(root->left, value, path.substr(1));
            return;
        }
        if (path[0] == 'R') {
            addPath(root->right, value, path.substr(1));
            return;
        }
        throw std::invalid_argument("Invalid path! Illegal char");
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
        return new Node<T>(root->value, BTree::clone(root->left), BTree::clone(root->right));
    }

private:
    Node<T>* root;
};

int main()
{
    Node<int>* root = new Node<int>(1,
        new Node<int>(2,
            new Node<int>(3),
            new Node<int>(4)),
        new Node<int>(5,
            new Node<int>(6),
            new Node<int>(7)));

    BTree<int> btree(root);
    std::cout << btree.countNodes() << std::endl;
    std::cout << btree.countLeaves() << std::endl;
    btree.printInorder();

    std::cout << std::endl;
    std::cout << btree.sumElements(2) << std::endl;

    auto result = btree.getElementsAtLevel(3);
    for (const auto& item : result) {
        std::cout << item << '\t';
    }
    std::cout << std::endl;
    btree.addPath(10, "LRL");
    btree.printInorder();
    std::cout << std::endl;
    try
    {
        btree.addPath(20, "RL");
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
}
