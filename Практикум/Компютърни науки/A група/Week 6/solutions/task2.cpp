#include <iostream>

// Дефиниция за възел на свързан списък
struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

// Сливане на два сортирани списъка
ListNode *mergeSortedLists(ListNode *l1, ListNode *l2)
{
    // Dummy възел като начало на резултатния списък
    ListNode dummy(0);
    ListNode *tail = &dummy;

    // Докато и двата списъка имат елементи
    while (l1 && l2)
    {
        // Избираме по-малкия възел и го добавяме към резултата
        if (l1->val <= l2->val)
        {
            tail->next = l1;
            l1 = l1->next;
        }
        else
        {
            tail->next = l2;
            l2 = l2->next;
        }
        tail = tail->next;
    }

    // Добавяме останалите елементи от единия от списъците
    tail->next = l1 ? l1 : l2;

    return dummy.next;
}

// Помощна функция за принтиране на списък
void printList(ListNode *head)
{
    while (head)
    {
        std::cout << head->val << " -> ";
        head = head->next;
    }
    std::cout << std::endl;
}

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

int main()
{
    // Създаване на първия сортиран списък
    ListNode *l1 = new ListNode(1);
    l1->next = new ListNode(2);
    l1->next->next = new ListNode(4);

    // Създаване на втория сортиран списък
    ListNode *l2 = new ListNode(1);
    l2->next = new ListNode(3);
    l2->next->next = new ListNode(4);

    // Извеждане на първоначалните списъци
    printList(l1);
    printList(l2);

    // Сливане на списъците
    ListNode *merged = mergeSortedLists(l1, l2);

    // Извеждане на слетия списък
    printList(merged);

    deleteList(merged);

    return 0;
}
