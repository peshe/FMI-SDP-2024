#include <iostream>

struct Node {
    int value;
    Node *next;

    Node(int value, Node *next = nullptr)
            : value(value), next(next) {}

    ~Node() {
        delete next;
    }

    void add(int value) {
        Node *last = this;
        while (last->next != nullptr) {
            last = last->next;
        }
        last->next = new Node(value);
    }

    void print() const {
        const Node *current = this;
        while (current->next != nullptr) {
            std::cout << current->value << " -> ";
            current = current->next;
        }
        std::cout << current->value << std::endl;
    }
};

bool makeTotal(Node *head) {
    // if empty or just one element, return false and do nothing
    if (!head || !head->next) {
        return false;
    }

    Node *current = head->next;
    // if there are just 2
    if (!current->next) {
        return false;
    }

    bool isBalanced = true;
    Node *previous = head;
    while (current->next) {
        if (previous->value + current->next->value != current->value) {
            isBalanced = false;
        }
        previous = current;
        current = current->next;
    }

    if (!isBalanced) {
        current = head->next;
        previous = head;
        while (current->next) {
            if (previous->value + current->next->value == current->value) {
                Node *toDelete = current;
                previous->next = current->next;
                current = current->next;
                toDelete->next = nullptr;
                delete toDelete;
            } else {
                previous = current;
                current = current->next;
            }
        }
    }

    return isBalanced;
}

void test1() {
    Node *head = new Node(1);
    head->add(4);
    head->add(3);
    head->add(-1);
    head->add(-4);

    std::cout << std::boolalpha << makeTotal(head) << std::endl;
    head->print();

    delete head;
}

void test2() {
    Node *head = new Node(10);
    head->add(5);
    head->add(-5);
    head->add(-15);
    head->add(2);

    std::cout << std::boolalpha << makeTotal(head) << std::endl;
    head->print();

    delete head;
}

int main() {
    test1();
    test2();
}
