#include "Node.h"

template <typename T>
using NodeBTree = Node<T>;

#include <algorithm>
#include <cassert>
#include <deque>
#include <iostream>
#include <vector>

using std::deque;
using std::vector;


template <typename T>
void generateFloors(
    const NodeBTree<T> *btree, size_t currentFloor, /*out*/vector<vector<T>>& floors
) {
    if (btree == nullptr) return;

    if (floors.size() <= currentFloor) {
        assert(floors.size() == currentFloor);
        floors.resize(currentFloor + 1);
    }
    floors[currentFloor].push_back(btree->value);

    generateFloors(btree->left, currentFloor + 1, floors);
    generateFloors(btree->right, currentFloor + 1, floors);
}

template <typename T>
void setFloors(
    NodeBTree<T> *btree, size_t currentFloor, vector<deque<T>>& floors
) {
    if (btree == nullptr) return;

    auto& floor = floors[currentFloor];
    btree->value = floor.front();
    floor.pop_front();

    setFloors(btree->left, currentFloor + 1, floors);
    setFloors(btree->right, currentFloor + 1, floors);
}

template <typename T>
void sortFloors(NodeBTree<T> *btree) {
    vector<vector<T>> floors;
    generateFloors(btree, 0, floors);

    vector<deque<T>> sortedFloors;
    sortedFloors.reserve(floors.size());

    for (auto& floor : floors) {
        std::sort(floor.begin(), floor.end());
        sortedFloors.emplace_back(floor.begin(), floor.end());
    }

    setFloors(btree, 0, sortedFloors);
}

template <typename T>
void printFloors(const NodeBTree<T> *btree) {
    vector<vector<T>> floors;
    generateFloors(btree, 0, floors);

    for (size_t floor = 0; floor < floors.size(); ++floor) {
        std::cout << "Floor " << floor + 1 << ':';
        for (const auto& value : floors[floor]) {
            std::cout << ' ' << value;
        }
        std::cout << std::endl;
    }
}

int main () {
    NodeBTree<int> *btree = new NodeBTree<int>(1,
                               new NodeBTree<int>(2,
                                  new NodeBTree<int>(6),
                                  new NodeBTree<int>(7,
                                        new NodeBTree<int>(9))),
                               new NodeBTree<int>(5,
                                  new NodeBTree<int>(3),
                                  new NodeBTree<int>(4,
                                        nullptr,
                                        new NodeBTree<int>(8))));
    printFloors(btree);
    std::cout << std::endl;

    sortFloors(btree);
    printFloors(btree);

    delete btree;
    return 0;
}
