#include <iostream>
#include <stack>
#include <string>

bool isValid(const std::string& pars)
{
    std::stack<char> st;

    for (const char el : pars)
    {
        if (el == '(' || el == '[' || el == '{')
            st.push(el);
        else if (
            (el == ')' && st.top() == '(') ||
            (el == ']' && st.top() == '[') ||
            (el == '}' && st.top() == '{')
        ) st.pop();
    }

    return st.empty();
}

int main()
{
    std::string input;

    std::getline(std::cin, input);

    std::cout << isValid(input) << std::endl;
    
    return 0;
}