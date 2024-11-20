#include <vector>
#include <string>
#include <stddef.h>

using std::vector,std::swap;

class Tree{
    struct Node{
        int val;
        vector< Node* > children; 
        Node(int value, const vector<Node*>&  children = {}): val(value), children(children){};
    }*root;
    
    void copy(Node*& curr,const Node* other);
    void free(Node* curr);

    public:
    Tree();
    Tree(const Tree& other);
    Tree(Tree&& other);
    Tree& operator=(const Tree& other);
    Tree& operator=(Tree&& other);
    ~Tree();

    void print()const;
    size_t count()const;
    size_t depth()const;
    size_t depthUtil(Node*)const;
    size_t countOnLevel(size_t depth)const;
    void deleteEl(int el);
    void insertElAt(const vector<size_t>& position, int el);
    void insertTreeAt(const vector<size_t>& position, Tree& other);
    int levelSum(size_t index);









    private:
    Node* locatePosition(Node* curr, const vector<size_t>& position,size_t index);
    void formatedPrint(Node* curr,int depth,bool last,std::string& prefix)const;

};