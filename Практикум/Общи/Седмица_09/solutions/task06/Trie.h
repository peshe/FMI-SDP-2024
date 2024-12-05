#include <string>
#include <utility>
#include <vector>


struct TrieNode
{
    bool canTerminate;
    std::vector<std::pair<char, TrieNode*>> next;

    TrieNode()
    : canTerminate(false), next{}
    {}
    ~TrieNode();

    TrieNode* find(char c);
    TrieNode* add(char c);

private:
    TrieNode(const TrieNode&);
    TrieNode& operator= (const TrieNode&);
};


class Trie
{
public:
    void add(const std::string& word);
    bool remove(const std::string& word);

    void printWithPrefix(const std::string& prefix) const;

private:
    TrieNode* find(const std::string& prefix);

private:
    TrieNode root;
};
