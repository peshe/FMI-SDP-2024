#include <string>

using std::string;

class Trie{
    struct Node{
        int word = 0;
        Node* next[26]{nullptr,};
    }*head;
    bool hasDescendants(Node* curr)const;
    void removeRec(const string& word, int index, Node* curr);
    void insertRec(const string& word, int index, Node* curr);
    void printRec(Node* curr,string& word)const;
    void copy(Node*& curr,Node* other);
    void free(Node* curr);
    
    public:
    Trie();
    Trie(const Trie& other);
    Trie(Trie&& other);
    Trie& operator=(const Trie& other);
    Trie& operator=(Trie&& other);
    ~Trie();

    void insert(const string& word);

    bool search(const string& word)const;
    void remove(const string& word);
    void print()const;
};