#include "trie.h"
void Trie::copy(Node*& curr,Node* other){
    curr = new Node();
    for(int i = 0; i< 26;i++){
        if(other->next[i]){
            copy(curr->next[i],other->next[i]);
        }
    }
}
void Trie::free(Node* curr){
    if(!curr)return;
    for(int i = 0; i<26;i++ )
        free(curr->next[i]);
    delete curr;
}

Trie::Trie(){
    head = new Node();
}
Trie::Trie(const Trie& other){
    copy(head,other.head);
}
Trie::Trie(Trie&& other){
    std::swap(head,other.head);
}
Trie& Trie::operator=(const Trie& other){
    if(&other == this)return *this;
    free(head);
    copy(head,other.head);
    return *this;
}
Trie& Trie::operator=(Trie&& other){
    if(&other == this)return *this;
    std::swap(head,other.head);
    return *this;
}
Trie::~Trie(){
    free(head);
}

void Trie::insert(const string& word){
    
}
void Trie::search(const string& word)const{

}
void Trie::remove(const string& word){

}
void Trie::print()const{

}