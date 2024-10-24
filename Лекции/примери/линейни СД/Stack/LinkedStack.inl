/******************************************************************
*  Sample code to the course "Data Structures And Algorithms", FMI
*
* An educational class, representing linked stack.
*  - inline functions definition.
*
* (cc) Petar Armyanov, FMI, 2024
*******************************************************************/

template <typename DataType>
LinkedStack<DataType>::LinkedStack()
    : tos(nullptr)
{}


template <typename DataType>
LinkedStack<DataType>::LinkedStack(const LinkedStack<DataType>& stack)
    : tos(nullptr)
{
    try {
        copy(stack.tos);
    }
    catch (std::bad_alloc&) {
        clear();
        throw;
    }
}


template <typename DataType>
LinkedStack<DataType>::~LinkedStack()
{
    clear();
}


// NOTE! Only weak exception safety is guaranteed!
template <typename DataType>
LinkedStack<DataType>& LinkedStack<DataType>::operator=(const LinkedStack<DataType>& rhs)
{
    if (this != &rhs) {
        clear();
        copy(rhs.tos);
    }
    return *this;
}


template <typename DataType>
void LinkedStack<DataType>::push(const DataType& elem)
{
    tos = new node(elem, tos);
}


template <typename DataType>
DataType LinkedStack<DataType>::pop()
{
    DataType res = top();
    node* keep = tos;
    tos = tos->next;
    delete keep;
    return res;
}


template <typename DataType>
const DataType& LinkedStack<DataType>::top() const
{
    if (!isEmpty())
        return tos->data;
    throw std::underflow_error("Empty stack");
}


template <typename DataType>
bool LinkedStack<DataType>::isEmpty() const
{
    return tos == nullptr;
}


template <typename DataType>
void LinkedStack<DataType>::clear()
{
    while (!isEmpty()) {
        node* keep = tos;
        tos = tos->next;
        delete keep;
    }
}


template <typename DataType>
void LinkedStack<DataType>::copy(const node* top)
{
    assert(isEmpty());
    if (top) {
        tos = new node(top->data);
        top = top->next;

        node* prev = tos;
        while (top) {
            prev->next = new node(top->data);
            prev = prev->next;
            top = top->next;
        }
    }
}
