
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
void printList(List<T> *l) {
	while (l) {
		std::cout << l->data << " -> ";
		l = l->next;
	}
	std::cout << std::endl;
}

template <class T>
class Queue {
	List<T> *first = nullptr;
	List<T> *last  = nullptr;

   public:
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
		if (!first) throw std::runtime_error("pop empty queue");
		T el = first->data;
		if (first == last) {
			delete first;
			first = last = nullptr;
		} else {
			List<T> *el = first;
			first		= first->next;
			delete el;
		}
		return el;
	}

	bool empty() { return first == nullptr; }

	void print() { printList(first); }

	~Queue() { freeHeap(first); }
};

template <class T>
class Stack {
	List<T> *_top = nullptr;

   public:
	void push(const T &el) {
		List<T> *e = new List<T>{el, _top};
		_top	   = e;
	}

	T &top() { return _top->data; }

	T pop() {
		if (!_top) throw std::runtime_error("pop empty stack");
		T el = _top->data;
		if (_top->next == nullptr) {
			delete _top;
			_top = nullptr;
		} else {
			List<T> *el = _top;
			_top		= _top->next;
			delete el;
		}
		return el;
	}

	void print() { printList(_top); }
	bool empty() { return _top == nullptr; }

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
	Stack<int> s;
	Queue<char> q[2];

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

		if (std::isdigit(*exp)) { s.push(*exp - '0'); }
		if (isOp(*exp)) {
			if (*exp == '*' || *exp == '/') q[0].push(*exp);
			if (*exp == '+' || *exp == '-') q[1].push(*exp);
		}

		if (*exp == '\0') break;
		++exp;
	}

	return s.top();
}

int main() {
	std::cout << strangeEval("2 3 5 + *") << std::endl;
	std::cout << strangeEval("1 2 3 4 5 6 + + * + * 2 -") << std::endl;
}
