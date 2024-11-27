#include "BST.cpp"

int main(){
    BST tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(40);
    tree.insert(5);
    tree.insert(7);
    tree.insert(9);
    tree.insert(6);
    tree.insert(1);
    tree.insert(4);
    tree.insert(2);
    tree.remove(4);
    tree.print();
}