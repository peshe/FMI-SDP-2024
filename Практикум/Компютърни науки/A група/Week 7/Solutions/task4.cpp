#include <iostream>
#include <unordered_map>

// Структура на възел за списък със случайни указатели
struct Node
{
    int data;
    Node *next;
    Node *random;

    Node(int val) : data(val), next(nullptr), random(nullptr) {}
};

// Функция за клониране на списък със случайни указатели
Node *cloneRandomList(Node *head)
{
    // Ако входният списък е празен
    if (!head)
        return nullptr;

    // Стъпка 1: Създаване на нови възли и свързване ги до оригиналните
    Node *current = head;
    while (current)
    {
        Node *newNode = new Node(current->data);
        newNode->next = current->next;
        current->next = newNode;
        current = newNode->next;
    }

    // Стъпка 2: Свързване на случайните указатели
    current = head;
    while (current)
    {
        if (current->random)
        {
            current->next->random = current->random->next;
        }
        current = current->next->next;
    }

    // Стъпка 3: Възстановяване на оригиналните връзки и извличане на новия списък
    Node *newHead = head->next;
    current = head;
    Node *newCurrent = newHead;

    while (current)
    {
        // Възстановяване на next указателите
        current->next = newCurrent->next;
        current = current->next;

        if (current)
        {
            newCurrent->next = current->next;
            newCurrent = newCurrent->next;
        }
    }

    return newHead;
}

// Помощни функции
void printList(Node *head)
{
    while (head)
    {
        std::cout << "(" << head->data;
        if (head->random)
        {
            std::cout << ", Random: " << head->random->data;
        }
        std::cout << ") -> ";
        head = head->next;
    }
    std::cout << std::endl;
}

// Функция за освобождаване на паметта
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
    // Създаване на оригинален списък
    Node *head = new Node(1);
    head->next = new Node(2);
    head->next->next = new Node(3);
    head->next->next->next = new Node(4);

    // Свързване на случайни указатели
    head->random = head->next->next;                   // 1 сочи към 3
    head->next->random = head;                         // 2 сочи към 1
    head->next->next->random = head->next->next->next; // 3 сочи към 4
    head->next->next->next->random = head->next;       // 4 сочи към 2

    // Клониране на списъка
    Node *clonedHead = cloneRandomList(head);

    // clonedHead->next->next->random->data = -1; // Проверка дали можем да променим само клонирания без да променяме оригиналния

    printList(head);
    printList(clonedHead);

    // Освобождаване на паметта
    freeList(head);
    freeList(clonedHead);

    return 0;
}
