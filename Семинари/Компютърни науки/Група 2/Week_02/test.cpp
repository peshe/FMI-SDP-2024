#include <iostream>
#include <type_traits>
#include <utility>
#include "vector.h"

template <typename T>
struct Storage {
	inline static constexpr bool is_reference = std::is_lvalue_reference_v<T>;

	T ref;

	template <class Q>
	Storage(Q &value) : ref(value) {}
	template <class Q>
	Storage(Q &&value) : ref(std::move(value)) {}

	void print() { std::cout << "is ref " << is_reference << std::endl; }
};

template <class Q>
Storage(Q &value) -> Storage<Q &>;

template <class Q>
Storage(Q &&value) -> Storage<Q>;

template <class T, class U>
class Storage2 {
	Storage<T> s1;
	Storage<U> s2;

   public:
	template <class A, class B>
	Storage2(A &&v1, B &&v2) : s1(std::forward<A>(v1)), s2(std::forward<B>(v2)) {}

	void print() {
		s1.print();
		s2.print();
	}
};

template <class A, class B>
Storage2(A &&, B &&) -> Storage2<A, B>;

int main() {
	int	 a	 = 1;
	int &ref = a;

	Vector<int> v = {1, 2, 3};
	Storage(v).print();
	Storage(Vector<int>{1, 2, 3}).print();

	Storage2(a, ref).print();
	Storage2(std::move(a), 1).print();
	Storage2(ref, 1).print();

	Storage2(Vector<int>{1, 2, 3}, v).print();

	return 0;
}
