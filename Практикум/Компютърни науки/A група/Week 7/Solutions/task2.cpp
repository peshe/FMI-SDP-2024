#include <iostream>

struct Node
{
    int data;
    Node *prev;
    Node *next;

    Node(int val) : data(val), prev(nullptr), next(nullptr) {}
};

// Помощни функции (които са същите като преди)
int getListLength(Node *head)
{
    int length = 0;
    while (head)
    {
        length++;
        head = head->next;
    }
    return length;
}

// Функция за намиране на възел по позиция
Node *getNodeAtPosition(Node *head, int k)
{
    for (int i = 1; i < k && head; i++)
    {
        head = head->next;
    }
    return head;
}

void swapInPlace(Node* position, Node* newEl){
    if (position->next)
        position->next->prev = newEl;
    if (position->prev)
        position->prev->next = newEl;
    newEl->prev = position->prev;
    newEl->next = position->next;
}

// Функция за размяна на възли
Node *swapNodesSimple(Node *head, int k)
{
    int length = getListLength(head);
    if (!head || k < 1 || k > length)
        return head;

    // Намиране на възлите за размяна
    Node *leftNode = getNodeAtPosition(head, k);
    Node *rightNode = getNodeAtPosition(head, length - k + 1);

    // Създаване на временен възел
    Node *temp = new Node(0);

    // Свързване на временния възел на мястото на левия възел
    swapInPlace(leftNode, temp);
    
    // Премества левия възел на мястото на десния
    swapInPlace(rightNode,leftNode);
    
    // Премества десния възел на мястото на temp
    swapInPlace(temp,rightNode);
    
    // Определяне на новата глава, ако е необходимо
    if (head == leftNode)
        head = rightNode;
    else if (head == rightNode)
        head = leftNode;

    // Освобождаване на паметта от временния възел
    delete temp;

    return head;
}

Node *createList(int arr[], int n)
{
    if (n == 0)
        return nullptr;

    Node *head = new Node(arr[0]);
    Node *current = head;

    for (int i = 1; i < n; i++)
    {
        current->next = new Node(arr[i]);
        current->next->prev = current;
        current = current->next;
    }

    return head;
}

void printList(Node *head)
{
    while (head)
    {
        std::cout << head->data << " <-> ";
        head = head->next;
    }
    std::cout << std::endl;
}

void freeList(Node *head)
{
    while (head)
    {
        Node *temp = head;
        head = head->next;
        delete temp;
    }
}

int main()
{
    int arr1[] = {5, 2, 15, 30, 4, 6};
    Node *head1 = createList(arr1, 6);

    printList(head1);

    head1 = swapNodesSimple(head1, 2);

    printList(head1);

    freeList(head1);

    return 0;
}