#include <iostream>
#include <string>
#include <stack>

bool isDigit(char c)
{
    return  (c >= '0' && c <= '9');
}
int getPrecedence(char ch)
{

    if (ch == '+' || ch == '-')
    {
        return 1;
    }
    else if (ch == '*' || ch == '/')
    {
        return 2;
    }
    else if (ch == '^')
    {
        return 3;
    }
    else
    {
        return -1;
    }
}

bool hasLeftAssociativity(char ch) 
{
    return (ch == '+' || ch == '-' || ch == '/' || ch == '*');
}

std::string infixToRpn(std::string expression)
{
    std::stack<char> stack;
    std::string output = "";
    for (int i = 0; i < expression.length(); ++i) 
    {
        char c = expression[i];
        if (isDigit(c))
        {
            output += c;
        }
        else if (c == '(')
        {
            stack.push(c);
        }
        else if (c == ')') 
        {
            while (!stack.empty() && stack.top() != '(')
            {
                output += stack.top();
                stack.pop();
            }
            stack.pop();
        }
        else 
        {
            while (
                !stack.empty()
                && getPrecedence(c) <= getPrecedence(stack.top()) 
                && hasLeftAssociativity(c)) {
                output += stack.top();
                stack.pop();
            }
            stack.push(c);
        }
    }
    while (!stack.empty()) 
    {
        if (stack.top() == '(')
        {
            return "This expression is invalid";
        }
        output += stack.top();
        stack.pop();
    }
    return output;
}
int main()
{
    std::string expression = "5+2/(3-8)^5^2";
    std::cout << infixToRpn(expression);
}
