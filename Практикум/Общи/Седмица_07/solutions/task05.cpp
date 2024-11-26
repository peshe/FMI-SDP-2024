#include "Node.h"
template <typename T> using NodeBTree = Node<T>;

#include <cassert>
#include <functional>
#include <iostream>


template <typename T>
class NodeList {
public:
    T value;  // Стойност, съхранена във възела.
    NodeList<T>* next; // Указател към евентуалния следващ елемент.

    NodeList(T value = T(), NodeList* next = nullptr)
      : value(value), next(next)
    { }

    ~NodeList() {
      delete next;
    }

    void add(T value) {
      NodeList<T>* last = this;
      while (last->next != nullptr) {
        last = last->next;
      }
      last->next = new NodeList<T>(value);
    }

    void print() const {
      const NodeList<T>* current = this;
      while (current->next != nullptr) {
        std::cout << current->value << " -> ";
        current = current->next;
      }
      std::cout << current->value << std::endl;
    }
};

template <typename T>
NodeList<T>* filterBTreeToList(
    const NodeBTree<T>* btree,
    const std::function<bool(const T&)>& pred,
    /*out*/ NodeList<T>*& listEnd
) {
    if (btree == nullptr) {
        listEnd = nullptr;
        return nullptr;
    }

    NodeList<T>* leftEnd = nullptr;
    NodeList<T>* leftStart = filterBTreeToList(btree->left, pred, leftEnd);

    NodeList<T>* rightEnd = nullptr;
    NodeList<T>* rightStart = filterBTreeToList(btree->right, pred, rightEnd);

    NodeList<T>* combinedStart = nullptr;

    if (leftStart != nullptr) {
        combinedStart = leftStart;
        assert(leftEnd != nullptr);
        assert(leftEnd->next == nullptr);
        leftEnd->next = rightStart;

        if (rightEnd != nullptr) {
            assert(rightStart != nullptr);
            assert(rightEnd->next == nullptr);
            listEnd = rightEnd;
        }
        else {
            assert(rightStart == nullptr);
            listEnd = leftEnd;
        }
    }
    else if (rightStart != nullptr) {
        combinedStart = rightStart;
        assert(rightEnd != nullptr);
        assert(rightEnd->next == nullptr);
        listEnd = rightEnd;
    }

    if (pred(btree->value)) {
        if (combinedStart != nullptr) {
            assert(listEnd != nullptr);
            assert(listEnd->next == nullptr);
            listEnd->add(btree->value);
            listEnd = listEnd->next;
        }
        else {
            listEnd = combinedStart = new NodeList<T>(btree->value);
        }
    }

    return combinedStart;
}

template <typename T>
NodeList<T>* filterBTreeToList(
    const NodeBTree<T>* btree, const std::function<bool(const T&)>& pred
) {
    NodeList<T>* listEnd = nullptr;
    return filterBTreeToList(btree, pred, listEnd);
}

template <typename T>
void print(NodeList<T>* list) {
    if (list != nullptr) {
        list->print();
    }
    else {
        std::cout << std::endl;
    }
}

int main () {
    NodeBTree<int> *btree = new NodeBTree<int>(1,
                               new NodeBTree<int>(2,
                                              new NodeBTree<int>(3),
                                              new NodeBTree<int>(4)),
                               new NodeBTree<int>(5,
                                              new NodeBTree<int>(6),
                                              new NodeBTree<int>(7)));
    std::function<bool(const int&)> pred = [] (const int& val) -> bool {
        return val % 2 == 0;
    };

    NodeList<int> *filtered = filterBTreeToList(btree, pred);
    print(filtered);

    delete filtered;
    delete btree;
    return 0;
}
