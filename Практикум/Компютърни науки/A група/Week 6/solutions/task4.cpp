#include <iostream>
#include <utility>

// Дефиниция за възел на свързан списък
struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

// Разделяне на списъка на две части по средата
void splitListMid(ListNode *head, ListNode *&first, ListNode *&second)
{
    // Ако списъкът е празен
    if (!head)
    {
        first = nullptr;
        second = nullptr;
        return;
    }

    ListNode *slow = head;
    ListNode *fast = head;
    ListNode *prevSlow = nullptr;

    // Бавният указател ще спре в средата, а бързият в края
    while (fast && fast->next)
    {
        fast = fast->next->next; // Бързият се движи с 2 стъпки
        prevSlow = slow;         // Предишният за бавния (нужен за прекъсване)
        slow = slow->next;       // Бавният се движи с 1 стъпка
    }

    // Проверка за четен и нечетен брой елементи - тук влизаме само при нечетен (ако беше четен щяхме да сме на nullptr)
    if (fast)
    {
        prevSlow = slow;
        slow = slow->next;
    }

    // Прекъсваме връзката между двете части
    if (prevSlow)
    {
        prevSlow->next = nullptr;
    }

    // Първата половина започва от началото на списъка
    first = head;

    // Втората половина започва от "бавния" указател
    second = slow;
}

void splitEvenOdd(ListNode *head, ListNode *&oddHead, ListNode *&evenHead)
{
    oddHead = head;               // Нечетните започват от първия елемент
    ListNode *oddTail = head;     // Указател за края на нечетния подсписък
    evenHead = nullptr;           // Начало на четния подсписък
    ListNode *evenTail = nullptr; // Указател за края на четния подсписък

    ListNode *current = head->next; // Започваме от втория елемент
    bool isEven = true;             // Флаг за редуване

    while (current)
    {
        if (isEven)
        {
            if (!evenHead)
            {
                evenHead = current; // Запазваме началото на четните
                evenTail = current; // Поставяме края на четните
            }
            else
            {
                evenTail->next = current; // Добавяме към четните
                evenTail = current;       // Обновяваме края
            }
        }
        else
        {
            oddTail->next = current; // Добавяме към нечетните
            oddTail = current;       // Обновяваме края
        }
        isEven = !isEven; // Редуваме четни/нечетни
        current = current->next;
    }

    // Прекъсваме двата подсписъка
    if (evenTail)
        evenTail->next = nullptr;
    oddTail->next = nullptr;
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
    // Създаване на тестов списък
    ListNode *head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(3);
    head->next->next->next = new ListNode(4);
    head->next->next->next->next = new ListNode(5);

    // Демонстрация на разделяне по средата
    std::cout << "List:" << std::endl;
    printList(head);

    ListNode *first = nullptr;
    ListNode *second = nullptr;

    splitListMid(head, first, second);

    std::cout << "first:" << std::endl;
    printList(first);
    std::cout << "second:" << std::endl;
    printList(second);

    deleteList(first);
    deleteList(second);

    // Възстановяване на списъка за следващата демонстрация
    head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(3);
    head->next->next->next = new ListNode(4);
    head->next->next->next->next = new ListNode(5);

    // Демонстрация на разделяне на четни и нечетни позиции
    std::cout << "List:" << std::endl;
    printList(head);

    ListNode *odd = nullptr;
    ListNode *even = nullptr;

    splitEvenOdd(head, odd, even);

    std::cout << "odd:" << std::endl;
    printList(odd);
    std::cout << "even:" << std::endl;
    printList(even);

    deleteList(odd);
    deleteList(even);

    return 0;
}
