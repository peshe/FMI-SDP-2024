#include <iostream>
#include <stack>
#include <string>

bool isDigit(char c)
{
    return c >= '0' && c <= '9';
}
int calculateRPN(std::string expression)
{
    std::stack<int> elements;
    int tmp = 0;
    for(int i = 0; i < expression.length(); i++)
    {
        if(isDigit(expression[i]))
        {
            tmp = tmp * 10 + expression[i] - '0';
        }
        else 
        {
            if(expression[i] == ' ')
            {
                if(tmp != 0) elements.push(tmp);
                tmp = 0;
            }
            else
            {
                switch(expression[i])
                {
                    case '+':
                    {
                        int second, first;
                        second = elements.top();
                        elements.pop();
                        first = elements.top();
                        elements.pop();
                        std::cout << first << " " << second << " + " << std::endl;
                        elements.push(first + second);
                        break;
                    }
                    case '-':
                    {

                        int second, first;
                        second = elements.top();
                        elements.pop();
                        first = elements.top();
                        elements.pop();
                        std::cout << first << " " << second << " - " << std::endl;
                        elements.push(first - second);
                        break;
                    }
                    case '*':
                    {

                        int second, first;
                        second = elements.top();
                        elements.pop();
                        first = elements.top();
                        elements.pop();
                        std::cout << first << " " << second << " * " << std::endl;
                        elements.push(first * second);
                        break;
                    }
                    case '/':
                    {

                        int second, first;
                        second = elements.top();
                        elements.pop();
                        first = elements.top();
                        elements.pop();
                        std::cout << first << " " << second << " / " << std::endl;
                        elements.push(first / second);
                        break;
                    }
                    case '^':
                    {

                        int second, first;
                        second = elements.top();
                        elements.pop();
                        first = elements.top();
                        elements.pop();
                        std::cout << first << " " << second << " ^ " << std::endl;
                        int temp = 1;
                        for(int i = 0; i < second; i++)
                        {
                            temp *= first;
                        }
                        elements.push(temp);
                        break;
                    }
                }
            }
        }
    }
    return elements.top();
}
int main()
{
    std::string expression;
    getline(std::cin, expression);
    std::cout << calculateRPN(expression);
}