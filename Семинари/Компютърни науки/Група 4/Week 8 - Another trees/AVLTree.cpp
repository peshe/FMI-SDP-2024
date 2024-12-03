#include <iostream>

class TreeNode
{
    int val;
    TreeNode* l, *r;
    int height;
    
    public:
        TreeNode()
        {
            l = nullptr;
            r = nullptr;
            height = 1;
        }
        int getVal()
        {
            return val;
        }
        void setVal(int val)
        {
            this->val = val;
        }
        int getHeight()
        {
            return height;
        }
        void setHeight(int h)
        {
            this->height = h;
        }
        TreeNode*& getLeft()
        {
            return l;
        }
        TreeNode*& getRight()
        {
            return r;
        }
        void setLeft(TreeNode* l)
        {
            this->l = l;
        }
        void setRight(TreeNode* r)
        {
            this->r = r;
        }
};
class AVLTree
{
    TreeNode* root;
    private:
        bool searchHelper(TreeNode* node, int element)
        {
            if(node == nullptr) return false;
            if(node->getVal() == element) return true;
            if(node->getVal() < element)
            {
                return searchHelper(node->getRight(), element);
            }
            else
            {
                return searchHelper(node->getLeft(), element);
            }
            
        }

        void insertHelper(TreeNode* &node, int element)
        {
            if(node == nullptr)
            {
                node = new TreeNode();
                node->setVal(element);
            }
            else
            {
                if(element < node->getVal())
                {
                    insertHelper(node->getLeft(),element);
                }
                else if(element == node->getVal())
                {
                    return;
                }
                else
                {
                    insertHelper(node->getRight(),element);
                }
            }
            if(node->getLeft() && node->getRight())
            {
                node->setHeight(std::max(node->getLeft()->getHeight(), node->getRight()->getHeight()) + 1);
            }
            else if(node->getLeft())
            {
                node->setHeight(node->getLeft()->getHeight() + 1);
            }
            else if(node->getRight())
            {
                node->setHeight(node->getRight()->getHeight() + 1);
            }
            else
            {
                node->setHeight(1);
            }

            if(balanceFactor(node) > 1)
            {
                std::cout << "Left: " << node->getLeft() << std::endl;
                if(element < node->getLeft()->getVal())
                {
                    rotateRight(node);
                }
                else
                {
                    rotateLeft(node->getLeft());
                    rotateRight(node);
                }
            }
            else if(balanceFactor(node) < -1)
            {
                if(element > node->getRight()->getVal())
                {
                    rotateLeft(node);
                }
                else
                {
                    rotateRight(node->getRight());
                    rotateLeft(node);
                }
            }
        }

        int balanceFactor(TreeNode* node)
        {
            
            return (node->getLeft() ? node->getLeft()->getHeight() : 0) - (node->getRight() ? node->getRight()->getHeight() : 0);
        }
        
    public:

        TreeNode* getRoot() {
            return root;
        }

        void rotateLeft(TreeNode* node)
        {
            int rootValue = node->getRight()->getVal();
            int nodeValue = node->getVal();
            node->setVal(rootValue);
            node->setLeft(new TreeNode());
            node->getLeft()->setVal(nodeValue);
            TreeNode* tmp = node->getRight();
            node->setRight(node->getRight()->getRight());
            delete tmp;
        }
        void rotateRight(TreeNode* node)
        {
            int rootValue = node->getLeft()->getVal();
            int nodeValue = node->getVal();
            node->setVal(rootValue);
            node->setRight(new TreeNode());
            node->getRight()->setVal(nodeValue);
            TreeNode* tmp = node->getLeft();
            node->setLeft(node->getLeft()->getLeft());
            delete tmp;
        }

        AVLTree()
        {
            root = nullptr;
        }
        bool search(int element)
        {
            
            return searchHelper(root, element);
        }

        void insert(int element)
        {
            return insertHelper(root, element);
        }

        
};
int main()
{
    AVLTree a;
    a.insert(7);
    a.insert(6);
    a.insert(5);
}