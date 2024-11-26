#include "tree.h"
#include <stdexcept>
#include <queue>
#include <iostream>

void Tree::insertElAt(const vector<size_t>& position, int el){
    if(!root){
        root = new Node(el);
        return;
    }
    Node* temp = locatePosition(root,position,0);
    if(!temp)
        throw std::invalid_argument("Invalid position");

    temp->children.push_back(new Node(el));
}

int Tree::levelSum(size_t index){
    std::queue<Node*> q;
    q.push(root);
    Node* curr;
    int depth = 1,currLayerSize=1,nextlayerSize=0;
    while(!q.empty()&&depth<=index){
        curr = q.front();
        q.pop();
        currLayerSize--;
        for(Node* child:curr->children){
            q.push(child);
            nextlayerSize++;
        }
        if(!currLayerSize){
            depth++;
            currLayerSize = nextlayerSize;
            nextlayerSize = 0;
        }
    }
    int sum=0;
    while(!q.empty()){
        sum += q.front()->val;
        q.pop();
    }
    return sum;
}

Tree::Node* Tree::locatePosition(Tree::Node *curr, const vector<size_t> &position,size_t index)
{
    if(index == position.size())return curr;
    if(position[index]>curr->children.size())return nullptr;
    return locatePosition((curr->children[position[index]-1]), position, index+1);
}

