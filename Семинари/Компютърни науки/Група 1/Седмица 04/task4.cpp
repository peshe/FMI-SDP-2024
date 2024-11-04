#include <iostream>
#include <stack>

using namespace std;

int main(){
    string input="The quick brown fox jumps over the lazy dog";
    stack<string> s;
    s.push("");
    for(auto x:input){
        if(x==' ')
            s.push("");
        else s.top()+=x;
    }

    string result="";
    
    while(!s.empty()){
        result+=s.top();
        result+=' ';
        s.pop();
    }
    cout<<result;
}

