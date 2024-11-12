#include <iostream>
#include <stack>
#include <string>

bool evaluate(const std::string& input)
{
    std::stack<char> operators;
    std::stack<bool> operands;

    for (const char el : input)
    {
        if (el == '0' || el == '1')
            operands.push(el - '0');
        else if (el == '~' || el == '&' || el == '|')
            operators.push(el);
        else if (el == ')')
        {
            char currentOperator = operators.top();
            operators.pop();

            if (currentOperator == '~')
            {
                bool currentOperand = operands.top();
                operands.pop();

                operands.push(!currentOperand);
            }
            else
            {
                bool currentOperand1 = operands.top();
                operands.pop();
                bool currentOperand2 = operands.top();
                operands.pop();

                bool newOperand = (
                    currentOperator == '&' ?
                    currentOperand1 && currentOperand2 :
                    currentOperand1 || currentOperand2    
                );

                operands.push(newOperand);
            }
        }
    }

    return
        operators.empty() && // there must be no additional operands
        operands.size() == 1 && // only one value remained
        operands.top(); // actual value
}

int main()
{
    std::string input;
    std::getline(std::cin, input);

    std::cout << evaluate(input) << std::endl;

    return 0;
}