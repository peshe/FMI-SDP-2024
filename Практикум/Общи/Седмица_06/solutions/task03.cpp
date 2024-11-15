class Solution {
public:
    Node* flatten(Node* head) {
        Node* flattenedTail = nullptr;
        return flatten(head, flattenedTail);
    }

private:
    Node* flatten(Node* head, Node*& flattenedTail /*out*/) {
        if (head == nullptr) {
            flattenedTail = nullptr;
            return nullptr;
        }

        Node* flattenedNextHead = flatten(head->next, flattenedTail);

        Node* flattenedChildTail = nullptr;
        Node* flattenedChildHead = flatten(head->child, flattenedChildTail);

        if (flattenedChildHead != nullptr) {
            head->next = flattenedChildHead;
            assert(flattenedChildHead->prev == nullptr);
            flattenedChildHead->prev = head;

            assert(flattenedChildTail != nullptr);
            flattenedChildTail->next = flattenedNextHead;

            if (flattenedNextHead != nullptr) {
                assert(flattenedTail != nullptr);
                assert(flattenedNextHead->prev == head);
                flattenedNextHead->prev = flattenedChildTail;
            }
            else {
                assert(flattenedTail == nullptr);
                flattenedTail = flattenedChildTail;
            }

            head->child = nullptr;
        }
        else {
            assert(flattenedChildTail == nullptr);
            assert(head->child == nullptr);

            if (flattenedNextHead != nullptr) {
                assert(flattenedTail != nullptr);
                assert(flattenedNextHead->prev == head);
            }
            else {
                assert(flattenedTail == nullptr);
                flattenedTail = head;
            }
        }

        return head;
    }
};
