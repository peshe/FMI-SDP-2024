#include <iostream>
using namespace std;
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
	BinTree() {
		this->root = nullptr;
	}
	BinTree(int rootData) {
		this->root = new Node(rootData, nullptr, nullptr);
	}
	int getRootData() {
		return this->root->getData();
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
};

BinTree* createNew(int data) {
	return new BinTree(data);
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

int main() {
	BinTree* tree = new BinTree(8);
	tree->setLeft(4);
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
	//                 8
	//        4					3
	//    3      4			6		7
	//  7   9  77  3	99    77  77  7

	tree->print();


	//BinTree* tree = new BinTree();
	//inputTree(tree);
	//tree->print();
	int path[] = {8, 3, 6, 45};

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
	}
    int x = 0;
    cin>>x;
    return 0;
}