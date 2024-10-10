#include <iostream>
#include <stack>
#include <string>

bool isOpen(char c)
{
    return c == '(' || c == '{' || c == '[';
}
char getOpen(char c)
{
    if(c == ')')
    {
        return '(';
    }
    else if(c == ']')
    {
        return '[';
    }
    else if(c == '}')
    {
        return '{';
    }
    else
    {
        return 0;
    }
}
bool correct(std::string expression)
{
    std::stack<char> symbols;
    for(char i : expression)
    {
        if(isOpen(i))
        {
            symbols.push(i);
        }
        else
        {
            std::cout << i << std::endl;
            if(symbols.empty())
            {
                return false;
            }
            else if(symbols.top() != getOpen(i))
            {
                return false;
            }
            else
            {
                symbols.pop();
            }
        }
    }
    return symbols.empty();
}
int main()
{
    std::string str;
    std::cin >> str;
    std::cout << std::boolalpha << correct(str);
}