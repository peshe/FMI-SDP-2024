#include "trie.h"
#include "tree.h"
#include <iostream>
using namespace std;

int main(){
    // Tree t,t2;
    // t.insertElAt({},0);
    // t.insertElAt({},1);
    // t.insertElAt({},2);
    // t.insertElAt({},3);
    // t.insertElAt({2},12);
    // t.insertElAt({3},6);
    // t.insertElAt({3},20);
    // t.insertElAt({3},8);
    // t.insertElAt({1},4);
    // t.insertElAt({1,1},15);
    // // t.insertElAt({},10);
    // t.print();
    // cout<<t.levelSum(4)<<endl;

    //-----------------------------------

    Trie t;
    t.insert("a");
    t.insert("abb");
    t.insert("abd");
    t.insert("aca");
    t.insert("acbz");
    t.insert("ace");
    // t.insert("abc");
    t.remove("acbz");
    t.print();
    // t.remove("abd");
    // t.print();
}