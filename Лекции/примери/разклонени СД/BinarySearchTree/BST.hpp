/******************************************************************
*  Sample code to the course "Data Structures And Algorithms", FMI
*
* A template class for a Binary Search Tree (BST)
*
* Template type requirements:
*   default constructable
*   assignable
*   equality (==) and comparison (<) operators
*   output operator (<<)
*
* (cc) Petar Armyanov, FMI, 2024
******************************************************************/

#pragma once

#ifndef __BST_HEADER_INCLUDED_
#define __BST_HEADER_INCLUDED_

#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
#include <queue>


namespace fmi::sdp {

template <class DataType>
class BST
{
public:
    BST() : root(nullptr), size(0) {};

    ~BST() noexcept { clear(root); }

    BST(const BST& tree)
        : root(copy(tree.root))
        , size(tree.size) {};

    BST(BST&& tree) noexcept
        : BST()
    {
        std::swap(root, tree.root);
        std::swap(size, tree.size);
    };

    BST& operator=(const BST& tree)
    {
        if (&tree != this) {
			// copy and swap -> strong exception safety
			*this = BST(tree);
        }
        return *this;
    }

    BST& operator=(BST&& rhs) noexcept
    {
        if (this != &rhs) {
            std::swap(root, rhs.root);
            std::swap(size, rhs.size);
        }
        return *this;
    }

    // Standard BST methods
	bool find(const DataType& key) const { return findIterative(root, key); }
    void insert(const DataType& key) { insertIterative(root, key); ++size; }
    bool remove(const DataType& key) { return remove(root, key); }

    size_t getSize() const { return size; }

	// some additional query methods - shows how to check special tree properties
    size_t getHeight() const { return (size_t)height(root); }
    bool isBalanced() const { return balanced(root); }
    bool isPerfectlyBalanced() const { return perfectBalanced(root); }

    // Inorder print -> outputs the elements in sorted order
	void printInorder() const { print(root); std::cout << "\n"; }

    class Iterator;	// Iterates in sorted order
    Iterator begin()
    {
        return Iterator(root);
    }
    Iterator end()
    {
        return Iterator(nullptr);
    }

    class LevelIterator; // BFS iterator
    LevelIterator levelBegin()
    {
        return LevelIterator(root);
    }
    LevelIterator levelEnd()
    {
        return LevelIterator(nullptr);
    }

    // function for static reorder to build weight-balanced tree
    // uses O(N) memory and works in O(N) time
    void staticBalance()
    {
        if (root) {
            std::vector<node*> elements;
            extractNodes(root, elements);
            root = buildPBT(elements, 0, elements.size());
        }
    }

private:
    struct node
    {
        DataType key;
        node* left, * right;

        node(const DataType& key, node* left = nullptr, node* right = nullptr)
            : key(key)
            , left(left)
            , right(right)
        {}
    } *root;

    size_t size;

private:

	// example for prefix traversal
    void clear(node*& root) noexcept
    {
        if (root) {
            clear(root->left);
            clear(root->right);
            delete root;
            root = nullptr;
        }
    }


	// example for postfix traversal
    node* copy(node* root)
    {
		if (!root) return root;
		
		node* result = new node(root->key);
		try{
			result->left = copy(root->left);
			result->right = copy(root->right);
            return result;
		}catch(...){
			clear(result->left);
			clear(result->right);
			throw;
		}
    }


	// simple recursive search
    bool find(const node* root, const DataType& key) const
    {
        if (!root) return false;
        if (root->key == key) return true;
        return key < root->key ? find(root->left, key) : find(root->right, key);
    }

    // An iterative search implementation
	bool findIterative(const node* root, const DataType& key) const
    {
        const node* current = root;
        while (current) {
            if (current->key == key) return true;
            current = current->key < key ? current->right : current->left;
        }
        return false;
    }


	// simple recursive insert. Allows duplication
    void insert(node*& root, const DataType& key)
    {
        if (!root) {
            root = new node(key);
        }
        else {
            insert(key < root->key ? root->left : root->right, key);
        }
    }

    // An iterative insert implementation. Allows duplication
	void insertIterative(node*& root, const DataType& key) const
    {
        if (!root) root = new node(key);
        else {
            node* parent = root;
            node* next = parent->key < key ? parent->right : parent->left;
            while (next) {
                parent = next;
                next = parent->key < key ? parent->right : parent->left;
            }
            if (parent->key < key) 
                parent->right = new node(key);
            else 
                parent->left = new node(key);
        }
    }


    // Recursive removal.
	// No iterative implementation is given for simplicity
	bool remove(node*& root, const DataType& key)
    {
        if (!root) return false;

        if (root->key == key) {
            node* toDel = root;
            if (!root->left) {
                root = root->right;
            }
            else if (!root->right) {
                root = root->left;
            }
            else {
                node* mR = extractMin(root->right);
                mR->left = root->left;
                mR->right = root->right;
                root = mR;
            }
            --size;
            delete toDel;
			return true;
        }
        else {
            return remove(key < root->key ? root->left : root->right, key);
        }
    }

    node* extractMin(node*& root)
    {
        if (root->left) {
            return extractMin(root->left);
        }

        node* n = root;
        root = root->right;
        return n;
    }


    int height(const node* root) const
    {
        if (!root) return 0;
        return 1 + std::max(height(root->left), height(root->right));
    }

    bool balanced(const node* root) const
    {
        if (!root) return true;
        return abs(height(root->left) - height(root->right)) < 2 &&
               balanced(root->left) && balanced(root->right);
    }

    long weight(const node* root) const
    {
        if (!root) return 0;
        return 1 + weight(root->left) + weight(root->right);
    }

    bool perfectBalanced(const node* root) const
    {
        if (!root) return true;
        return labs(weight(root->left) - weight(root->right)) < 2 &&
               perfectBalanced(root->left) && perfectBalanced(root->right);
    }


	void print(const node* root) const
    {
        if (root) {
            print(root->left);
            std::cout << root->key << " ";
            print(root->right);
        }
    }

    void extractNodes(node* root, std::vector<node*>& nodes)
    {
        if (root) {
            extractNodes(root->left, nodes);
            nodes.push_back(root);
            extractNodes(root->right, nodes);
        }
    }

    node* buildPBT(const std::vector<node*>& nodes, size_t left, size_t right)
    {
        if (left >= right) return nullptr;
        
        size_t middle = left + (right - left) / 2;
        node* root = nodes[middle];
        root->left = buildPBT(nodes, left, middle);
        root->right = buildPBT(nodes, middle+1, right);
        return root;
    }

    // DFS (inorder) iterator
	class Iterator
    {
        friend class BST;
    public:
        const DataType operator* ()const
        {
            return current->key;
        }
        const DataType* operator-> ()const
        {
            return &current->key;
        }
        
        operator bool() const
        {
            return current;
        }
        bool operator==(const Iterator& other) const
        {
            return current == other.current;
        }
        bool operator!=(const Iterator& other)const
        {
            return !(*this == other);
        }

        Iterator& operator++()
        {
            if (!front.empty()) {
                current = front.top();
                front.pop();
            }
            if (current) {
                pushLeft(current->right);
            }
            return *this;
        }
        Iterator operator++(int)
        {
            Iterator res(*this);
            ++(*this);
            return res;
        }

    private:
        Iterator(node* root)
        {
            if (root) {
                front.push(nullptr);
                pushLeft(root);
                ++(*this);
            }
        }

	private:
        void pushLeft(node* root)
        {
            while (root) {
                front.push(root);
                root = root->left;
            }
        }

        std::stack<node*> front;
        node* current = nullptr;
    };

    // BFS (level) iterator
	class LevelIterator
    {
        friend class BST;
    public:
        const DataType operator* ()const
        {
            return current->key;
        }
        const DataType* operator-> ()const
        {
            return &current->key;
        }

        operator bool() const
        {
            return current;
        }
        bool operator==(const LevelIterator& other) const
        {
            return current == other.current;
        }
        bool operator!=(const LevelIterator& other) const
        {
            return !(*this == other);
        }

        LevelIterator& operator++()
        {
            if (!front.empty()) {
                current = front.front();
                front.pop();
                pushChildren(current);
            }
            else {
                current = nullptr;
            }
            return *this;
        }
        LevelIterator operator++(int)
        {
            LevelIterator res(*this);
            ++(*this);
            return res;
        }
		
    private:
        LevelIterator(node* root)
        {
            current = root;
            pushChildren(current);
        }
		
    private:
        void pushChildren(node* root)
        {
            if (root) {
                if (root->left) front.push(root->left);
                if (root->right) front.push(root->right);
            }
        }
		
        std::queue<node*> front;
        node* current = nullptr;
    };
};

} //namespace sdp::fmi


#endif //__BST_HEADER_INCLUDED_
