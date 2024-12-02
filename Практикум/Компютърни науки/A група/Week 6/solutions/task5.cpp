#include <iostream>
using namespace std;

// Дефиниция за възел на свързан списък
struct ListNode
{
    int data;
    ListNode *next;

    ListNode(int val) : data(val), next(nullptr) {}
};

// Функция за освобождаване на паметта
void deleteList(ListNode *head)
{
    while (head)
    {
        ListNode *temp = head;
        head = head->next;
        delete temp;
    }
}

// Функция за превъртане на списъка
void rotateList(ListNode *&head, int k, char direction)
{
    if (!head || k == 0)
        return;

    // Намиране на големината
    int n = 1;
    ListNode *tail = head;
    while (tail->next)
    {
        tail = tail->next;
        n++;
    }

    // Нормализиране на k
    k = k % n;
    if (k == 0)
        return;

    // k на брой L ротации са точно (n - k) R ротации
    if (direction == 'L')
    {
        k = n - k;
    }

    // Кръгов списък
    tail->next = head;

    // Намиране на новата опашка
    int stepsToNewTail = n - k;
    ListNode *newTail = head;
    for (int i = 1; i < stepsToNewTail; i++)
    {
        newTail = newTail->next;
    }

    // Нова глава и нова опашка (премахваме кръговия списък)
    head = newTail->next;
    newTail->next = nullptr;
}

void printList(ListNode *head)
{
    while (head)
    {
        cout << head->data;
        if (head->next)
            cout << " -> ";
        head = head->next;
    }
    cout << endl;
}

int main()
{
    ListNode *head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(3);
    head->next->next->next = new ListNode(4);
    head->next->next->next->next = new ListNode(5);

    printList(head);

    rotateList(head, 2, 'L');
    cout << "2 L:" << endl;
    printList(head);

    rotateList(head, 1, 'R');
    cout << "1 R:" << endl;
    printList(head);

    deleteList(head);

    return 0;
}
