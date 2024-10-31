#include <cassert>
#include <iostream>
#include <stack>
#include <stdexcept>

template <class T>
class Queue {
   private:
	void flipStacks() {
		if (s2.empty()) {
			while (!s1.empty()) {
				s2.push(s1.top());
				s1.pop();
			}
		} else if (s1.empty()) {
			while (!s2.empty()) {
				s1.push(s2.top());
				s2.pop();
			}
		} else {
			throw std::runtime_error("invalid call to flip");
		}
	}

   public:
	void push(const T &el) { s1.push(el); }
	void push(T &&el) {
		s1.push(std::move(el));
	}

	void pop() {
		this->flipStacks();
		s2.pop();
		this->flipStacks();
	}

	T front() const {
		this->flipStacks();
		T temp = s2.top();
		this->flipStacks();
		return temp;
	}
	T front() {
		this->flipStacks();
		T temp = s2.top();
		this->flipStacks();
		return temp;
	}

	const T &back() const { return s1.top(); }
	T		&back() { return s1.top(); }

	bool		empty() const { return this->size() == 0; }
	std::size_t size() const { return this->s1.size(); }

   private:
	std::stack<T> s1, s2;
};

int main() {
	Queue<int> q;
	q.push(1);
	q.push(2);
	q.push(3);
	q.push(4);
	assert(q.size() == 4);
	assert(!q.empty());

	int a = q.front();
	q.pop();
	int b = q.front();
	q.pop();
	int c = q.front();
	q.pop();
	int d = q.front();
	q.pop();
	assert(q.empty());

	assert(a == 1);
	assert(b == 2);
	assert(c == 3);
	assert(d == 4);
	
}
