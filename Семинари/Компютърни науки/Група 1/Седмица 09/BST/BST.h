
#include <string>
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

    void insert(int val);
    bool search(int val)const;
    void remove(int val);
    void printF(Node* curr,int depth,bool down, std::string& prefix)const;
    void print();

};
