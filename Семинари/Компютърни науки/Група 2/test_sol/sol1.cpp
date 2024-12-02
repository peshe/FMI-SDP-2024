#include <functional>
#include <iostream>
#include <stdexcept>

template <class T>
struct List {
	T	  data;
	List *next = nullptr;
};

using Interval = std::pair<int, int>;
std::ostream &operator<<(std::ostream &out, const Interval &i) {
	return out << "[" << i.first << "," << i.second << "]";
}

template <class T>
List<T> *getElement(List<T> *l, int n) {
	for (int i = 0; i < n; ++i) {
		l = l->next;
		if (!l) throw std::runtime_error("invalid index");
	}
	return l;
}

template <class T>
void freeHeap(List<T> *l) {
	List<T> *curr;
	while (l) {
		curr = l->next;
		delete l;
		l = curr;
	}
}

void replaceSublist(List<int> *l, const Interval &sublist) {
	if (sublist.first > sublist.second) throw std::runtime_error("invalid range");
	List<int> *start		= getElement(l, sublist.first);
	List<int> *last_removed = getElement(start, sublist.second - sublist.first);
	List<int> *end			= last_removed->next;
	last_removed->next		= nullptr;

	int sum = 0;
	{
		List<int> *curr = start;
		while (curr) {
			sum += curr->data;
			curr = curr->next;
		}
	}
	start->data = sum;
	freeHeap(start->next);
	start->next = end;
}

void sumSublists(List<int> *l, List<Interval> *intervals) {
	while (intervals) {
		Interval &i = intervals->data;
		try {
			replaceSublist(l, i);
		} catch (...) {
			throw std::runtime_error(std::string("invalid indices in list: [") + std::to_string(i.first) + ", " +
									 std::to_string(i.second) + "]");
		}
		intervals = intervals->next;
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
List<T> *makeList(int n, std::function<void(T &)> &&f) {
	List<T>	 dummy;
	List<T> *l = &dummy;
	for (int i = 0; i < n; ++i) {
		try {
			l->next = new (std::nothrow) List<T>();
			f(l->next->data);
			l = l->next;
		} catch (...) {
			freeHeap(dummy.next);
			throw;
		}
	}
	l->next = nullptr;
	return dummy.next;
}

template <class T>
class List_ptr {
	List<T> *l;

   public:
	List_ptr(List<T> *l) : l(l) {}
	~List_ptr() { freeHeap(l); }

	operator List<T> *() { return l; }
};

/*
9
1 -5 3 2 20 -14 1 7 9
3
1 3
0 0
2 4

*/

int main() {
	int n, k;
	std::cin >> n;

	List_ptr<int> l = makeList<int>(n, [](int &k) { std::cin >> k; });

	std::cin >> k;
	List_ptr<Interval> intervals = makeList<Interval>(k, [](Interval &k) { std::cin >> k.first >> k.second; });

	printList<int>(l);
	printList<Interval>(intervals);

	std::cout << std::endl;

	sumSublists(l, intervals);
	printList<int>(l);

	return 0;
}
