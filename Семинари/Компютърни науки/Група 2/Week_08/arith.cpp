#include <cerrno>
#include <iostream>
#include "../Week_04/sy.h"

class Expression {
   public:
	virtual double operator()(double x = 0) = 0;
	virtual void   print(std::ostream &out) = 0;

	Expression()							  = default;
	Expression &operator=(const Expression &) = delete;
	Expression(const Expression &)			  = delete;

	virtual ~Expression() {};
};

class BinaryOperation : public Expression {
   protected:
	virtual double op(double a, double b)	   = 0;
	virtual void   print_op(std::ostream &out) = 0;

   public:
	Expression *arg1;
	Expression *arg2;

	BinaryOperation(Expression *arg1, Expression *arg2) : arg1(arg1), arg2(arg2) {}

	virtual double operator()(double x) override { return op(arg1->operator()(x), arg2->operator()(x)); }
	virtual void   print(std::ostream &out) override {
		  out << '(';
		  arg1->print(out);
		  print_op(out);
		  arg2->print(out);
		  out << ')';
	}

	virtual ~BinaryOperation() {
		delete arg1;
		delete arg2;
	}
};

class Sum : public BinaryOperation {
   protected:
	virtual double op(double a, double b) final override { return a + b; }
	virtual void   print_op(std::ostream &out) final override { out << " + "; }

   public:
	using BinaryOperation::BinaryOperation;
};

class Sub : public BinaryOperation {
   protected:
	virtual double op(double a, double b) final override { return a - b; }
	virtual void   print_op(std::ostream &out) final override { out << " - "; }

   public:
	using BinaryOperation::BinaryOperation;
};

class Mul : public BinaryOperation {
   protected:
	virtual double op(double a, double b) final override { return a * b; }
	virtual void   print_op(std::ostream &out) final override { out << " * "; }

   public:
	using BinaryOperation::BinaryOperation;
};

class Div : public BinaryOperation {
   protected:
	virtual double op(double a, double b) final override { return a / b; }
	virtual void   print_op(std::ostream &out) final override { out << " / "; }

   public:
	using BinaryOperation::BinaryOperation;
};

class Pow : public BinaryOperation {
   protected:
	virtual double op(double a, double b) final override { return std::pow(a, b); }
	virtual void   print_op(std::ostream &out) final override { out << " ^ "; }

   public:
	using BinaryOperation::BinaryOperation;
};

Expression *makeExpression(char op, Expression *a, Expression *b) {
	switch (op) {
		case '+': return new Sum(a, b);
		case '-': return new Sub(a, b);
		case '*': return new Mul(a, b);
		case '/': return new Div(a, b);
		case '^': return new Pow(a, b);
	}
	throw std::runtime_error("bad operation");
}

class Number : public Expression {
	double value;

   public:
	Number(double value) : value(value) {}

	virtual double operator()(double) final override { return value; }
	virtual void   print(std::ostream &out) final override { out << value; }
};

class Variable : public Expression {
	virtual double operator()(double x) final override { return x; }
	virtual void   print(std::ostream &out) final override { out << 'x'; }
};

Expression *fromRPN(const std::string &expression) {
	std::stack<Expression *> stack;

	for (std::size_t i = 0; i < expression.size(); ++i) {
		char c = expression[i];
		if (std::isdigit(c)) {
			int num = 0;
			while (std::isdigit(expression[i])) {
				num *= 10;
				num += expression[i] - '0';
				++i;
			}
			stack.push(new Number(num));
		}
		if (std::isalpha(c)) { stack.push(new Variable()); }

		if (isOp(c)) {
			Expression *right = stack.top();
			stack.pop();
			Expression *left = stack.top();
			stack.pop();
			stack.push(makeExpression(c, left, right));
		}
	}
	return stack.top();
}

void optimizeTree(Expression *&exp) {
	Pow *pow1;
	Pow *pow2;

	if ((pow1 = dynamic_cast<Pow *>(exp)) != nullptr) {
		if ((pow2 = dynamic_cast<Pow *>(pow1->arg1)) != nullptr) {
			Expression *a = pow2->arg1;
			Expression *b = pow2->arg2;
			Expression *c = pow1->arg2;
			pow2->arg1	  = nullptr;
			pow2->arg2	  = nullptr;
			pow1->arg2	  = nullptr;

			delete pow1;

			exp = new Pow(a, new Mul(b, c));
			// continue from the same node because it was changed
			optimizeTree(exp);
		}
	} else {
		BinaryOperation *bop;
		if ((bop = dynamic_cast<BinaryOperation *>(exp)) != nullptr) {
			optimizeTree(bop->arg1);
			optimizeTree(bop->arg2);
		}
	}
}

int main() {
	{
		std::string rpn = shuntingYard("32 + 40 * 2 / (10 - 13) ^ 2 ^ 3");

		std::cout << rpn << std::endl;

		Expression *tree = fromRPN(rpn);

		std::cout << tree->operator()() << std::endl;
		delete tree;
	}

	{
		Expression *tree = fromRPN(shuntingYard("x * x + 10 * x"));
		std::cout << tree->operator()(1) << std::endl;
		delete tree;
	}

	{
		std::string exp	 = shuntingYard("((2 ^ x) ^ x) ^ x");
		Expression *tree = fromRPN(exp);
		tree->print(std::cout);
		std::cout << std::endl;

		optimizeTree(tree);
		tree->print(std::cout);
		std::cout << std::endl;

		std::cout << (*tree)() << std::endl;
		delete tree;
	}
}
