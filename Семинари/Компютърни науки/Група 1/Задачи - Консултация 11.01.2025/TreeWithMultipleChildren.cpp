#include <iostream>
#include <vector>
#include <queue>
#include <sstream>
#include <fstream>

using namespace std;

struct Node{
    int val;
    vector<Node*> children;
};

Node* inputTree(istream& in){
    Node dummy;
    Node* root=&dummy,*curr;
    queue<Node*>q;
    string s;
    int val;
    q.push(root);
    while(!q.empty()){
        
        curr = q.front();
        q.pop();

        s="";
        while(s=="\n" || s == ""){//пропускам новите редове и |
            getline(in,s,'|');
        }
        
        stringstream ss(s);
        
        while(!ss.eof()){

            while(ss.peek() == ' ' && ss)ss.get();//пропускам space-овете преди числото
            if(!ss)break;

            ss >>val;
            
            while(ss.peek() == ' '&& ss)ss.get();//пропускам space-овете след числото
            if(!ss)break;
            
            Node* newNode = new Node{val,{}};
            curr->children.push_back(newNode);
            q.push(newNode);
        }
    }

    return dummy.children[0];
}

void removeUselessLayers(Node* root){
    queue<Node*> BFSQueue;
    vector<Node*> previous,current,toBeDeleted;//Ползваме ги за да пазим текущия и предишния слой
    
    Node* currNode;
    BFSQueue.push(root);
    previous.push_back(root);
    
    int layerCounter = 1; // Промелниви за следене на слой
    int nextLayerCounter = 0;
    int depth = 0; 

    bool hasOneChild = true;

    while(!BFSQueue.empty()){
        currNode = BFSQueue.front();
        BFSQueue.pop();
        layerCounter--;
        
        for(Node* child: currNode->children){
            BFSQueue.push(child);
            current.push_back(child);
            hasOneChild &= (child->children.size()==1); 
            nextLayerCounter++;
        }

        if(!layerCounter){//приключен слой
            depth++;
            layerCounter = nextLayerCounter;
            nextLayerCounter = 0;

            if(hasOneChild){//Ако в слоя има само върхове с по едно дете
                vector<Node*> temp = current;
                toBeDeleted.insert(toBeDeleted.end(),current.begin(),current.end());
                current.clear();
                for(Node* node: previous)//Само пренасочваме указателите от предишния слоя 
                    for(Node*& child: node->children)
                        child = child->children[0];
                
                //Текущия слой вече не е достижим от корена, но се намира в опашката на BFS-то
                //Добавили сме указателите на текущия слой и във вектора tоBeDeleted
            }
            else{
                previous = std::move(current);
                current = vector<Node*>();
                //Ако няма да премахваме слоя, текущия става предишен, а текущия е празен
            }
            hasOneChild = true;
        }
    }
    for(Node* node:toBeDeleted)//Изтриваме накрая излишните елементи
        delete node;
}

void formatedPrint(Node* curr,int depth,bool last, std::string& prefix){
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
void print(Node* root){
    std::string s = "";
    formatedPrint(root,0,1, s);
}

int main(){
    ifstream in("test1.txt");
    Node* root = inputTree(in);
    print(root);
    removeUselessLayers(root);
    print(root);
}

