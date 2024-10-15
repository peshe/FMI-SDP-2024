#pragma once

#include <algorithm>
#include <functional>
#include <utility>
#include "autoref.hpp"

template <class T, class U>
class Zip {
	AutoRef<T> rng1;
	AutoRef<U> rng2;

   public:
	template <class A, class B>
	Zip(A &&rng1, B &&rng2) : rng1(std::forward<A>(rng1)), rng2(std::forward<B>(rng2)) {}

	std::size_t size() const { return std::min(rng1->size(), rng2->size()); };

	auto begin() { return Iterator(rng1->begin(), rng2->begin()); }
	auto end() { return Iterator(rng1->begin() + size(),rng2->begin() + size()); }

	auto begin() const { return Iterator(rng1->begin(), rng2->begin()); }
	auto end() const { return Iterator(rng1->begin() + size(), rng2->begin() + size()); }

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
			Iterator res(*this);
			++it1;
			++it2;
			return res;
		}
		inline Iterator &operator--() {
			--it1;
			--it2;
			return *this;
		}
		inline Iterator operator--(int) {
			Iterator res(*this);
			--it1;
			--it2;
			return res;
		}
		inline Iterator &operator+=(int n) {
			it1 += n;
			it2 += n;
			return *this;
		}
		inline Iterator &operator-=(int n) {
			it1 -= n;
			it2 -= n;
			return *this;
		}
		inline Iterator operator+(int n) {
			Iterator res(*this);
			res += n;
			return res;
		}
		inline Iterator operator-(int n) {
			Iterator res(*this);
			res -= n;
			return res;
		}

		inline auto operator*() {
			return std::pair<decltype(*it1) &, decltype(*it2) &>(std::ref(*it1), std::ref(*it2));
		}
		inline bool operator!=(Iterator other) const { return it1 != other.it1 || it2 != other.it2; }
		inline bool operator==(Iterator other) const { return it1 == other.it1 && it2 == other.it2; }

		friend class Zip<T, U>;
	};
};

template <class A, class B>
Zip(A &&, B &&) -> Zip<A, B>;
