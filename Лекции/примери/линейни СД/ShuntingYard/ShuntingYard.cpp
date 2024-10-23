/******************************************************************
*  Sample code to the course "Data Structures And Algorithms", FMI
*
* Implementation of the Dejcstra Shunting yard algorithm.
* Uses polymorphic operators and demonstrate some patterns also.
*
* (cc) Petar Armyanov, FMI, 2024
*******************************************************************/

#include <iostream>
#include <cctype>

#include "operators.hpp"
#include "linkedStack.hpp"

namespace fmi::sdp {

static int getNumber(const char*& expr)
{
    int result = 0;
    while (isdigit(*expr)) {
        result = result * 10 + (*expr - '0');
        ++expr;
    }
    return result;
}


static void apply(LinkedStack<int>& numbers, char op) {
    if (numbers.isEmpty()) {
        throw std::logic_error("bad expression!");
    }
    int right = numbers.pop();
    if (numbers.isEmpty()) {
        throw std::logic_error("bad expression!");
    }
    int left = numbers.pop();
    numbers.push(apply(left, right, op));
}

// Implementation of the algorithm in C-style
int shuntingYard(const char* expression)
{
    LinkedStack<int> numbers;                   // The stack with the numbers and temporary results
    LinkedStack<char> operators;                // The stack with postponed operators

    while (*expression) {
        if (isspace(*expression)) {                 // Skip the spaces
            ++expression;
        }

        else if (isdigit(*expression)) {            // Parse a number
            numbers.push(getNumber(expression));
        }

        else if (isOpenBr(*expression)) {           // Parse an open brace
            operators.push(*expression);
            ++expression;
        }

        else if (isCloseBr(*expression)) {          // Parse a close brace
            while (!operators.isEmpty() &&
                   !isOpenBr(operators.top())) {
                char op = operators.pop();
                apply(numbers, op);
            } 
            if (operators.isEmpty() ||
                !matching(operators.pop(), *expression)){
                throw std::logic_error("bad expression!");
            }
            ++expression;
        }

        else {                                      // Everything else is threated as an operator
            char op = *expression;
            while (!operators.isEmpty() && getPriority(operators.top()) >= getPriority(op)) {
                apply(numbers, operators.pop());
            }
            operators.push(op);
            ++expression;
        }
    }

    // Pop out and apply all operators left
    while (!operators.isEmpty()) {
        apply(numbers, operators.pop());
    }

    //Some final checks
    if (numbers.isEmpty()) {
        throw std::logic_error("bad expression!");
    }
    int result = numbers.pop();
    if (!numbers.isEmpty()) {
        throw std::logic_error("bad expression!");
    }

    return result;
}


// Object-oriented implementation of the algorithm.
int shuntingYardPoly(const char* expression)
{
    LinkedStack<int> numbers;                   // The stack with the numbers and temporary results
    LinkedStack<const Operator*> operators;           // The stack with postponed operators


    while (*expression) {
        if (isspace(*expression)) {                 // Skip the spaces
            ++expression;
        }
        else if (isdigit(*expression)) {            // Parse a number
            numbers.push(getNumber(expression));
        }

        else {
            const Operator* op = OperatorSelector::getSelector()->selectOperator(*expression);
            if (!op) throw std::logic_error("Unknown operation!");

            if (op->isBrace()) {
                const braceOperator* br = dynamic_cast<const braceOperator*>(op);
                assert(br);
                if (br->isOpen()) {
                    operators.push(op);
                }
                else {
                    while (!operators.isEmpty() && !operators.top()->isBrace()) {
                        int right = numbers.pop(), left = numbers.pop();
                        numbers.push(operators.pop()->apply(left, right));
                    }
                    if (operators.isEmpty() ||
                        !dynamic_cast<const braceOperator*>(operators.top())->match(op->symbol)) {
                        throw std::logic_error("bad expression!");
                    }
                    assert(operators.top()->isBrace() &&
                        dynamic_cast<const braceOperator*>(operators.top())->match(op->symbol));
                    operators.pop();
                }
                ++expression;
            }
            else {                                      // Everything else is threated as an operator
                while (!operators.isEmpty() && (operators.top()->priority > op->priority)) {
                    int right = numbers.pop(), left = numbers.pop();
                    numbers.push(operators.pop()->apply(left, right));
                }
                operators.push(op);
                ++expression;
            }
        }
    }

    // Pop out and apply all operators left
    while (!operators.isEmpty()) {
        int right = numbers.pop(), left = numbers.pop();
        numbers.push(operators.pop()->apply(left, right));
    }

    //Some final checks
    if (numbers.isEmpty()) {
        throw std::logic_error("bad expression!");
    }
    int result = numbers.pop();
    if (!numbers.isEmpty()) {
        throw std::logic_error("bad expression!");
    }

    return result;
}


} // namespace sdp::fmi


int main()
{
    const char* tests[] = {
        "3+6*2/0",
        "3+6*2",
        "36+2",
        "3 * ( 6 + 2 )",
        "3*(6+2) / 2+6*5",
        "3*(6+2) / (2+6*1)",
        "3*(6-2) ^ ((1+2*4)-7)",
        "[10 / (((3 * (6 - 27) + ((10 + 2 * 4) * 7)) + 137) / 100)]"
    };
    
    for (const char* test : tests) { 
        try {
            std::cout << test << " = "
                      << fmi::sdp::shuntingYard(test) << std::endl;
        }
        catch (std::exception& ex) {
            std::cerr << std::endl << test << " -> " << ex.what() << "\n";
        }
    }


    for (const char* test : tests) {
        try {
            std::cout << test << " = "
                << fmi::sdp::shuntingYardPoly(test) << std::endl;
        }
        catch (std::exception& ex) {
            std::cerr << std::endl << test << " -> " << ex.what() << "\n";
        }
    }
    return 0;
}
