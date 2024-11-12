#include <iostream>
#include <stack>

using namespace std;

struct RecFrame {
    int n;          
    bool beforeRec;  

    // RecFrame(int n, bool isCalled) : n(n), isCalled(isCalled) {}
};

int main(){
    stack<RecFrame> factoriel;
    RecFrame curr;
    factoriel.push({5, true});
    int result = 1;// result се използва като аргумент по референция

    while(!factoriel.empty()){
        curr = factoriel.top();
        factoriel.pop();
        if(curr.n == 0 ){
            // База на рекурсията 
            continue;
        }
        if(curr.beforeRec){
            //тяло преди рекурсивно извикване
            // в тази задача няма значение дали пресмятаме преди или след рекурсивното извикване
            // result = result * curr.n;

            // Добавяме frame за тялото след рекурсивното извикване с текущите аргументи
            factoriel.push({curr.n,false});

            // Добавяме следващото извикване. То ще се изпълни преди продължението на текущите аргументи
            factoriel.push({curr.n-1,true});
        }
        else{
            //тяло след рекурсивното извикване
            result = result * curr.n;
        }
        
    }
    std::cout<<result<<std::endl;

}