#include <iostream>

// Дефиниция за възел на свързан списък
struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

// Премахване на дублиращи се елементи от сортиран списък
ListNode *removeDuplicates(ListNode *head)
{
    // Ако списъкът е празен или има само един елемент, връщаме го без промяна
    if (!head || !head->next)
        return head;

    // Текущ указател за обхождане на списъка
    ListNode *current = head;

    // Докато имаме следващ възел
    while (current->next)
    {
        // Ако текущият възел и следващият имат еднаква стойност
        if (current->val == current->next->val)
        {
            // Съхраняваме възела за изтриване
            ListNode *toDelete = current->next;
            // Свързваме текущия възел със следващия след дубликата
            current->next = current->next->next;
            // Освобождаваме паметта на дубликата
            delete toDelete;
        }
        else
        {
            // Преминаваме към следващия възел
            current = current->next;
        }
    }

    return head;
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
    // Създаване на тестов списък с дублиращи се елементи
    ListNode *head = new ListNode(1);
    head->next = new ListNode(1);
    head->next->next = new ListNode(2);
    head->next->next->next = new ListNode(3);
    head->next->next->next->next = new ListNode(3);

    // Извеждане на оригиналния списък
    printList(head);

    // Премахване на дублиращите се елементи
    head = removeDuplicates(head);

    // Извеждане на списъка без дублирани елементи
    printList(head);

    deleteList(head);

    return 0;
}
