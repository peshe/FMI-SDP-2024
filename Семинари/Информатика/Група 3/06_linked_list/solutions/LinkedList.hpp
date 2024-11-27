#ifndef LINKED_LIST
#define LINKED_LIST

#include<iostream>
#include<stdexcept>

template <class T>
class LinkedList
{
private:
	struct Node {
		T data;
		Node* next;

		Node(T value = T(), Node* next = nullptr)
			:data(value), next(next)
		{}
	};

public:
	LinkedList() : head(nullptr), tail(nullptr) {}

	LinkedList(const LinkedList& other) {
		this->cloneFrom(other);
	}
	LinkedList<T>& operator=(const LinkedList& other) {
		if (this != &other) {
			Node* oldHead = this->head;
			this->cloneFrom(other);
			this->free(oldHead);
		}

		return *this;
	}

	~LinkedList() {
		this->free(this->head);
	}

public:
	void insertFront(const T& value) {
		Node* newNode = new Node(value, this->head);
		this->head = newNode;
		if (!this->tail) {
			this->tail = newNode;
		}
	}

	void insertBack(const T& value) {
		Node* newNode = new Node(value);

		if (!this->tail) {
			this->tail = this->head = newNode;
			return;
		}

		this->tail->next = newNode;
		this->tail = newNode;
	}

	void insertAt(const T& value, std::size_t index) {
		if (!this->head && index != 0) {
			throw std::invalid_argument("Cannot insert into empty list at index different from 0");
		}

		if (index == 0) {
			this->insertFront(value);
			return;
		}

		Node* previous = this->head;
		for (std::size_t i = 1; i <= index && previous != nullptr; i++) {
			previous = previous->next;
		}

		if (previous == nullptr) {
			throw std::invalid_argument("Index out of bounds: too large");
		}

		Node* newNode = new Node(value, previous->next);
		previous->next = newNode;
	}

	void removeFront() {
		if (!this->head) {
			throw std::logic_error("List is empty");
		}

		Node* toDelete = this->head;
		if (this->head == this->tail) {
			this->head = this->tail = nullptr;
			delete toDelete;
		}
		else
		{
			this->head = this->head->next;
			delete toDelete;
		}
	}
	void removeBack() {
		if (!this->head) {
			throw std::logic_error("List is empty");
		}

		if (this->head == this->tail) {
			delete this->head;
			this->head = this->tail = nullptr;
			return;
		}

		Node* previous = this->head;
		while (previous->next != this->tail) {
			previous = previous->next;
		}

		delete this->tail;
		this->tail = previous;
		previous->next = nullptr;
	}

	void removeAt(std::size_t index) {
		if (!this->head) {
			throw std::logic_error("List is empty");
		}

		if (index == 0) {
			this->removeFront();
			return;
		}

		Node* previous = this->head;
		for (std::size_t i = 1; i <= index - 1 && previous != nullptr; i++) {
			previous = previous->next;
		}

		if (previous == nullptr) {
			throw std::invalid_argument("Index out of bounds: too large");
		}

		if (previous->next == this->tail) {
			delete this->tail;
			this->tail = previous;
			previous->next = nullptr;
		}
		else
		{
			Node* toDelete = previous->next;
			previous->next = toDelete->next;
			delete toDelete;
		}
	}

public:
	void print() const {
		Node* current = this->head;
		while (current) {
			std::cout << current->data << std::endl;
			current = current->next;
		}
	}

public:
	LinkedList<T> map(T (*func)(const T& value)) {
		Node* current = this->head;
		LinkedList<T> result;
		while (current) {
			result.insertBack(func(current->data));
			current = current->next;
		}

		return result;
	}
private:
	void cloneFrom(const LinkedList& other) {
		Node* result = nullptr;
		Node* resultTail = nullptr;
		try
		{
			Node* current = other.head;
			while (current) {
				Node* newNode = new Node(current->data);
				if (!result) {
					result = resultTail = newNode;
				}
				else
				{
					resultTail->next = newNode;
					resultTail = newNode;
				}
				current = current->next;
			}
		}
		catch (const std::exception&)
		{
			this->free(result);
			throw;
		}

		this->head = result;
		this->tail = resultTail;
	}

	void free(Node* start) {
		std::cout << "Called free(): " << this->head->data << std::endl;
		Node* current = start;
		while (current) {
			Node* next = current->next;
			delete current;
			current = next;
		}
	}

private:
	Node* head;
	Node* tail;
};

#endif // !LINKED_LIST
