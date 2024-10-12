class LinkedStackNode
{
    private:
        int el;
        LinkedStackNode* next;

    public:
        int getEl() { return el;}
        LinkedStackNode* getNext() {return next;}
        void setEl(int el) { this->el = el;}
        void setNext(LinkedStackNode* next) {this->next = next;}
        LinkedStackNode(int el, LinkedStackNode* next)
        {
            this->el = el;
            this->next = next;
        }
};
class LinkedStack
{
    private:
        LinkedStackNode* element
        int size;
    
    public:
        LinkedStack()
        {
            element = nullptr;
            size = 0;
        }
        bool empty()
        {
            return element == nullptr;
        }
        void push(int elem)
        {
            LinkedStackNode* tmp = new LinkedStackNode(elem, element);
            element = tmp;
            size++;
        }
        int top()
        {
            if(size == 0)
            {
                throw "Empty stack";
            }
            return element->getEl();
        }
        int pop()
        {
            if(size == 0)
            {
                throw "Empty stack";
            }
            int topValue = top();
            LinkedStackNode* tmp = element;
            element = element->getNext();
            delete tmp;
            return topValue;
            size--;
        }

}