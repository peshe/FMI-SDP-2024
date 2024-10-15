#pragma once

#include <utility>
#include "autoref.hpp"

template <class T>
class Reverse {
	AutoRef<T> ref;

   public:
	template <class Q>
	Reverse(Q &&ref) : ref(std::forward<Q>(ref)) {}

	std::size_t size() const { return ref->size(); }

	auto begin() { return Iterator(ref->end() - 1); }
	auto end() { return Iterator(ref->begin() - 1); }

	template <class It>
	class Iterator  {
		It it;
		Iterator(It &&it) : it(it) {}
		Iterator(It &it) : it(it) {}

	   public:
		inline Iterator &operator++() {
			--it;
			return *this;
		}
		inline Iterator operator++(int) {
			Iterator res(*this);
			--it;
			return res;
		}
		inline Iterator &operator--() {
			++it;
			return *this;
		}
		inline Iterator operator--(int) {
			Iterator res(*this);
			++it;
			return res;
		}
		inline Iterator operator+(int n) const {
			Iterator res(*this);
			res.it -= n;
			return res;
		}
		inline Iterator operator-(int n) const {
			Iterator res(*this);
			res.it += n;
			return res;
		}
		inline Iterator &operator+=(int n) {
			it -= n;
			return *this;
		}
		inline Iterator &operator-=(int n) {
			it += n;
			return *this;
		}

		inline auto& operator*() {
			return *it;
		}
		inline bool operator!=(Iterator other) const { return it != other.it; }
		inline bool operator==(Iterator other) const { return it == other.it; }
		friend class Reverse<T>;
	};
};

template <class Q>
Reverse(Q &&) -> Reverse<Q>;
