#include <iostream>
#include <queue>

class TreeNode
{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode* parrent;

    public:
        TreeNode(int val, TreeNode* left, TreeNode* right, TreeNode* parrent)
        {
            this->val = val;
            this->left = left;
            this->right = right;
            this->parrent = parrent;
        }
        TreeNode* getLeft() {return left;}
        TreeNode* getRight() {return right;}
        TreeNode* getParrent() {return parrent;}
        int getValue(){return val;}

        void setLeft(TreeNode* left) {this->left = left;}
        void setRight(TreeNode* right) {this->right = right;}
        void setValue(int value) {this->val = value;}
        void setParrent(TreeNode* parrent) {this->parrent = parrent;}
};

class BinarySearchTree
{
    private:
        TreeNode* root;

        TreeNode* buildHelper(int *arr, int size)
        {
            //std::cout << *arr << std::endl;
            if(size <= 0) return nullptr;
            TreeNode* result = new TreeNode(arr[size/2], buildHelper(arr, size % 2 == 0 ? size/2 - 1 : size / 2) , buildHelper(arr + size/2 + 1, size % 2 == 0 ? size/2-1 : size/2), nullptr);
            return result;
        }

        TreeNode* searchNode(TreeNode* current, int element)
        {
            if(current == nullptr)
            {
                return nullptr;
            }
            else if(current->getValue() == element)
            {
                return current;
            }
            else
            {
                return current->getValue() < element ? searchNode(current->getRight(), element) : searchNode(current->getLeft(), element);
            }
        }
        void addElementHelper(TreeNode* node, int element)
        {
            if(element == node->getValue())
            {
                return;
            }
            if(element < node->getValue())
            {
                if(node->getLeft() == nullptr)
                {
                    node->setLeft(new TreeNode(element, nullptr, nullptr, node));
                }
                else 
                {
                    addElementHelper(node->getLeft(), element);
                }
            }
            else
            {
                if(node->getRight() == nullptr)
                {
                    node->setRight(new TreeNode(element, nullptr, nullptr, node));
                }
                else 
                {
                    addElementHelper(node->getRight(), element);
                }

            }

        }

        void deleteNodeHelper(TreeNode* _root, int element)
        {
            TreeNode* elementToDelete = searchNode(_root, element);
            if(elementToDelete == nullptr)
            {
                return;
            }
            if(elementToDelete->getLeft() == nullptr && elementToDelete->getRight() == nullptr)
            {

                TreeNode* par = elementToDelete->getParrent();
                if(par->getLeft() == elementToDelete)
                {
                    delete elementToDelete;
                    par->setLeft(nullptr);
                }
                else
                {
                    delete elementToDelete;
                    par->setRight(nullptr);
                }
            }
            else if(elementToDelete->getLeft() == nullptr)
            {
                TreeNode* par = elementToDelete->getParrent();
                if(par->getLeft() == elementToDelete)
                {
                    par->setLeft(elementToDelete->getRight());
                }
                else
                {
                    
                    par->setRight(elementToDelete->getRight());
                }
                delete elementToDelete;
            }
            else if(elementToDelete->getRight() == nullptr)
            {
                TreeNode* par = elementToDelete->getParrent();
                if(par->getLeft() == elementToDelete)
                {
                    par->setLeft(elementToDelete->getLeft());
                }
                else
                {
                    par->setRight(elementToDelete->getLeft());
                }
                delete elementToDelete;
            }
            else
            {
                int tmp = elementToDelete->getValue();
                elementToDelete->setValue(elementToDelete->getRight()->getValue());
                elementToDelete->getRight()->setValue(tmp);
                deleteNodeHelper(elementToDelete->getRight(), element);

            }
        }
        void fixParrents(TreeNode* node)
        {
            if(node == nullptr)
            {
                return;
            }
            if(node->getLeft() != nullptr)
            {
                node->getLeft()->setParrent(node);
            }
            if(node->getRight() != nullptr)
            {
                node->getRight()->setParrent(node);
            }  
            fixParrents(node->getLeft());
            fixParrents(node->getRight());
        }

    public:

        void addElement(int element)
        {
            if(root == nullptr)
            {
                root = new TreeNode(element, nullptr, nullptr, nullptr);
            }
            else 
            {
                addElementHelper(root, element);
            }
        }
        void buildBySortedArray(int* arr, int size)
        {
            root = buildHelper(arr, size);
            fixParrents(root);

        }

        bool search(int element)
        {
            return searchNode(root, element) != nullptr;
        }

        void printByLevels()
        {
            std::queue<TreeNode*> qu;
            qu.push(root);
            while(!qu.empty())
            {
                TreeNode* node = qu.front();
                std::cout << node->getValue();
                qu.pop();
                if(node->getLeft() != nullptr)
                {
                    qu.push(node->getLeft());
                }
                if(node->getRight() != nullptr)
                {
                    qu.push(node->getRight());
                }

            }
        }

        
        void deleteNode(int element)
        {
            deleteNodeHelper(root, element);
        }
};
int main()
{
    int arr[] = {4, 5, 6, 7, 8, 9, 10 };
    BinarySearchTree *bst = new BinarySearchTree();
    bst->buildBySortedArray(arr, 7);
    bst->printByLevels();
    std::cout << std::endl;
    std::cout << std::boolalpha << bst->search(11) << std::endl;
    bst->deleteNode(6);

    std::cout << std::endl;
    std::cout << std::boolalpha << bst->search(11) << std::endl;
    bst->printByLevels();
}