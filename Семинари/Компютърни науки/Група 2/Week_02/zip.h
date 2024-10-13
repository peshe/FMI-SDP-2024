#pragma once

#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <type_traits>
#include <utility>
#include <cxxabi.h>

template <class T, class U>
class Zip {
	T rng1;
	U rng2;

   public:
	void debug() {
		std::cout << "T: " << (std::is_lvalue_reference_v<T> ? "reference" : "moved") << " "
				  << "U: " << (std::is_lvalue_reference_v<U> ? "reference" : "moved") << std::endl;
	}

	template <class A, class B>
	Zip(A &rng1, B &rng2) : rng1(rng1), rng2(rng2) {
		debug();
	}
	template <class A, class B>
	Zip(A &&rng1, B &rng2) : rng1(std::move(rng1)), rng2(rng2) {
		debug();
	}
	template <class A, class B>
	Zip(A &rng1, B &&rng2) : rng1(rng1), rng2(std::move(rng2)) {
		debug();
	}
	template <class A, class B>
	Zip(A &&rng1, B &&rng2) : rng1(std::move(rng1)), rng2(std::move(rng2)) {
		debug();
	}

	template <class It1, class It2>
	class Iterator {
		It1 it1;
		It2 it2;

		Iterator(It1 &&it1, It2 &&it2) : it1(std::move(it1)), it2(std::move(it2)) {}

	   public:
		inline Iterator &operator++() {
			++it1;
			++it2;
			return *this;
		}
		inline Iterator operator++(int) {
			it1++;
			it2++;
			return *this;
		}
		inline Iterator &operator--() {
			--it1;
			--it2;
			return *this;
		}
		inline Iterator operator--(int) {
			it1--;
			it2--;
			return *this;
		}

		inline auto operator*() {
			return std::pair<decltype(*it1) &, decltype(*it2) &>(std::ref(*it1), std::ref(*it2));
		}
		inline bool operator!=(Iterator other) const { return it1 != other.it1 && it2 != other.it2; }
		inline bool operator==(Iterator other) const { return it1 == other.it1 || it2 == other.it2; }

		friend class Zip<T, U>;
	};

	auto begin() { return Iterator(rng1.begin(), rng2.begin()); }
	auto end() { return Iterator(rng1.end(), rng2.end()); }

	auto begin() const { return Iterator(rng1.begin(), rng2.begin()); }
	auto end() const { return Iterator(rng1.end(), rng2.end()); }
};

template <class A, class B>
Zip(A &, B &) -> Zip<A &, B &>;

template <class A, class B>
Zip(A &&, B &) -> Zip<A, B &>;

template <class A, class B>
Zip(A &, B &&) -> Zip<A &, B>;

template <class A, class B>
Zip(A &&, B &&) -> Zip<A, B>;
