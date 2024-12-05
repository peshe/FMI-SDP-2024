#include "Trie.h"


int main() {
    Trie trie;

    trie.add("a");
    trie.printWithPrefix("");

    trie.add("abc");
    trie.printWithPrefix("");

    trie.remove("a");
    trie.printWithPrefix("");

    trie.add("b");
    trie.add("bcd");
    trie.printWithPrefix("");

    trie.printWithPrefix("b");

    trie.printWithPrefix("bc");

    trie.printWithPrefix("bcde");

    trie.printWithPrefix("e");

    return 0;
}
