/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;

    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
*/

class Solution {
public:
    Node* copyRandomList(Node* head) {
        map<Node*, Node*> oldToNew;

        for (Node* node = head; node != nullptr; node = node->next) {
            Node* newNode = new Node(node->val);
            oldToNew[node] = newNode;
        }
        oldToNew[nullptr] = nullptr;

        for (Node* node = head; node != nullptr; node = node->next) {
            Node* newNode = oldToNew[node];
            newNode->next = oldToNew[node->next];
            newNode->random = oldToNew[node->random];
        }

        return oldToNew[head];
    }
};
