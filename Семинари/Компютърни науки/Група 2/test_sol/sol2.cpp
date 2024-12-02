
#include <cassert>
#include <stdexcept>
#include <iostream>

template <class T>
struct List {
	T	  data;
	List *next;
};

template <class T>
void freeHeap(List<T> *l) {
	List<T> *curr;
	while (l) {
		curr = l->next;
		delete l;
		l = curr;
	}
}

template <class T>
class Queue {
	List<T> *first = nullptr;
	List<T> *last  = nullptr;

   public:
	Queue()							 = default;
	Queue &operator=(const Queue &q) = delete;
	Queue(const Queue &q)			 = delete;

	void push(const T &el) {
		List<T> *e = new List<T>{el, nullptr};

		if (first) {
			last->next = e;
			last	   = e;
		} else {
			first = last = e;
		}
	}

	T &front() { return first->data; }

	T pop() {
		T		 ret = first->data;
		List<T> *el	 = first;
		first		 = first->next;
		if (last == el) last = nullptr;
		delete el;
		return ret;
	}

	bool empty() const { return first == nullptr; }

	~Queue() { freeHeap(first); }
};

template <class T>
class Stack {
	List<T> *_top = nullptr;

   public:
	Stack()							 = default;
	Stack &operator=(const Stack &s) = delete;
	Stack(const Stack &s)			 = delete;

	void push(const T &el) {
		List<T> *e = new List<T>{el, _top};
		_top	   = e;
	}

	T &top() { return _top->data; }

	T pop() {
		T		 ret = _top->data;
		List<T> *el	 = _top;
		_top		 = _top->next;
		delete el;
		return ret;
	}

	bool empty() const { return _top == nullptr; }

	~Stack() { freeHeap(_top); }
};

bool isOp(char c) { return c == '+' || c == '-' || c == '*' || c == '/'; }

int (*f(char c))(int, int) {
	switch (c) {
		case '+': return [](int a, int b) { return a + b; };
		case '-': return [](int a, int b) { return a - b; };
		case '*': return [](int a, int b) { return a * b; };
		case '/': return [](int a, int b) { return a / b; };
		default: throw std::runtime_error("bad operation");
	}
}

int strangeEval(const char *exp) {
	Stack<int>	s;		  // operand stack
	Queue<char> q[2];	  // q[0] holds the '*' and '/' operators
						  // q[1] holds the '+' and '-' operators
	try {
		while (true) {
			if (std::isdigit(*exp) || *exp == '\0') {
				for (int i = 0; i < 2; ++i) {
					while (!q[i].empty()) {
						int a1 = s.pop();
						int a2 = s.pop();
						s.push(f(q[i].pop())(a2, a1));
					}
				}
			}

			if (std::isdigit(*exp)) {
				int num = 0;
				while (std::isdigit(*exp)) {
					num = num * 10 + *exp - '0';
					++exp;
				}
				s.push(num);
				--exp;
			}
			if (isOp(*exp)) {
				if (*exp == '*' || *exp == '/') q[0].push(*exp);
				if (*exp == '+' || *exp == '-') q[1].push(*exp);
			}

			if (*exp == '\0') break;
			++exp;
		}
	} catch (...) { throw std::runtime_error("bad expression"); }
	// if all above is correct, then the stack should have at least one element
	int res = s.pop();
	if (!s.empty()) throw std::runtime_error("bad expression");
	return res;
}

int main() {
	std::cout << strangeEval("2 3 5 + *") << std::endl;
	std::cout << strangeEval("2 3 5 * +") << std::endl;
	std::cout << strangeEval("1 2 3 4 5 6 + + * + * 2 -") << std::endl;
	std::cout << strangeEval("1 2 3 4 5 6 * * + + + 2 -") << std::endl;
	return 0;
}
