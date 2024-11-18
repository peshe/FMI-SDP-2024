/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* prev;
    Node* next;
    Node* child;
};
*/

class Solution {
public:
    Node* flatten(Node* head) {
        Node* current = head;
        while(current) {
            if(current->child) {
                Node* flattenedHead = flatten(current->child);
                Node* flattenedEnd = getLast(flattenedHead);
                Node* next = current->next;

                flattenedEnd->next = next;
                flattenedHead->prev = current;

                current->next = flattenedHead;
                current->child = nullptr;
                
                if(next) {
                    next->prev = flattenedEnd;
                }
                
                current = next;
            }
            else {
                current = current->next;
            }
        }
        return head;
    }
private:
    Node* getLast(Node* lst) {
        if(!lst) {
            return nullptr;
        }
        Node* current = lst;
        while(current->next) {
            current = current->next;
        }
        return current;
    }
};