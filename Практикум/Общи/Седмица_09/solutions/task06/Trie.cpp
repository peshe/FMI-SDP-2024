#include "Trie.h"

#include <cassert>
#include <iostream>
#include <string>
#include <utility>


using std::cout;
using std::string;


TrieNode::~TrieNode() {
    for (auto& i : next) {
        delete i.second;
    }
}

TrieNode* TrieNode::find(char c) {
    for (auto& i : next) {
        if (i.first == c) {
            return i.second;
        }
    }
    return nullptr;
}

TrieNode* TrieNode::add(char c) {
    TrieNode* result = new TrieNode();
    next.push_back(std::make_pair(c, result));
    return result;
}


void Trie::add(const string& word) {
    TrieNode* current = &root;

    for (char c : word) {
        TrieNode* next = current->find(c);

        if (next == nullptr) {
            next = current->add(c);
        }

        assert(next != nullptr);
        current = next;
    }

    current->canTerminate = true;
}

bool Trie::remove(const string& word) {
    TrieNode* node = find(word);
    if (node == nullptr) {
        return false;
    }

    bool removed = node->canTerminate;
    node->canTerminate = false;
    return removed;
}

static void printTrieNode(const string& prefix, const TrieNode* node) {
    if (node == nullptr) {
        return;
    }

    if (node->canTerminate) {
        cout << prefix << '\n';
    }

    for (auto& i : node->next) {
        printTrieNode(prefix + i.first, i.second);
    }
}

void Trie::printWithPrefix(const string& prefix) const {
    const TrieNode* node = const_cast<Trie*>(this)->find(prefix);
    printTrieNode(prefix, node);
    cout << std::endl;
}

TrieNode* Trie::find(const string& prefix) {
    TrieNode* current = &root;

    for (char c : prefix) {
        TrieNode* next = current->find(c);

        if (next == nullptr) {
            return nullptr;
        }

        current = next;
    }

    return current;
}
