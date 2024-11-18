template <class T>
class Node {
public:
    T value;
    Node<T>* next;

    Node(T value = T(), Node<T>* next = nullptr)
      : value(value), next(next)
    { }
};

template <class T>
Node<T>* cloneReversed(Node<T>* first)
{
	Node<T>* current = first;
	Node<T>* previous = nullptr;

	while (current)
	{
		Node<T>* next = current->next;
		Node<T>* temp = nullptr;

		try
		{
			 temp = new Node<T>(current->value, previous);
		}
		catch (...)
		{
			// If the new node cannot be created delete the previous ones.
			Node<T>* toBeDeleted = previous;
			while (toBeDeleted)
			{
				Node<T>* nextToDelete = toBeDeleted->next;
				delete toBeDeleted;
				toBeDeleted = nextToDelete;
			}

			throw std::bad_alloc();
		}
		
		previous = temp;
		current = next;
	}

	return previous;
}