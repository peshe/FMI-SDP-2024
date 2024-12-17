#include <utility>
#include <iostream>
#include <iomanip>
#include "AVLTree.h"

using namespace std;

int AVLTree::getHeight(Node * curr)const
{
    if(!curr)return 0;
    return curr->height;
}

void AVLTree::updateHeight(Node* curr){
    if(!curr)return;
    curr->height =1+ max(getHeight(curr->left), getHeight(curr->right));
}

void AVLTree::leftRotation(Node *& curr){
    Node* temp = curr->right;
    curr->right = temp->left;
    temp->left = curr;
    
    updateHeight(curr);
    curr = temp;
    updateHeight(curr);
}

void AVLTree::rightRotation(Node *& curr)
{
    Node* temp = curr->left;
    curr->left = temp->right;
    temp->right = curr;
    updateHeight(curr);
    curr = temp;
    updateHeight(curr);
}

int AVLTree::BF(Node * curr) const
{
    return getHeight(curr->left) - getHeight(curr->right);
}

void AVLTree::balance(Node*& curr)
{
    if(!curr)return;
    if(BF(curr) == 2){          //left heavy
        if(BF(curr->left) == 1) //left left
            rightRotation(curr);
        else{                   //left right
            leftRotation(curr->left);
            rightRotation(curr);
        }    
    }
    else if(BF(curr) == -2){     //right heavy
        if(BF(curr->right) == -1)//right right
            leftRotation(curr);
        else{                    //right left
            rightRotation(curr->right);
            leftRotation(curr);
        }
    }
}






























AVLTree::Node* AVLTree::copy(AVLTree::Node* curr){
    if(!curr)return nullptr;
    return new AVLTree::Node(curr->val, copy(curr->left), copy(curr->right), curr->height);
}
void AVLTree::free(AVLTree::Node* curr){
    if(!curr)return;
    free(curr->left);
    free(curr->right);
    delete curr;
}

AVLTree::Node* AVLTree::getMin(AVLTree::Node* curr)const{   
    if(!curr)return curr;
    return curr->left ? getMin(curr->left) : curr;
}

AVLTree::Node* AVLTree::extractMin(AVLTree::Node*& curr){
    if(!curr)return curr;
    if(curr->left){
        Node* res = extractMin(curr->left);
        updateHeight(curr);
        balance(curr);
        return res;
    }   
    else{
        AVLTree::Node* detach=curr;
        curr = curr->right;
        return detach;
    }

}

void AVLTree::insertRec(AVLTree::Node*& curr, int el){
    if(!curr){
        curr = new AVLTree::Node(el);
        return;
    }

    insertRec((curr->val < el ? curr->right : curr->left),el); 
    
    updateHeight(curr);
    balance(curr);
}
bool AVLTree::searchRec(AVLTree::Node* curr, int el)const{
    if(!curr)return false;
    if(curr->val == el) return true;
    return searchRec( (curr->val < el ? curr->right : curr->left) , el);
}
void AVLTree::removeRec(AVLTree::Node*& curr, int el){
    if(!curr)return;
    AVLTree::Node* toDelete; 
    if(curr->val==el){
        if(!curr->left && !curr->right){
            toDelete = curr;
            curr = nullptr;
        }
        else if(!curr->left){
            toDelete = curr;
            curr = curr->right;
        }
        else if(!curr->right){
            toDelete = curr;
            curr = curr->left;
        }
        else{
            AVLTree::Node* newCurr = extractMin(curr->right);
            newCurr -> left = curr->left;
            newCurr -> right = curr->right;
            toDelete = curr;
            curr = newCurr;
        }
        delete toDelete;
    }
    else {
        removeRec((curr->val < el ? curr->right : curr->left),el);
    }
    updateHeight(curr);
    balance(curr);
}

AVLTree::AVLTree(const AVLTree& other){
    root = copy(other.root);
};
AVLTree::AVLTree(AVLTree&& other){
    std::swap(root,other.root);
}
AVLTree& AVLTree::operator=(const AVLTree& other){
    if(&other != this){
        free(root);
        root = copy(other.root);
    }
    return *this;
}
AVLTree& AVLTree::operator=(AVLTree&& other){
    if(&other != this){
        std::swap(root, other.root);
    }
    return *this;
}
AVLTree::~AVLTree(){
    free(root);
}

void AVLTree::insert(int val){
    insertRec(root,val);
};
bool AVLTree::search(int val)const{
    return searchRec(root,val);
};
void AVLTree::remove(int val){
    removeRec(root,val);
};
void AVLTree::printF(AVLTree::Node* curr,int depth,bool down, std::string& prefix)const{
    if(!curr)return;

    if(depth){
        prefix+="|  ";
        if(!down)
            prefix[(depth-1)*3] = ' ';
    }
    printF(curr->left,depth+1, 0, prefix);
    if(depth)
        prefix.erase(prefix.end()-3,prefix.end());

    cout<<prefix;
    if(depth){
        cout<<(down ?  "L--" : ",--" );
    }
    cout<<curr->val<<endl;

    if(depth){
        prefix+="|  ";
        if(down)
            prefix[(depth-1)*3] = ' ';
    }
    printF(curr->right,depth+1, 1, prefix);
    if(depth)
        prefix.erase(prefix.end()-3,prefix.end());
}
void AVLTree::print()const{
    std::string s="";
    printF(root,0,1,s);
}

