#include <iostream>

// Структура на възела на двусвързания списък
struct Node
{
    int data;
    Node *next;
    Node *prev;
    Node(int val) : data(val), next(nullptr), prev(nullptr) {}
};

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

// Функция за размяна на възли на място в списък (newEl трябва да е извън списъка)
void swapInPlace(Node* position, Node* newEl){
    if (position->next)
        position->next->prev = newEl;
    if (position->prev)
        position->prev->next = newEl;
    newEl->prev = position->prev;
    newEl->next = position->next;
}


// Функция за размяна на възли
Node *swapNodesSimple(Node *head, Node *leftNode, Node *rightNode)
{
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

// Функция за освобождаване на паметта
void freeList(Node *head)
{
    while (head)
    {
        Node *temp = head;
        head = head->next;
        delete temp; // Освобождаваме паметта на текущия възел
    }
}

// Функция за създаване на двусвързания списък от масив
Node *createList(int arr[], int n)
{
    if (n == 0)
    {
        return nullptr; // Ако масивът е празен, връщаме null
    }

    Node *head = new Node(arr[0]); // Създаваме първия възел
    Node *current = head;

    for (int i = 1; i < n; ++i)
    {
        // Създаваме нов възел и го свързваме с предходния
        current->next = new Node(arr[i]);
        current->next->prev = current;
        current = current->next; // Придвижваме се към новия възел
    }

    return head; // Връщаме началото на списъка
}

// Функция за сортиране на почти сортиран двусвързания списък с отместване K
Node *sortDoublyLinkedList(Node *head, int K)
{
    if (!head)
        return nullptr; // Ако списъкът е празен

    Node *current = head;

    // Преглеждаме всеки възел
    while (current)
    {
        Node *minNode = current;
        Node *temp = current;

        // Сравняваме с до K съседни възела
        for (int i = 0; i < K && temp != nullptr; ++i)
        {
            if (temp->next && temp->next->data < minNode->data)
            {
                minNode = temp->next;
            }
            temp = temp->next;
        }

        // Ако сме намерили минимален възел в следващите K позиции
        if (minNode != current)
        {
            // Разменяме данните
            swapNodesSimple(head, current, minNode);
        }

        current = minNode->next;
    }

    return head;
}

// Функция за отпечатване на двусвързания списък
void printList(Node *head)
{
    std::cout << " <-> ";

    Node *temp = head;
    while (temp)
    {
        std::cout << temp->data << " <-> ";
        temp = temp->next;
    }
    std::cout << std::endl;
}

int main()
{
    int arr[] = {2, 5, 15, 3, 4};
    int n = sizeof(arr) / sizeof(arr[0]);

    // Създаване на двусвързания списък
    Node *head = createList(arr, n);

    printList(head);

    // Сортиране на списъка с отместване K
    int K = 2;
    head = sortDoublyLinkedList(head, K);

    printList(head);

    // Освобождаване на паметта след използване
    freeList(head);

    return 0;
}
