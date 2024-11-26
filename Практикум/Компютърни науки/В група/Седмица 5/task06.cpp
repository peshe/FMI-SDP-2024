#include <iostream>
#include <vector>
#include <cstddef>
#include "SinglyLinkedListNode.hpp"

bool nextValue(std::vector<Node<int>*>& lists, std::size_t &nextValueIdx)
{
    std::size_t counter = 0 ;
    
    while (counter < lists.size() && lists[counter] == nullptr)
        ++counter;

    if (counter == lists.size())
        return false;
    
    std::size_t minValIdx = counter;
    
    for (std::size_t i = counter + 1; i < lists.size(); ++i)
    {
        if (lists[i] != nullptr && lists[i]->value < lists[minValIdx]->value)
            minValIdx = i;
    }

    nextValueIdx = minValIdx;

    return true;
}

Node<int>* mergeKLists(std::vector<Node<int>*>& lists)
{
    if (lists.size() == 0) return nullptr;

    std::size_t nextValIdx;
    bool nextVal = nextValue(lists, nextValIdx);

    if (nextVal == false) return nullptr;
    Node<int>* head = new Node<int>(lists[nextValIdx]->value), *it = head;
    lists[nextValIdx] = lists[nextValIdx]->next; 
    
    while (nextValue(lists, nextValIdx))
    {
        it->next = new Node<int>(lists[nextValIdx]->value);
        it = it->next;

        lists[nextValIdx] = lists[nextValIdx]->next;
    }

    it = head->next;
    delete head;

    return it;
}

int main()
{
    Node<int>* l1 = new Node<int>(1, new Node<int>(4, new Node<int>(5)));
    Node<int>* l2 = new Node<int>(1, new Node<int>(3, new Node<int>(4)));
    Node<int>* l3 = new Node<int>(2, new Node<int>(6));

    std::vector<Node<int>*> v;
    v.push_back(nullptr);
    v.push_back(nullptr);
    v.push_back(nullptr);

    Node<int>* result = mergeKLists(v);
    result->print();

    deallocate(l1);
    deallocate(l2);
    deallocate(l3);
    deallocate(result);

    return 0;
}