#include <iostream>
using namespace std;
struct Node{
    int val;
    Node* next, *prev, *down;
    Node(int v):val(v),next(nullptr),prev(nullptr),down(nullptr){};
};

Node* flattenUtil(Node* head){
    if(!head)return head;
    Node* curr = head;
    Node* prev=nullptr;
    Node* downEnd;
    while(curr){
        if(curr->down){
            downEnd = flattenUtil(curr->down);
            downEnd->next = curr->next;
            if(curr->next)
                curr->next->prev = downEnd;
            curr->next = curr->down;
            curr->down->prev = curr;
            curr->down = nullptr;

            curr = downEnd ->next;
            prev = downEnd;
        }
        else{
            prev = curr;
            curr = curr->next;

        }
    }
    return prev;
}

Node* flatten(Node* head){
    if(!head)return head;
    flattenUtil(head);
    return head;
}

int main(){
    Node* n1 = new Node({1});
    Node* n2 = new Node({2});
    Node* n3 = new Node({3});
    Node* n4 = new Node({4});
    Node* n5 = new Node({5});
    Node* n6 = new Node({6});
    Node* n7 = new Node({7});
    Node* n8 = new Node({8});
    Node* n9 = new Node({9});
    Node* n10 = new Node({10});
    n1->next = n2;
    n2->next = n3;
    n3->next = n4;

    n4->prev = n3;
    n3->prev = n2;
    n2->prev = n1;
    
    n2->down = n5;

    n5->next = n6;
    n6->next = n7;
    n7->next = n8;
    
    n8->prev= n7;
    n7->prev= n6;
    n6->prev= n5;
    
    n6->down = n9;

    n9->next = n10;
    n10->prev = n9;

    flatten(n1);
    Node* curr= n4;
    while(curr){
        cout<<curr->val<<" "<<endl;
        curr=curr->prev;
    }
    delete n1;
    delete n2;
    delete n3;
    delete n4;
    delete n5;
    delete n6;
    delete n7;
    delete n8;
    delete n9;
    delete n10;
}