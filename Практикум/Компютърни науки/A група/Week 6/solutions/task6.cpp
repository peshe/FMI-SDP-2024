#include <iostream>
using namespace std;

// Дефиниция на структурата на възел:
struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

// Функция за размяна на съседни възли:
ListNode *swapPairs(ListNode *head)
{
    // Създаване на допълнителен възел:
    ListNode dummy(0);
    dummy.next = head;
    ListNode *prev = &dummy;

    while (prev->next != nullptr && prev->next->next != nullptr)
    {
        // Указатели към текущите възли за размяна:
        ListNode *first = prev->next;
        ListNode *second = first->next;

        // Размяна на възлите:
        first->next = second->next;
        second->next = first;
        prev->next = second;

        // Преместване към следващата двойка:
        prev = first;
    }

    return dummy.next;
}

// Помощна функция за отпечатване на списък:
void printList(ListNode *head)
{
    while (head != nullptr)
    {
        cout << head->val << " -> ";
        head = head->next;
    }
    cout << endl;
}

// Функция за изтриване на списъка:
void deleteList(ListNode *head)
{
    while (head)
    {
        ListNode *temp = head;
        head = head->next;
        delete temp;
    }
}

// Главна функция за тестване:
int main()
{
    // Създаване на списъка:
    ListNode *head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(3);
    head->next->next->next = new ListNode(4);
    head->next->next->next->next = new ListNode(5);

    printList(head);

    // Размяна на съседни възли:
    head = swapPairs(head);
    printList(head);

    // Изтриване на списъка за освобождаване на паметта:
    deleteList(head);

    return 0;
}
