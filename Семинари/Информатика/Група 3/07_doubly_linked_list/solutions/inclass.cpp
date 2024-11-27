#include <iostream>
#include <list>

template<class T>
struct Node {
    T data;
    Node<T>* next;
    Node<T>* prev;

    Node(T data, Node<T>* next = nullptr, Node<T>* prev = nullptr)
        : data(data), next(next), prev(prev) {}

    ~Node() {
        delete next;
    }

    void add(T value) {
        Node<T>* last = this;
        while (last->next != nullptr) {
            last = last->next;
        }
        last->next = new Node<T>(value, nullptr, last);
    }

    void print() const {
        const Node<T>* current = this;
        while (current->next != nullptr) {
            std::cout << current->data << " <-> ";
            current = current->next;
        }
        std::cout << current->data << std::endl;
    }
};

template <class T>
void insertSorted(Node<T>*& head, const T& value) {
    Node<T>* newNode = new Node<T>(value);

    if (!head) {
        head = newNode;
        return;
    }

    if (value <= head->data) {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
        return;
    }

    Node<T>* current = head;
    while (current->next && current->next->data < value) {
        current = current->next;
    }
    
    newNode->next = current->next;
    newNode->prev = current;
    current->next = newNode;
    if (newNode->next) {
        newNode->next->prev = newNode;
    }
    
}

void test1() {
    Node<int>* head = new Node<int>(3);
    head->print();
    insertSorted(head, 4);
    std::cout << "After:\n";
    head->print();
}

void test2() {
    Node<int>* head = new Node<int>(3);
    head->print();
    insertSorted(head, 2);
    std::cout << "After:\n";
    head->print();
}

void test3() {
    Node<int>* head = new Node<int>(1);
    head->add(2);
    head->add(4);
    head->print();
    insertSorted(head, 3);
    std::cout << "After:\n";
    head->print();
}

template<class T>
void insertSorted(std::list<T>& ll, const T& value) {
    auto iter = ll.begin();

    while (iter != ll.end()) {
        if (*iter > value) {
            ll.insert(iter, value);
            break;
        }
        iter++;
    }

    if (iter == ll.end()) {
        ll.push_back(value);
    }
}

bool makeTotal(Node<int>* head) {
    // if empty, just one or 2, do nothing
    if (!head || !head->next || !head->next->next)
    {
        return false;
    }

    bool isBalanced = true;
    Node<int>* current = head->next;
    Node<int>* previous = head;
    while (current->next) {
        if (previous->data + current->next->data != current->data)
        {
            isBalanced = false;
            break;
        }
        previous = current;
        current = current->next;
    }
    
    if (isBalanced) {
        return true;
    }

    current = head->next;
    previous = head;
    while (current->next) {
        if (previous->data + current->next->data == current->data)
        {
            Node<int>* toDelete = current;
            previous->next = current->next;
            current = current->next;

            //if using dtor with delete next
            toDelete->next = nullptr;
            delete toDelete;
        }
        else
        {
            previous = current;
            current = current->next;
        }
    }

    return isBalanced;

}

void totalTest1() {
    Node<int>* head = new Node<int>(1);
    head->add(4);
    head->add(3);
    head->add(-1);
    head->add(-4);

    std::cout << std::boolalpha << makeTotal(head) << std::endl;
    head->print();

    delete head;
}

void totalTest2() {
    Node<int>* head = new Node<int>(10);
    head->add(5);
    head->add(-5);
    head->add(-15);
    head->add(2);

    std::cout << std::boolalpha << makeTotal(head) << std::endl;
    head->print();

    delete head;
}

int main()
{
   /* test1();
    test2();
    test3();*/

    /*std::list<int> lst;
    lst.push_back(1);
    lst.push_back(2);
    lst.push_back(4);

    insertSorted(lst, 3);

    for (const auto& item : lst) {
        std::cout << item << std::endl;
    }*/

    totalTest1();
    totalTest2();

    return 0;
}
