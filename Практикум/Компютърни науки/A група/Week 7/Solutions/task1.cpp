#include <iostream>

// Структура на възел за двусвързан списък
struct Node
{
    int data;
    Node *prev;
    Node *next;

    Node(int val) : data(val), prev(nullptr), next(nullptr) {}
};

// Функция за премахване на дублиращи се елементи
Node *removeDuplicates(Node *head)
{
    // Ако списъкът е празен или има само един елемент
    if (!head || !head->next)
        return head;

    Node *current = head;

    while (current)
    {
        Node *runner = current->next;

        // Търсене на дубликати напред от текущия възел
        while (runner)
        {
            // Ако е открит дубликат
            if (current->data == runner->data)
            {
                // Премахване на възела
                    runner->prev->next = runner->next;
                if (runner->next)
                    runner->next->prev = runner->prev;

                // Временно запазване на възела за изтриване
                Node *toDelete = runner;
                runner = runner->next;

                delete toDelete;
            }
            else
            {
                runner = runner->next;
            }
        }

        current = current->next;
    }

    return head;
}

// Помощни функции за създаване и принтиране на списък
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
    std::cout << " <-> ";

    while (head)
    {
        std::cout << head->data << " <-> ";
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
    int arr[] = {5, 2, 3, 2, 4, 1, 3, 5, 6};
    Node *head = createList(arr, 9);

    printList(head);

    head = removeDuplicates(head);

    printList(head);

    // Освобождаване на паметта
    freeList(head);

    return 0;
}