#pragma once
#include <alloca.h>
#include <algorithm>
#include "NodeAllocator.h"

template <class T>
class LList {
   public:
	struct Node : public Serializable {
		Node *next;
		T	  value;

		Node(Node* next = nullptr, T value = T()) : next(next), value(value) {}

		std::string to_string() {
			char buffer[sizeof(Node*) * 2 + 1];
			snprintf(buffer, sizeof(buffer), "%p", (void*)next);
			return std::string("Node ( next: ") + buffer + ", value: "+ std::to_string(value) + ")";
		}

		void serialize(std::ostream &out) override {
			static_cast<void>(out); // silence warnings
			throw std::runtime_error("Not implemented");
		}
		void deserialize(std::istream &in) override {
			static_cast<void>(in); // silence warnings
			throw std::runtime_error("Not implemented");
		}
	};

	LList(Allocator<Node> &a) : head(nullptr), tail(nullptr), allocator(&a) {}

	LList(const LList<T> &other) : LList(*other.allocator) { copy(other); }
	LList(LList<T> &&other) : head(other.head), tail(other.tail), allocator(other.allocator) {
		other.head = nullptr;
		other.tail = nullptr;
	}
	LList<T> &operator=(const LList<T> &other) {
		if (&other == this) return *this;
		free();
		copy(other);
		return *this;
	}
	LList<T> &operator=(LList<T> &&other) {
		std::swap(head, other.head);
		std::swap(tail, other.tail);
		std::swap(allocator, other.allocator);
		return *this;
	}
	~LList() { free(); }

	void free() {
		Node *curr = head;
		while (curr != nullptr) {
			Node *temp = curr;
			curr	   = curr->next;
			allocator->free(temp);
		}
		tail = nullptr;
		head = nullptr;
	}

	//// PLEASE CALL THIS ONLY ON EMPTY LISTS
	void copy(const LList<T> &other) {
		allocator = other.allocator;
		if (!other.head) return;
		for (Node *curr = other.head; curr; curr = curr->next) {
			push_back(curr->value);
		}
	}

	void push_back(const T &value) {
		Node *toAdd = allocator->allocate();
		*toAdd		= Node{nullptr, value};

		if (!head) {
			head = tail = toAdd;
			return;
		}
		tail->next = toAdd;
		tail	   = toAdd;
	}

	void push_front(const T &value) {
		Node *toAdd = allocator->allocate();
		*toAdd		= Node{head, value};
		if (!head) {
			head = tail = toAdd;
			return;
		}
		head = toAdd;
	}


	void print(std::ostream &out) {
		for (Node *curr = head; curr; curr = curr->next) {
			out << curr->value << " ";
		}
		out << std::endl;
	}

   private:
	Node			*head;	   /// pointer to first node
	Node			*tail;	   /// pointer to last element
	Allocator<Node> *allocator;
};
