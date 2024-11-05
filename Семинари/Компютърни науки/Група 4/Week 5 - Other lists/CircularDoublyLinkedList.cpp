#include <iostream>

class ListNode
{
    private:
        int element;
        ListNode* before, *after;

    public:
        int getElement()
        {
            return element;
        }
        void setElement(int element)
        {
            this->element = element;
        }
        ListNode* getAfter() { return after;}
        ListNode* getBefore() {return before;}
        void setBefore(ListNode* before) {this -> before = before;}
        void setAfter(ListNode* after) {this->after = after;}
        ListNode(int element, ListNode* before, ListNode* after) {
            this->element = element; 
            this->before = before;
            this->after = after;
        }

};
class DoublyLinkedList
{
    private:
        ListNode* head; 
    
    public:
    
        DoublyLinkedList()
        {
            head = nullptr;
        }
        void insertBack(int element)
        {
            if(head == nullptr)
            {
                insertFront(element);
            }
            else
            {
                ListNode* tmp = head;
                while(tmp->getAfter() != nullptr)
                {
                    tmp = tmp->getAfter();
                }
                tmp->setAfter(new ListNode(element, tmp, head));
                head->setBefore(tmp->getAfter());
                
            }
        }
        void insertFront(int element)
        {  
            if(head == nullptr)
            {

                head = new ListNode(element, head, head);
                head->setAfter(head);
                head->setBefore(head);
                
            }
            else
            {
                ListNode* lastNode = getLast();
                head = new ListNode(element, lastNode, head);
                lastNode->setAfter(head);
            }
            
            if(head->getAfter())
            {
                head->getAfter()->setBefore(head);
            }
        }
        int popFront()
        {
            if(head == nullptr)
            {
                throw "List is empty";
            }
            int element = head->getElement();
            ListNode* h = head;
            head = head->getAfter();
            ListNode* lastNode = getLast();
            head->setBefore(lastNode);
            lastNode->setAfter(head);
            delete h;
            return element;
        }
        bool isEmpty()
        {
            return head == nullptr;
        }
        void print()
        {
            ListNode* tmp = head;
            do
            {
                std::cout << tmp->getElement() << " ";
                tmp = tmp->getAfter();
            }
            while(tmp != head);
            std::cout << std::endl;
        }
        void insertOnIndex(int index, int element)
        {
            ListNode* tmp = head;
            for(int i = 0; i < index - 1 && tmp != nullptr; i++)
            {
                tmp = tmp->getAfter();
            }
            if(tmp == nullptr)
            {
                throw "Invalid index";
            }
            tmp->setAfter(new ListNode(element, tmp, tmp->getAfter()));
            tmp->getAfter()->getAfter()->setBefore(tmp->getAfter());
        }
        int deleteOnIndex(int index)
        {
            ListNode* tmp = head;
            for(int i = 0; i < index - 1 && tmp != nullptr; i++)
            {
                tmp = tmp->getAfter();
            }
            if(tmp == nullptr || tmp->getAfter() == nullptr)
            {
                throw "Invalid Index";
            }
            ListNode* after = tmp->getAfter();
            tmp->setAfter(after->getAfter());
            if(after->getAfter())
            {
                after->getAfter()->setBefore(tmp);
            }
            int element = after->getElement();
            delete after;
            return element;
        }

        void printBackwards(ListNode* from)
        {
            ListNode* tmp = from;
            while(tmp != nullptr)
            {
                std::cout << tmp->getElement() << " ";
                tmp = tmp->getBefore();
            }
            std::cout << std::endl;
        }

        ListNode* getLast()
        {
            ListNode* result = head;
            while(result->getAfter() != head)
            {
                result = result->getAfter();
            }
            return result;
        }
};
DoublyLinkedList filter(DoublyLinkedList a, bool(*pred)(int))
{
    DoublyLinkedList result;
    ListNode* lastNode = a.getLast();
    ListNode* tmp = a.getLast();
    do
    {
        if(pred(tmp->getElement()))
        {
            result.insertFront(tmp->getElement());
        }
        tmp = tmp->getBefore();
    }
    while(tmp != lastNode);
    return result;
}
int main()
{
    DoublyLinkedList list;
    for(int i = 10; i > 0; i--)
    {
        list.insertFront(i);
    }
    list.print();
    DoublyLinkedList evens = filter(list, [](int el)->bool{return el%2==0;});
    evens.print();
    //list.printBackwards(list.getLast());
}