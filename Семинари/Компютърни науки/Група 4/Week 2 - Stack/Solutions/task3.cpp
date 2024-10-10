#include <iostream>
#include <string>
#include <stack>

std::string revStr(std::string str)
{
    std::stack<char> st;
    std::string result = "";
    for(char i : str)
    {
        st.push(i);
    }
    while(!st.empty())
    {
        result.push_back(st.top());
        st.pop();
    }
    return result;
}
int main()
{
    std::string niz;
    std::cin >> niz;
    std::cout << revStr(niz) << std::endl;
}