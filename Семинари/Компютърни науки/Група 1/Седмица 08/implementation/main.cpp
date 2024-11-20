#include "tree.h"
#include <iostream>
using namespace std;

int main(){
    Tree t,t2;
    t.insertElAt({},0);
    t.insertElAt({},1);
    t.insertElAt({},2);
    t.insertElAt({},3);
    t.insertElAt({2},12);
    t.insertElAt({3},6);
    t.insertElAt({3},20);
    t.insertElAt({3},8);
    t.insertElAt({1},4);
    t.insertElAt({1,1},15);
    // t2 = std::move(t);
    // t.insertElAt({},10);
    t.print();
    cout<<t.levelSum(4)<<endl;
    // cout<<t.isLevelPrime(3);
    // cout<<"-------------------------\n";
    // t2.print();
}