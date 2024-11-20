#include "tree.h"
#include <stdexcept>
#include <queue>
#include <iostream>



int Tree::levelSum(size_t index){
    if(!root)return 0;
    if(index == 0)return root->val;
    std::queue<Node*> q;
    q.push(root);
    int currLevel = 1,nextLevel = 0,depth=0;
    Node* temp;
    while(!q.empty() && depth< index){
        temp = q.front();
        q.pop();
        currLevel--;
        for(Node* child:temp->children){
            q.push(child);
            nextLevel++;
        }
        if(!currLevel){
            currLevel = nextLevel;
            nextLevel = 0;
            depth++;
        }
    }

    int sum = 0;
    while(!q.empty()){
        sum+=q.front()->val;
        q.pop();
    }

    return sum;
}

void Tree::insertElAt(const vector<size_t>& position, int el){
    if(!root){
        if(!position.size()){
            root = new Node(el);
            return;
        }
        else throw std::invalid_argument("Invalid position");
    }
    Node* temp = locatePosition(root,position,0);
    if(temp == nullptr){
        throw std::invalid_argument("Invalid position");
    }
    temp->children.push_back(new Node(el));
}


Tree::Node* Tree::locatePosition(Tree::Node *curr, const vector<size_t> &position,size_t index){
    if(!curr)return curr;
    if(index >=position.size())return curr;
    if(position[index] > curr->children.size())return nullptr;
    return locatePosition(curr->children[position[index]-1],position,index+1);
}































































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

