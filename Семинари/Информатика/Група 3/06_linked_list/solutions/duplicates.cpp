void removeConsecutiveDuplicates(Node* first)
{
	if (!first)
	{
		return; // Do nothing
	}

	Node* current = first->next;
	Node* previous = first;

	while (current)
	{
		if (previous->value == current->value) {
			previous->next = current->next;
			delete current;

			current = previous->next;
			continue;
		}
		previous = current;
		current = current->next;
	}
}