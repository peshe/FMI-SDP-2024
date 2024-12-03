#include <iostream>
#include <string>

// Структура за възел на задача
struct TaskNode
{
    std::string name;
    int priority;
    TaskNode *next;

    TaskNode(std::string n, int p) : name(n), priority(p), next(nullptr) {}
};

// Помощна функция за принтиране на списъка с задачи
void printTaskList(TaskNode *head)
{
    while (head)
    {
        std::cout << head->name << " " << head->priority << std::endl;
        head = head->next;
    }
}

// Функция за освобождаване на паметта
void deleteList(TaskNode *head)
{
    while (head)
    {
        TaskNode *temp = head;
        head = head->next;
        delete temp;
    }
}

// Функция за разпределение на задачи като свързани списъци
TaskNode *partitionTasks(TaskNode *head, int k)
{
    // Създаване на три dummy възела за трите групи
    TaskNode largeDummy("", -1);
    TaskNode equalDummy("", -1);
    TaskNode smallDummy("", -1);

    // Указатели към краищата на всяка група
    TaskNode *largeTail = &largeDummy;
    TaskNode *equalTail = &equalDummy;
    TaskNode *smallTail = &smallDummy;

    // Обхождане на оригиналния списък
    TaskNode *current = head;
    TaskNode *nextNode;
    while (current)
    {
        // Временен възел за следващата стъпка
        nextNode = current->next;

        // Премахваме връзката на текущия възел
        current->next = nullptr;

        // Разпределяне според приоритета
        if (current->priority > k)
        {
            // Задачи с по-висок приоритет
            largeTail->next = current;
            largeTail = current;
        }
        else if (current->priority < k)
        {
            // Задачи с по-нисък приоритет
            smallTail->next = current;
            smallTail = current;
        }
        else
        {
            // Задачи с равен приоритет
            equalTail->next = current;
            equalTail = current;
        }

        // Преминаване към следващия възел
        current = nextNode;
    }

    // Свързване на трите групи
    // Най-напред големите, после равните, след това малките

    // Ако равните са празни, директно свързваме големите с малките
    if (equalDummy.next == nullptr)
    {
        largeTail->next = smallDummy.next;
    }
    else
    {
        largeTail->next = equalDummy.next;
        equalTail->next = smallDummy.next;
    }

    // Връщаме главата на новия списък
    return largeDummy.next ? largeDummy.next : (equalDummy.next ? equalDummy.next : smallDummy.next);
}

int main()
{
    // Създаване на свързан списък със задачи
    TaskNode *head = new TaskNode("taskA", 3);
    head->next = new TaskNode("taskB", 5);
    head->next->next = new TaskNode("taskC", 7);
    head->next->next->next = new TaskNode("taskD", 5);
    head->next->next->next->next = new TaskNode("taskE", 9);
    head->next->next->next->next->next = new TaskNode("taskF", 7);
    head->next->next->next->next->next->next = new TaskNode("taskG", 2);
    head->next->next->next->next->next->next->next = new TaskNode("taskH", 1);

    // Приоритет за разпределение
    int k = 5;

    // Извеждане на първоначалния списък
    printTaskList(head);

    // Разпределение на задачите
    head = partitionTasks(head, k);

    // Извеждане на разпределения списък
    std::cout << "\n-----------\n\n";
    printTaskList(head);

    deleteList(head);

    return 0;
}