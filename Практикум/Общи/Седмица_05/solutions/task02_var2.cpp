template <class T>
class Node {
public:
    T value;
    Node<T>* next;

    Node(T value = T(), Node* next = nullptr)
      : value(value), next(next)
    { }
};

template<class T>
Node<T> *removeAll(Node<T> *list, const T &value) {
    Node<T> *head = list;
    Node<T> *previous = list;
    Node<T> *current = list;
    while (current) {
        if (current->value == value) {
            if (current == head) {
                head = head->next;
                previous = current;
                delete current;
                current = head;
            } else {
                previous->next = current->next;
                delete current;
                current = previous->next;
            }
        } else {
            previous = current;
            current = current->next;
        }
    }

    return head;
}