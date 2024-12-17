#include <iostream>
#include "queue"
#include "main.h"
using namespace std;

int max(int a, int b, int c) {
	if (a > b && a > c) return a;
	if(b > c) return b;
	return c;
}

class DLLNode {
private:
	int data;
	DLLNode* prev;
	DLLNode* next;
public:
	DLLNode() {
		this->data = 0;
		this->prev = nullptr;
		this->next = nullptr;
	}
	DLLNode(int data) {
		this->data = data;
		this->prev = nullptr;
		this->next = nullptr;
	}
	int getData() {
		return this->data;
	}
	void setData(int data) {
		this->data = data;
	}
	DLLNode* getNext() {
		return this->next;
	}
	DLLNode* getPrev() {
		return this->prev;
	}
	void setNext(DLLNode* next) {
		this->next = next;
	}
	void setPrev(DLLNode* prev) {
		this->prev = prev;
	}
};

class DLL {
private:
	DLLNode* start;
	DLLNode* getLast() {
		if (start == nullptr) return nullptr;
		DLLNode* current = start;
		while (current->getNext() != nullptr) {
			current = current->getNext();
		}
		return current;
	}
public:
	DLL() {
		this->start = nullptr;
	}
	DLL(const DLL& other) {
		this->appendDllAtEnd(other);
	}
	void addItemAtEnd(int data) {
		DLLNode* newNode = new DLLNode(data);
		if (this->start == nullptr) {
			this->start = newNode;
		} else {
			DLLNode* last = this->getLast();
			newNode->setPrev(last);
			last->setNext(newNode);
		}
	}
	void appendDllAtEnd(const DLL& dll) {
		DLLNode* nodeToAppend = dll.start;
		while (nodeToAppend) {
			this->addItemAtEnd(nodeToAppend->getData());
			nodeToAppend = nodeToAppend->getNext();
		}
	}
	void print() {
		DLLNode* current = this->start;
		while (current != nullptr) {
			cout << current->getData() << endl;
			current = current->getNext();
		}
	}
};


class BinTree;

class Node {
private:
	int data;
	BinTree* left;
	BinTree* right;
public:
	Node(int _data, BinTree* _left, BinTree* _right) : data(_data), left(_left), right(_right) {}
	int getData() const {
		return data;
	}
	BinTree* getLeft() const {
		return left;
	}
	BinTree* getRight() const {
		return right;
	}
	void setData(int data) {
		this->data = data;
	}
	void setLeft(BinTree* left) {
		this->left = left;
	}
	void setRight(BinTree* right) {
		this->right = right;
	}
};

class BinTree {
private:
	Node* root;
	BinTree* createNode(int data) {
		return new BinTree(data);
	}
public:
	BinTree(Node* root) {
		this->root = root;
	}
	BinTree() {
		this->root = nullptr;
	}
	BinTree(int rootData) {
		this->root = new Node(rootData, nullptr, nullptr);
	}
	int getRootData() {
		return this->root->getData();
	}
	Node* getRoot() {
		return this->root;
	}
	BinTree* getLeft() {
		return this->root->getLeft();
	}
	BinTree* getRight() {
		return this->root->getRight();
	}
	void createLeftTree() {
		this->root->setLeft(new BinTree());
	}
	void createRightTree() {
		this->root->setRight(new BinTree());
	}
	void setLeft(int leftRootData) {
		BinTree* left = this->createNode(leftRootData);
		this->root->setLeft(left);
	}
	void setRight(int rightRootData) {
		BinTree* right = this->createNode(rightRootData);
		this->root->setRight(right);
	}
	void setRightTree(BinTree* tree) {
		this->root->setRight(tree);
	}
	void setRoot(int rootData) {
		if (this->root == nullptr) {
			this->root = new Node(rootData, nullptr, nullptr);
		}
		this->root->setData(rootData);
	}
	void print() {
		cout << "ROOT: " << this->root->getData() << endl;
		BinTree* leftSubTree = this->root->getLeft();
		if (leftSubTree != nullptr) {
			cout << "LEFT: ";
			leftSubTree->print();
		}
		BinTree* rightSubTree = this->root->getRight();
		if (rightSubTree != nullptr) {
			cout << "RIGHT: ";
			rightSubTree->print();
		}
	}
	int getMaxPathLength() {
		int leftMaxPathLength = 0, rightMaxPathLength = 0;
		if (this->getLeft() != nullptr) {
			leftMaxPathLength = this->getLeft()->getMaxPathLength();
		}
		if (this->getRight() != nullptr) {
			rightMaxPathLength = this->getRight()->getMaxPathLength();
		}
		return 1 + max(rightMaxPathLength, leftMaxPathLength);
	}
	int getDiameter() {
		int leftDiameter = 0;
		int maxLeftPathLength = 0; 
		int rightDiameter = 0;
		int maxRightPathLength = 0;
		if (this->getLeft() != nullptr) {
			leftDiameter = this->getLeft()->getDiameter();
			maxLeftPathLength = this->getLeft()->getMaxPathLength();
		}
		if (this->getRight() != nullptr) {
			rightDiameter = this->getRight()->getDiameter();
			maxRightPathLength = this->getRight()->getMaxPathLength();
		}
		return max(rightDiameter, leftDiameter, maxRightPathLength + maxLeftPathLength + 1);
	}
	void rotateRight() {
		BinTree* leftSubTree = this->root->getLeft();
		this->root->setLeft(leftSubTree->getRight());
		BinTree* newRightTree = new BinTree(this->root);
		leftSubTree->setRightTree(newRightTree);
		this->root = leftSubTree->getRoot();
	}
	bool isLeaf() {
		return this->getLeft() == nullptr && this->getRight() == nullptr;
	}
};

BinTree* createNew(int data) {
	return new BinTree(data);
}

bool PathSum(BinTree* tree, int sum) {
	if (tree == nullptr) {
		return false;
	}
	if (tree->isLeaf() && sum == 0) {
		return true;
	}

	return PathSum(tree->getLeft(), sum - tree->getRootData())||PathSum(tree->getRight(), sum - tree->getRootData());
}

int CountLeafNodes(BinTree* tree) {
	if (tree == nullptr) {
		return 0;
	}
	if (tree->isLeaf()) {
		return 1;
	}
	
	return CountLeafNodes(tree->getLeft()) + CountLeafNodes(tree->getRight());
}

void inputTree(BinTree* tree) {
	int root;
	char input;
	cout << "ROOT: ";
	cin >> root;
	tree->setRoot(root);
	cout << "Would you like to enter a left subtree(y/n)? " << endl;
	cin >> input;
	if (input == 'y') {
		BinTree* left = tree->getLeft();
		if (left == nullptr) {
			tree->createLeftTree();
			left = tree->getLeft();
		}
		inputTree(left);
	}
	cout << "Would you like to enter a right subtree(y/n)? " << endl;
	cin >> input;
	if (input == 'y') {
		BinTree* right = tree->getRight();
		if (right == nullptr) {
			tree->createRightTree();
			right = tree->getRight();
		}
		inputTree(right);
	}
}

bool checkPathHelper(BinTree* tree, int path[], int size, int index) {
	if (tree == nullptr) return false;
	int nextIndex = index + 1;
	if (path[index] == tree->getRootData()) {
		if (index == size - 1) {
			return true;
		}
	}
	else {
		nextIndex = 0;
	}
	bool pathContainedInLeft = checkPathHelper(tree->getLeft(), path, size, nextIndex);
	bool pathContainedInRight = checkPathHelper(tree->getRight(), path, size, nextIndex);
	return pathContainedInLeft || pathContainedInRight;
}

bool checkPath(BinTree* tree, int path[], int size) {
	return checkPathHelper(tree, path, size, 0);
}

void calculateStatistics(BinTree* tree, int* const stats) {
	if (tree == nullptr) return;
	stats[tree->getRootData()]++;
	calculateStatistics(tree->getLeft(), stats);
	calculateStatistics(tree->getRight(), stats);
}

bool contains(BinTree* tree, Node* node) {
	if (tree == nullptr) return false;
	return tree->getRoot() == node || contains(tree->getLeft(), node) || contains(tree->getRight(), node);
}

Node* lca(BinTree* tree, Node* n1, Node* n2) {
	if (tree == nullptr) return nullptr;
	if (n1 == n2) return n1;
	bool leftContainsN1 = contains(tree->getLeft(), n1);
	bool leftContainsN2 = contains(tree->getLeft(), n2);
	bool rightContainsN1 = contains(tree->getRight(), n1);
	bool rightContainsN2 = contains(tree->getRight(), n2);
	if (tree->getRoot() == n1 && (rightContainsN2 || leftContainsN2)) {
		return n1;
	}
	if (tree->getRoot() == n2 && (rightContainsN1 || leftContainsN1)) {
		return n2;
	}
	if ((leftContainsN1 && rightContainsN2) || (leftContainsN2 && rightContainsN1)) {
		return tree->getRoot();
	}
	if (leftContainsN1 && leftContainsN2) return lca(tree->getLeft(), n1, n2);
	if (rightContainsN1 && rightContainsN2) return lca(tree->getRight(), n1, n2);
	return nullptr;
}

DLL convertTreeToDLL(BinTree* tree) {
	if (tree == nullptr) return DLL();

	DLL leftDll = convertTreeToDLL(tree->getLeft());
	DLL rightDll = convertTreeToDLL(tree->getRight());
	leftDll.addItemAtEnd(tree->getRootData());
	leftDll.appendDllAtEnd(rightDll);
	return leftDll;
}

class ZigZagTraverser {
	int level;
	void fillNodes(deque<Node*>& q, vector<Node*>& nodes) {
		while (!q.empty()) {
			nodes.push_back(q.front());
			q.pop_front();
		}
		for (Node* node : nodes) {
			if (node->getLeft() != nullptr) {
				q.push_back(node->getLeft()->getRoot());
			}
			if (node->getRight() != nullptr) {
				q.push_back(node->getRight()->getRoot());
			}
		}
	}
	void print(vector<Node*> nodes) {
		if (level % 2 == 0) {
			for (auto it = nodes.rbegin(); it != nodes.rend(); ++it) {
				Node* node = *it;
				cout << node->getData() << " ";
			}
		}
		else {
			for (Node* node : nodes) {
				cout << node->getData() << " ";
			}
		}
		level++;
	}
public:
	void traverse(deque<Node*>& q) {
		vector<Node*> nodes;
		this->fillNodes(q, nodes);
		this->print(nodes);
	}
};

void BFS(BinTree* tree) {
	//int level = 1;
	deque<Node*> q;
	//queue<Node*> q;
	q.push_back(tree->getRoot());
	ZigZagTraverser zzT;
	while (q.size() > 0) {
		zzT.traverse(q);
	}
	cout << endl;
}

int main() {
	BinTree* tree = new BinTree(8);
	tree->setLeft(44);
	tree->getLeft()->setLeft(3);
	tree->getLeft()->setRight(4);
	tree->getLeft()->getLeft()->setLeft(7);
	tree->getLeft()->getLeft()->setRight(9);
	tree->getLeft()->getRight()->setLeft(77);
	tree->getLeft()->getRight()->setRight(3);
	tree->setRight(3);
	tree->getRight()->setLeft(6);
	tree->getRight()->setRight(7);
	tree->getRight()->getLeft()->setLeft(99);
	tree->getRight()->getLeft()->setRight(77);
	tree->getRight()->getRight()->setLeft(77);
	tree->getRight()->getRight()->setRight(7);
	//std::cout<<CountLeafNodes(tree);
	//                 8
	//        44				3
	//    3      4			6		7
	//  7   9  77  3	99    77  77  7

	//8
	//	44 3


	BFS(tree);


	// 7 3 9 44 77 4 3 8 99 6 77 3 77 7 7

	tree->print();

	tree->rotateRight();
	tree->print();
	//cout << tree->getDiameter();
	//Node* n1 = tree->getLeft()->getRight()->getRight()->getRoot();
	//Node* n2 = tree->getRight()->getLeft()->getLeft()->getRoot();
	//Node* lcaNode = lca(tree, n1, n2);
	//if (lcaNode == nullptr) {
	//	cout << "NO LCA";
	//}
	//else {
	//	cout << lcaNode->getData();
	//}

	//DLL dll = convertTreeToDLL(tree);
	//dll.print();

	//BinTree* tree = new BinTree();
	//inputTree(tree);
	//tree->print();
	/*int path[] = {8, 3, 6, 45};

	if (checkPath(tree, path, 4)) {
		cout << "YES";
	}
	else {
		cout << "NO";
	}

	cout << endl;

	int statistics[100]{};

	calculateStatistics(tree, statistics);

	for (int i = 0; i < 100; i++) {
		if (statistics[i] == 0) continue;
		cout << i << " : " << statistics[i] << endl;
	}*/
	return 0;
}
