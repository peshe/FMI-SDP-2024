#pragma once
#include <atomic>
#include <cstddef>
#include <vector>
#include <iostream>

class BST {
   public:
	BST(int *begin, int *end) { root = makeTree(begin, end); }
	void print()	 // left root right
	{
		print_helper(this->root);
	}

	bool contains(int value) { return contains_helper(value, root); }
	void insert(int value) { insert_helper(value, root); }

	~BST() { kill(this->root); }

   private:
	struct Node {
		int	  value;
		Node *left	= nullptr;
		Node *right = nullptr;
	};
	Node *root;

   private:
	Node *makeTree(int *begin, int *end) {
		if (begin == end) return nullptr;
		int	 *mid	 = begin + (end - begin) / 2;
		Node *result = new Node{*mid, makeTree(begin, mid), makeTree(mid + 1, end)};
		return result;
	}

	void kill(Node *curr) {
		if (curr == nullptr) { return; }

		kill(curr->left);
		kill(curr->right);
		delete curr;
	}

	void print_helper(Node *curr) {
		if (curr == nullptr) { return; }

		print_helper(curr->left);
		std::cout << curr->value << " ";
		print_helper(curr->right);
	}

	bool contains_helper(int value, Node *curr) {
		if (!curr) return false;
		if (curr->value == value) return true;

		return contains_helper(value, curr->value > value ? curr->left : curr->right);
	}
	void insert_helper(int value, Node *&curr) {
		if (!curr) {
			curr = new Node(value, nullptr, nullptr);
			return;
		}
		if (curr->value > value) {
			insert_helper(value, curr->left);
		} else {
			insert_helper(value, curr->right);
		}
	}
};
