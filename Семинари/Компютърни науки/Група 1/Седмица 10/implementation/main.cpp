#include <vector>
#include "AVLTree.cpp"

int main(){
    AVLTree tree,t2;
    srand(time(nullptr)*7543+12345);
    std::vector<int> numbers{10, 19, 48, 71, 72, 37, 53, 65, 54, 7, 70, 73, 25, 13, 39, 59, 48, 18, 61, 8};
    for(int i = 0 ; i< 20 ;i++){
        tree.insert(i);
    } 
    tree.print();
    t2 = tree;
    // t2.print();
    // tree.print();
    // for(auto i : numbers)
        // cout<<i<<", ";
    // cout<<endl;
    cout<<"---------------\n";
    // for(int i =0 ;i<numbers.size();i++){
    //     t2.print();
    //     cout<<"---------------\n";
    //     t2.remove(numbers[i]);
    // }
    // tree.print();
    t2.print();
}