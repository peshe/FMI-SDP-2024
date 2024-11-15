struct Node {
    int val;
    Node* next;

    Node(int val)
    : val(val), next(nullptr)
    {}
};

class Solution {
public:
    int findTheWinner(int n, int k) {
        Node* first = new Node(1);
        Node* current = first;
        for (int i = 2; i <= n; ++i) {
            current->next = new Node(i);
            current = current->next;
        }
        current->next = first;

        while (current->next != current) {
            for (int i = 1; i < k; ++i) {
                current = current->next;
            }
            Node* toDelete = current->next;
            current->next = toDelete->next;
            delete toDelete;
        }

        int result = current->val;
        delete current;
        return result;
    }
};
