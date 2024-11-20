/******************************************************************
*  Sample code to the course "Data Structures And Algorithms", FMI
*
* An educational class, representing generic tree, stored as
* 'First child - Right siblink'
*
* (cc) Petar Armyanov, FMI, 2024
*******************************************************************/

#pragma once

#ifndef __TREE_HEADER_INCLUDED_
#define __TREE_HEADER_INCLUDED_

#include <iostream>
#include <queue>

namespace fmi {
namespace sdp {

template <class DataType>
class Tree
{
public:
    Tree() : root(nullptr), size(0) {};

    ~Tree() noexcept { clear(root); }

    Tree(const Tree& tree)
        : root(copy(tree.root))
        , size(tree.size) {};

    Tree(Tree&& tree) noexcept
        : Tree()
    {
        std::swap(root, tree.root);
        std::swap(size, tree.size);
    };

    Tree& operator=(const Tree& tree)
    {
        if (&tree != this) {
            clear(root);
            root = copy(tree.root);
            size = tree.size;
        }
        return *this;
    }

    Tree& operator=(Tree&& rhs) noexcept
    {
        if (this != &rhs) {
            std::swap(root, rhs.root);
            std::swap(size, rhs.size);
        }
        return *this;
    }

    bool find(const DataType& key) const { return find(root, key); }
    bool insert(const DataType& key, int path[])
    {
        if (insert(root, key, path)) {
            ++size;
            return true;
        }
        return false;
    }
    bool remove(const DataType& key) { return remove(root, key); }

    size_t getSize() const { return size; }
    size_t getHeight() const { return height(root); }

    template <class Function>
    void map(const Function& fun) { map(fun, root); }

    void print() {
        map([](const DataType& x) {std::cout << x << ' '; });
        std::cout << '\n';
    }

    void printByLevels() const { printByLevels(root); }
private:
    struct node
    {
        DataType data;
        node *child, *sibling;

        node(const DataType& data, node* child = nullptr, node* sibling = nullptr)
            : data(data)
            , child(child)
            , sibling(sibling)
        {}
    } *root;

    size_t size;

private:

    void clear(node* root)
    {
        if (root) {
            clear(root->child);
            clear(root->sibling);
            delete root;
        }
    }

    node* copy(node* root)
    {
        return root ?
            new node(root->data, copy(root->child), copy(root->sibling)) :
            root;
    }

    bool find(const node* root, const DataType& key) const
    {
        if (!root) return false;
        if (root->data == key) return true;
        return find(root->sibling, key) || find(root->child, key);
    }

    size_t height(const node* root) const
    {
        if (!root) return 0;
        return std::max(1+height(root->child), height(root->sibling));
    }

    template <class Function>
    void map(const Function& fun, node* root) {
        if (root) {
            fun(root->data);
            map(fun, root->sibling);
            map(fun, root->child);
        }
    }

    bool remove(node*& root, const DataType& key) {
        if (!root) return false;

        if (root->data == key) {
            node* toDelete = root;
            if (!root->child) {
                root = root->sibling;
            }
            else if (root->sibling){
                node* it = root->child;
                while (it->sibling) it = it->sibling;
                it->sibling = root->sibling->child;
                root->sibling->child = root->child;
                root = root->sibling;
            }
            else {
                root = root->child;
            }
            --size;
            delete toDelete;
            return true;
        }
        else {
            return remove(root->sibling, key) || remove(root->child, key);
        }
    }

    bool insert(node*& root, const DataType& key, const int* path)
    {
        //A siblink to the root
        if (path[0] < 0) {
            root = new node(key, nullptr, root);
            return true;
        }

        //No such child? Wrong path!
        if (!root) return false;

        // Attach element in the roots children list
        if (path[0] == 0) {
            return insert(root->child, key, path + 1);
        }

        // Find the right child in the list
        node* it = root;
        int pos = path[0];
        while (it->sibling && pos > 0) {
            it = it->sibling;
            --pos;
        }
        return it->sibling ? insert(it->sibling->child, key, path + 1) : false;
    }

    // A BFS search with sentinel in the queue
    void printByLevels(const node* root) const
    {
        if (!root) return;
        std::queue<const node*> front;
        front.push(root);
        front.push(nullptr);
        for (;;) {
            const node* current = front.front();
            front.pop();
            if (!current) {
                std::cout << '\n';
                if (front.empty()) return;
                front.push(nullptr);
            }
            else {
                std::cout << current->data << ' ';
                for (const node* it = current->child; it; it = it->sibling) {
                    front.push(it);
                }
            }
        }
    }
};

} //namespace sdp
} //namespace fmi

#endif //__TREE_HEADER_INCLUDED_
