#include <iostream>

class Node {
public:
    int val;
    Node* prev;
    Node* next;
    Node* child;

    Node(int x, Node* prev = nullptr, Node* next = nullptr, Node* child = nullptr)
        : val(val), prev(prev), next(next), child(child) {}
};

void flatten(Node* head, Node* &fst, Node* &lst)
{
    if (head == nullptr) return;

    if (fst == nullptr)
    {
        fst = lst = new Node(head->val);
    }
    else
    {
        lst->next = new Node(head->val);
        lst->next->prev = lst;
        lst = lst->next;
    }

    if (head->child != nullptr)
    {
        flatten(head->child, fst, lst);
    }

    flatten(head->next, fst, lst);
}

Node* flatten(Node* head)
{
    Node* fst = nullptr;
    Node* lst = nullptr;

    flatten(head, fst, lst);

    return fst;
}
