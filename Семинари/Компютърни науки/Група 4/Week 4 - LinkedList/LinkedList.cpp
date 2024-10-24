#include <iostream>

class ListNode
{
    private:
        int element;
        ListNode* next;

    public:
        int getElement() {return element; }
        void setNext(ListNode* next)
        {
            this->next = next;
        }
        ListNode* getNext() {return next;}
        ListNode(int element, ListNode *next)
        {
            this->element = element;
            this->next = next;
        }

};

class LinkedList
{
    private:
        ListNode* head;
    
    public:
        LinkedList()
        {
            head = nullptr;
        }
        void print()
        {
            ListNode* tmp = head;
            while(tmp != nullptr)
            {
                std::cout << tmp->getElement() << " ";
                tmp = tmp->getNext();
            }
            std::cout << std::endl;
        }
        void insert(int element)
        {
            ListNode *tmp = new ListNode(element, head);
            head = tmp;
        }
        int popFront()
        {
            if(head == nullptr)
            {
                throw "List is empty";
            }
            ListNode *currentHead = head;
            head = head->getNext();
            int element = currentHead->getElement();
            delete currentHead;
            return element;

        }
        int popBack()
        {
            if(head == nullptr)
            {
                throw "List is empty";
            }
            if(head->getNext() == nullptr)
            {
                return popFront();
            }
            ListNode *tmp = head;
            
            while(tmp->getNext()->getNext() != nullptr)
            {
                tmp = tmp->getNext();
            }
            int element = tmp->getNext()->getElement();
            delete tmp->getNext();
            tmp->setNext(nullptr);
            return element;
        }
        int search(int element)
        {
            int index = -1;
            ListNode* tmp = head;
            int current = 0;
            while(tmp != nullptr && index == -1)
            {
                if(tmp->getElement() == element)
                {
                    index = current;
                }
                tmp = tmp->getNext();
                current++;
            }
            return index;
        }
        void reverse()
        {
            if(head == nullptr)
            {
                throw "List is empty";
            }
            if(head->getNext() == nullptr)
            {
                return;
            }
            ListNode* current = head;
            ListNode* next = current->getNext();
            ListNode* nextOfNext = next->getNext();
            head->setNext(nullptr);

            while(current != nullptr && next != nullptr)
            {
               //std::cout << current->getElement() << std::endl;
               next->setNext(current);
               current = next;
               next = nextOfNext; 
               if(nextOfNext) nextOfNext = next->getNext();
            }
            head = current;
        }

        int del(int index)
        {
            if(index == 0)
            {
                return popFront();
            }
            ListNode *tmp = head; 
            index--;
            for(int i = 0; i < index && tmp != nullptr; i++)
            {
                tmp = tmp->getNext();
            }
            if(tmp == nullptr || tmp->getNext() == nullptr)
            {
                throw "Invalid index";
            }
            ListNode* next = tmp->getNext();
            tmp->setNext(next->getNext());
            int element = next->getElement();
            delete next;
            return element;

        }

        int countNumbers(int element)
        {
            int counter = 0;
            ListNode* tmp = head;
            while(tmp != nullptr)
            {
                if(tmp->getElement() == element)
                {
                    counter++;
                }
                tmp = tmp->getNext();
            }
            return counter;
        }
        ListNode* findMiddle()
        {
            ListNode* fastPtr = head, *slowPtr = head;
            while(fastPtr != nullptr && fastPtr->getNext() != nullptr)
            {
                slowPtr = slowPtr->getNext();
                fastPtr = fastPtr->getNext()->getNext();
            }
            return slowPtr;
        }

        void swapElements(int index1, int index2)
        {
            ListNode* beforeIndex1 = head;
            ListNode* beforeIndex2 = head;
            if(index2 == 0 || index2 < index1)
            {
                return swapElements(index2, index1);
            }

            
            for(int i = 0; i < index1 - 1 && beforeIndex1 != nullptr; i++)
            {
                beforeIndex1 = beforeIndex1->getNext();
            }
            for(int i = 0; i < index2 - 1 && beforeIndex2 != nullptr; i++)
            {
                beforeIndex2 = beforeIndex2->getNext();
            }
            if(beforeIndex1==nullptr || 
               beforeIndex2==nullptr || 
               beforeIndex1->getNext() == nullptr || 
               beforeIndex2->getNext() == nullptr) {

                throw "Invalid index";
            }
            ListNode* onIndex1 = beforeIndex1->getNext();
            ListNode* onIndex2 = beforeIndex2->getNext();
            ListNode* afterIndex1 = beforeIndex1->getNext()->getNext();
            ListNode* afterIndex2 = beforeIndex2->getNext()->getNext();
            if(index1 == 0)
            {
                onIndex1 = head;
                afterIndex1 = head->getNext();
                head = onIndex2;
            }
            if(index1 != 0) beforeIndex1->setNext(onIndex2);
            if(index2 - index1 == 1)
            {
                onIndex1->setNext(afterIndex2);
                onIndex2->setNext(onIndex1);
                beforeIndex1->setNext(onIndex2);
                return;
            }
            beforeIndex2->setNext(onIndex1);
            onIndex2->setNext(afterIndex1);
            onIndex1->setNext(afterIndex2);
        }
        int getSize()
        {
            int size = 0;
            ListNode* tmp = head;
            while(tmp != nullptr)
            {
                size++;
                tmp = tmp->getNext();
            }
            return size;
        }

        int getElementOnIndex(int index)
        {
            ListNode* tmp = head;
            for(int i = 0; i < index && tmp != nullptr; i++)
            {
                tmp = tmp->getNext();
            }
            return tmp->getElement();
        }

        void bubbleSort()
        {
            int size = getSize();
            for(int i = 0; i < size; i++)
            {
                for(int j = i + 1; j < size; j++)
                {
                    if(getElementOnIndex(i) > getElementOnIndex(j))
                    {
                        std::cout << i << " " << j << std::endl;
                        swapElements(i, j);
                    }
                }
            }
        }

};
int main()
{
    LinkedList list;
    list.insert(5);
    list.insert(7);
    list.insert(2);
    list.insert(9);
    list.insert(3);
    list.print();
    //list.swapElements(0,2);
    //list.swapElements(1,2);

    list.bubbleSort();
    list.print();

    
    
}