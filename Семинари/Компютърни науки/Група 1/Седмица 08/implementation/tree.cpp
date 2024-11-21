#include <iostream>
#include "tree.h"
using std::vector,std::swap,std::cout,std::endl;

void Tree::copy(Node*& curr,const Node* other){
    curr = new Node(other->val);
    for(int i = 0; i< other->children.size();i++){
        curr->children.push_back(nullptr);
        copy(curr->children[i],other->children[i]);
    }
};

void Tree::free(Node* curr){
    if(!curr)return;
    for(Node* child : curr->children )
        free(child);
    delete curr;
}

Tree::Tree(): root(nullptr){};

Tree::Tree(const Tree& other){
    copy(root,other.root);
}

Tree::Tree(Tree&& other){
    swap(other.root,root);
}

Tree& Tree::operator=(const Tree& other){
    if(&other == this)
        return *this ;
    free(root);
    copy(root,other.root);
    return *this;
}

Tree& Tree::operator=(Tree&& other){
    swap(other.root, root);
    return *this;
}

Tree::~Tree(){
    free(root);
}

void Tree::print()const{
    std::string s = "";
    formatedPrint(root,0,1, s);
}

void Tree::formatedPrint(Node* curr,int depth,bool last, std::string& prefix)const{
    if(!curr)return;
    cout<<prefix;

    if(depth){
        if(last)
            cout<<"|\n"<<prefix;        
        
        cout<<(last ?  "L--" :"|--" );
    }
    cout<<curr->val<<endl;
   
    bool currLast;
    for(int i = 0; i < curr->children.size();i++){
        Node* child = curr->children[i];
        currLast = (i == curr->children.size() - 1 );
        if(depth){
            prefix.push_back( last ? ' ': '|');
            prefix.push_back(' ');
            prefix.push_back(' ');
        }
        formatedPrint(child,depth+1,currLast, prefix);
        if(depth){
        prefix.pop_back();
        prefix.pop_back();
        prefix.pop_back();
        }
    }
}

size_t Tree::count()const{
    //To be implemented
    return 0;
}
size_t Tree::depth()const{
    depthUtil(root);
}
size_t Tree::depthUtil(Node *curr) const
{
    if(!curr)return 0;
    if(curr->children.size()==0)return 1;
    size_t maxDepth = 0;
    for(Node * child:curr->children ){
        maxDepth = std::max(maxDepth,depthUtil(child));
    }
    return maxDepth+1;
}
size_t Tree::countOnLevel(size_t depth) const
{
    //To be implemented
    return 0;
}

void Tree::insertTreeAt(const vector<size_t>& position, Tree& other){
    //To be implemented

}

