
#include <string>
class AVLTree{

    private:
    
    struct Node
    {
        int val;
        Node* left, * right;
        unsigned int height;
        Node(int el, Node* l = nullptr, Node* r = nullptr, unsigned int h = 1 )
            : val(el)
            , left(l)
            , right(r)
            , height(h)
        {}
    } *root;

    void leftRotation(Node*& curr);
    void rightRotation(Node*& curr);

    int BF(Node* curr)const;
    void balance(Node*& curr);
    int getHeight(Node* curr)const;
    void updateHeight(Node* curr);

    Node* copy(Node* curr);
    void free(Node* curr);

    Node* getMin(Node* curr)const;

    Node* extractMin(Node*& curr);

    void insertRec(Node*& curr, int el);
    bool searchRec(Node* curr, int el)const;
    void removeRec(Node*& curr, int el);

    public:

    AVLTree():root(nullptr){};
    AVLTree(const AVLTree& other);
    AVLTree(AVLTree&& other);
    AVLTree& operator=(const AVLTree& other);
    AVLTree& operator=(AVLTree&& other);
    ~AVLTree();

    void insert(int val);
    bool search(int val)const;
    void remove(int val);
    void printF(Node* curr,int depth,bool down, std::string& prefix)const;
    void print()const;

};
