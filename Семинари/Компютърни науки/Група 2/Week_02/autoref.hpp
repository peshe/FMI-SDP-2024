#pragma once

#include <type_traits>
#include <utility>

template <typename T>
struct AutoRef {
	T ref;

	template <class Q>
	AutoRef(Q &value) : ref(value) {}
	template <class Q>
	AutoRef(Q &&value) : ref(std::move(value)) {}

	// removing the reference is needed for cases where T is a reference itself
	std::remove_reference_t<T>* operator->() {return &ref;}
	const std::remove_reference_t<T>* operator->() const {return &ref;}
	
	// reference to reference is illegal and thus T& is always deduced as just
	// a reference even when T is a reference type
	T& operator*() {return ref;}
	const T& operator*() const {return ref;}

	// allow casting to mimicked type
	operator T&() {return ref;}
	operator const T&() const {return ref;}

	T& get() {return ref;}
	const T& get() const {return ref;}

};

// template deduction guide so that T can be deduced to Q ot Q&
template <class Q>
AutoRef(Q &value) -> AutoRef<Q &>;

template <class Q>
AutoRef(Q &&value) -> AutoRef<Q>;
