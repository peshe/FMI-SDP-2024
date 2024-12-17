#pragma once

#ifndef BST_HEADER
#define BST_HEADER

#include <string>
#include <stack>
class BST{

    private:
    
    struct Node
    {
        int val;
        Node* left, * right;

        Node(int el, Node* l = nullptr, Node* r = nullptr)
            : val(el)
            , left(l)
            , right(r)
        {}
    } *root;

    Node* copy(Node* curr);
    void free(Node* curr);

    Node* getMin(Node* curr)const;

    Node* extractMin(Node*& curr);

    void insertRec(Node*& curr, int el);
    bool searchRec(Node* curr, int el)const;
    void removeRec(Node*& curr, int el);

    public:

    BST():root(nullptr){};
    BST(const BST& other);
    BST(BST&& other);
    BST& operator=(const BST& other);
    BST& operator=(BST&& other);
    ~BST();

    bool empty()const;
    void insert(int val);
    bool search(int val)const;
    void remove(int val);
    void printF(Node* curr,int depth,bool down, std::string& prefix)const;
    void print();
    /*------------------------------------------------------------------------------*/
    class Iterator;
    Iterator begin();
    Iterator end();
    
    class Iterator{
        Node* ptr;
        std::stack<Node*> path;
        
        void getNext(Node*);
        Iterator(Node* p);

        public:
        operator bool()const;
        Iterator& operator++();
        Iterator operator++(int);
        int operator*()const;
        bool operator==(const Iterator& other)const;
        bool operator!=(const Iterator& other)const;
        friend class BST;
    };
};

#endif