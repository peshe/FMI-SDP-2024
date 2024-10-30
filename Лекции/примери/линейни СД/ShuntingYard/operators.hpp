/******************************************************************
*  Sample code to the course "Data Structures And Algorithms", FMI
*
* Helper methods and classes to build shunting yard algorithm.
* 
* (cc) Petar Armyanov, FMI, 2024
*******************************************************************/

#pragma once

#ifndef __OPERATORS_HEADER_INCLUDED_
#define __OPERATORS_HEADER_INCLUDED_

#include <vector>
#include <stdexcept>
#include <cctype>

namespace fmi::sdp {


//Some helper functions
inline bool isOpenBr(char symbol)
{
    return symbol == '(' || symbol == '[';
}

inline bool isCloseBr(char symbol)
{
    return symbol == ')' || symbol == ']';
}

inline bool matching(char open, char close)
{
    return open == '(' && close == ')' ||
           open == '[' && close == ']';
}

inline int getPriority(char op) {
    if (op == '+' || op == '-') return 10;
    if (op == '*' || op == '/') return 20;
    else return 0;
}

inline int apply(int l, int r, char op)
{
    switch (op) {
    case '+': return l + r;
    case '-': return l - r;
    case '*': return l * r;
    case '/': if (r) return l / r; 
              else throw std::invalid_argument("Zero division!");
    default: throw std::logic_error("Unknown operation!");
    }
    return 0;
}





//Base class for operators in the expression
struct Operator
{
    char symbol;
    int priority;
    Operator(char s, int pr) :symbol(s), priority(pr) {}

    virtual int apply(int left, int right) const = 0;
    virtual bool isBrace() const { return false; }
    virtual ~Operator() {}
};

//Factory class for selecting appropriate operator
//The class is singleton.
class OperatorSelector
{
private:
    //the only constructor
    OperatorSelector() = default;
    
    // Deprecate all copy methods
    OperatorSelector(const OperatorSelector&) = delete;
    OperatorSelector& operator=(const OperatorSelector&) = delete;

public:
    //Static get instance method
    static OperatorSelector* getSelector()
    {
        static OperatorSelector theSelector;
        return &theSelector;
    }

    //public method to register new operator class
    void registerOperator(const Operator* op)
    {
        if (op && !selectOperator(op->symbol)) {
            operators.push_back(op);
        }
    }

    //method to select (construct) operator by a given symbol
    //from the registered ones 
    const Operator* selectOperator(char symbol) const
    {
        for (const Operator* const& op : operators) {
            if (op->symbol == symbol) {
                return op;
            }
        }
        return nullptr;
    }

private:
    std::vector<const Operator*> operators;
};

// Helper template class to register an operator class
// The object from this class keep the instance of the operator,
// so have to be alive more than the selector!
template <typename OP>
class operatorRegistrator
{
    OP op;
public:
    operatorRegistrator() {
        OperatorSelector::getSelector()->registerOperator(&op);
    }
};


// Some operator implementations
struct sumOperator : public Operator
{
public:
    sumOperator() : Operator('+', 10)
    {}
    int apply(int l, int r) const override
    {
        return l + r;
    }
};
static operatorRegistrator<sumOperator> _sumReg;

struct subOperator : public Operator
{
public:
    subOperator() : Operator('-', 10)
    {}
    int apply(int l, int r) const override
    {
        return l - r;
    }
};
static operatorRegistrator<subOperator> _subReg;

struct mulOperator : public Operator
{
public:
    mulOperator() : Operator('*', 20)
    {}
    int apply(int l, int r) const override
    {
        return l * r;
    }
};
static operatorRegistrator<mulOperator> _mulReg;

struct divOperator : public Operator
{
public:
    divOperator() : Operator('/', 20)
    {}
    int apply(int l, int r) const override
    {
        if (r) return l / r;
        throw std::invalid_argument("Division by zero");
    }
};
static operatorRegistrator<divOperator> _divReg;

// Special classes for brace operators.
//has lowest precedence.
struct braceOperator : public Operator
{
    braceOperator(char c) : Operator(c, 0) {}
    
    int apply(int, int) const override
    {
        throw std::exception("Bad operation!");
    }

    virtual bool isBrace() const override { return true; }
    virtual bool match(char ch) const = 0;
    virtual bool isOpen() const = 0;
};

struct openBrOperator : public braceOperator
{
    openBrOperator() : braceOperator('(') {}
    virtual bool match(char c) const override { return c == ')'; }
    virtual bool isOpen() const override { return true; }
};
struct closeBrOperator : public braceOperator
{
public:
    closeBrOperator() : braceOperator(')') {}
    virtual bool match(char c) const override { return c == '('; }
    virtual bool isOpen() const override { return false; }
};

static operatorRegistrator<openBrOperator> _openBrReg;
static operatorRegistrator<closeBrOperator> _closeBrReg;

struct openBr2Operator : public braceOperator
{
    openBr2Operator() : braceOperator('[') {}
    virtual bool match(char c) const override { return c == ']'; }
    virtual bool isOpen() const override { return true; }
};
struct closeBr2Operator : public braceOperator
{
public:
    closeBr2Operator() : braceOperator(']') {}
    virtual bool match(char c) const override { return c == '['; }
    virtual bool isOpen() const override { return false; }
};
static operatorRegistrator<openBr2Operator> _openBr2Reg;
static operatorRegistrator<closeBr2Operator> _closeBr2Reg;


} // namespace fmi::sdp

#endif //__OPERATORS_HEADER_INCLUDED_
