#include <utility>
#include <iostream>
#include <iomanip>
#include "BST.h"

using std::cout, std::endl;


BST::Node* BST::copy(BST::Node* curr){
    if(!curr)return nullptr;
    return new BST::Node(curr->val, copy(curr->left), copy(curr->right));
}
void BST::free(BST::Node* curr){
    if(!curr)return;
    free(curr->left);
    free(curr->right);
    delete curr;
}

BST::Node* BST::getMin(BST::Node* curr)const{   
    if(!curr)return curr;
    return curr->left ? getMin(curr->left) : curr;
}

BST::Node* BST::extractMin(BST::Node*& curr){
    if(!curr)return curr;
    if(curr->left)return extractMin(curr->left);   
    else{
        BST::Node* detach=curr;
        curr = curr->right;
        return detach;
    }

}

void BST::insertRec(BST::Node*& curr, int el){
    if(!curr)curr = new BST::Node(el);
    else insertRec((curr->val < el ? curr->right : curr->left),el); 
}
bool BST::searchRec(BST::Node* curr, int el)const{
    if(!curr)return false;
    if(curr->val == el) return true;
    return searchRec( (curr->val < el ? curr->right : curr->left) , el);
}
void BST::removeRec(BST::Node*& curr, int el){
    if(!curr)return;
    BST::Node* toDelete; 
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
            BST::Node* newCurr = extractMin(curr->right);
            newCurr -> left = curr->left;
            newCurr -> right = curr->right;
            toDelete = curr;
            curr = newCurr;
        }
        delete toDelete;
    }
    else removeRec((curr->val < el ? curr->right : curr->left),el);
}

BST::BST(const BST& other){
    root = copy(other.root);
};
BST::BST(BST&& other){
    std::swap(root,other.root);
}
BST& BST::operator=(const BST& other){
    if(&other != this){
        free(root);
        root = copy(other.root);
    }
    return *this;
}
BST& BST::operator=(BST&& other){
    if(&other != this){
        std::swap(root, other.root);
    }
    return *this;
}
BST::~BST(){
    free(root);
}

bool BST::empty() const
{
    return !root;
}

void BST::insert(int val)
{
    insertRec(root,val);
};
bool BST::search(int val)const{
    return searchRec(root,val);
};
void BST::remove(int val){
    removeRec(root,val);
};
void BST::printF(BST::Node* curr,int depth,bool down, std::string& prefix)const{
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
void BST::print(){
    std::string s="";
    printF(root,0,1,s);
}


/*-------------------------------------------------*/
BST::Iterator BST::begin(){
    return Iterator(root);
}
BST::Iterator BST::end(){
    return Iterator(nullptr);
}
void BST::Iterator::getNext(Node* curr){
    while(curr){
        path.push(curr);
        curr = curr->left;
    }
}
BST::Iterator::operator bool()const{    return ptr;    };
BST::Iterator& BST::Iterator::operator++(){
    if(path.empty())return *this;
    ptr = path.top();
    path.pop();
    if(ptr)
        getNext(ptr->right);
    return (*this);
}
BST::Iterator BST::Iterator::operator++(int){
    Iterator temp(*this);
    ++(*this);
    return temp;
}
int BST::Iterator::operator*()const{
    return ptr->val; 
}
bool BST::Iterator::operator==(const BST::Iterator& other)const{
    return ptr == other.ptr;
}
bool BST::Iterator::operator!=(const BST::Iterator& other)const{
    return !((*this) == other);
}

BST::Iterator::Iterator(Node *p){
    ptr = p;
    if(p){
        path.push(nullptr);
        getNext(p); 
        ++(*this);
    }
    
}
