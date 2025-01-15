#include <iostream>

struct Node {
    int data;
    Node *next;

    Node(int x, Node *next = nullptr) : data(x), next(next) {
    }
};

Node *split(Node *head) {
    Node *fast = head;
    Node *slow = head;

    while (fast != nullptr && fast->next != nullptr) {
        fast = fast->next->next;
        if (fast != nullptr) {
            slow = slow->next;
        }
    }

    Node *temp = slow->next;
    slow->next = nullptr;
    return temp;
}

Node *merge(Node *first, Node *second) {
    if (first == nullptr) return second;
    if (second == nullptr) return first;

    if (first->data < second->data) {
        first->next = merge(first->next, second);
        return first;
    } else {
        second->next = merge(first, second->next);
        return second;
    }
}

Node *MergeSort(Node *head) {
    if (head == nullptr || head->next == nullptr)
        return head;

    Node *second = split(head);

    head = MergeSort(head);
    second = MergeSort(second);

    return merge(head, second);
}

void printList(Node *head) {
    Node *current = head;
    while (current != nullptr) {
        std::cout << current->data << " ";
        current = current->next;
    }
    std::cout << std::endl;
}

int main() {
    Node *head = new Node(9);
    head->next = new Node(8);
    head->next->next = new Node(5);
    head->next->next->next = new Node(2);

    head = MergeSort(head);
    printList(head);

    while (head != nullptr) {
        Node *temp = head->next;
        delete head;
        head = temp;
    }
    return 0;
}
