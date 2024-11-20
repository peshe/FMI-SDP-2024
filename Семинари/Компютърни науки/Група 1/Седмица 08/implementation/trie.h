#include <string>

using std::string;

class Trie{
    struct Node{
        int word = 0;
        Node* next[26]{nullptr,};
    }*head;
    void copy(Node*& curr,Node* other);
    void free(Node* curr);

    Trie();
    Trie(const Trie& other);
    Trie(Trie&& other);
    Trie& operator=(const Trie& other);
    Trie& operator=(Trie&& other);
    ~Trie();

    void insert(const string& word);
    void search(const string& word)const;
    void remove(const string& word);
    void print()const;
};