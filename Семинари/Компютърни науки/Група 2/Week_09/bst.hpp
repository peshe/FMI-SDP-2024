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
		std::cout << std::endl;
	}

	void printTab() { printTab_helper(root, 0); }
	void printGraphic(std::ostream &out) {
		bits b;
		g_show(out, root, b);
	}

	bool contains(int value) { return contains_helper(value, root); }
	void insert(int value) { insert_helper(value, root); }

	~BST() { kill(this->root); }
	void remove(int value) { removeHelper(value, root); }

	void rebalance() {
		std::vector<int> arr;
		while (root) {
			Node *curr = extractMinNode(root);
			arr.push_back(curr->value);
			delete curr;
		}

		root = makeTree(&arr[0], &arr[0] + arr.size());
	}

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

	void removeHelper(int value, Node *&currNode) {
		if (!currNode) return;
		if (currNode->value == value) {
			Node *left	= currNode->left;
			Node *right = currNode->right;
			delete currNode;
			if (!right) {
				currNode = left;
			} else {
				currNode		= extractMinNode(right);
				currNode->left	= left;
				currNode->right = right;
			}
			return;
		}

		removeHelper(value, (currNode->value > value ? currNode->left : currNode->right));
	}

	Node *extractMinNode(Node *&curr) {
		if (!curr->left) {
			Node *result = curr;
			curr		 = curr->right;
			return result;
		}
		return extractMinNode(curr->left);
	}

	void printTab_helper(Node *curr, int tab) {
		for (int i = 0; i < tab; ++i)
			std::cout << ' ';
		std::cout << curr->value << std::endl;
		if (curr->left) {
			printTab_helper(curr->left, tab + 1);
		} else std::cout << std::endl;
		if (curr->right) {
			printTab_helper(curr->right, tab + 1);
		} else std::cout << std::endl;
	}

	using bits = std::vector<bool>;
	void g_tabs(std::ostream &out, const bits &b) {
		for (unsigned int i = 1; i < b.size(); ++i) {
			out << ((b[i - 1] != b[i]) ? " \u2502" : "  "); // │
		}
	}
	void g_show(std::ostream &out, const Node *r, bits &b, const std::string &middle = "") {
		// https://en.wikipedia.org/wiki/Box-drawing_character
		if (r->left) {
			b.push_back(true);
			g_show(out, r->left, b, " \u250c");		// ┌
			b.pop_back();
		}

		g_tabs(out, b);
		out << middle << "\u2500\u2524" << r->value << std::endl;	  // ─┤

		if (r->right) {
			b.push_back(false);
			g_show(out, r->right, b, " \u2514");	 // └
			b.pop_back();
		}
	}
};
