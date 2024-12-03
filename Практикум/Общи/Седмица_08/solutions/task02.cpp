void decode_huff(node * root, string s) {
    for (size_t i = 0; i < s.size();) {
        const node* currentNode = root;
        while (currentNode->data == 0) {
            if (s[i] == '0') {
                currentNode = currentNode->left;
            }
            else {
                assert(s[i] == '1');
                currentNode = currentNode->right;
            }
            ++i;
        }
        cout << currentNode->data;
    }
}
