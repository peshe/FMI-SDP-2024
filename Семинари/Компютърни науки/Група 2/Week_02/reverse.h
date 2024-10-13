#pragma once

#include <utility>
template <class T>
class Reverse {
	T ref;

   public:
	template <class Q>
	Reverse(Q &ref) : ref(ref) {}
	template <class Q>
	Reverse(Q &&ref) : ref(std::move(ref)) {}

	template <class It>
	class Iterator : public It {
		Iterator(It it) : It(it) {}
		Iterator(It &&it) : It(it) {}
	   public:
		inline Iterator &operator++() {
			this->It::operator--();
			return *this;
		}
		inline Iterator operator++(int) {
			this->It::operator--(0);
			return *this;
		}
		inline Iterator &operator--() {
			this->It::operator++();
			return *this;
		}
		inline Iterator operator--(int) {
			this->It::operator++(0);
			return *this;
		}
		friend class Reverse<T>;
	};

	auto begin() { return Iterator(--ref.end()); }
	auto end() { return Iterator(--ref.begin()); }
};

template <class Q>
Reverse(Q &) -> Reverse<Q &>;

template <class Q>
Reverse(Q &&) -> Reverse<Q>;
