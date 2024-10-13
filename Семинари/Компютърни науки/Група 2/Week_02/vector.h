#pragma once
#include <algorithm>
#include <cassert>
#include <initializer_list>
#include <iostream>

template <class T>
class Vector {
   private:
	std::size_t Capacity;
	std::size_t Size;
	T		   *Arr;

   public:
	Vector();
	~Vector();
	Vector(const Vector &other);
	Vector(Vector &&other);
	Vector(std::initializer_list<T> other);
	Vector &operator=(const Vector &other);
	Vector &operator=(Vector &&other);
	void	clear();

	T		&operator[](int i) { return Arr[i]; }
	const T &operator[](int i) const { return Arr[i]; }

	void resize(std::size_t new_cap);

	void push_back(T &&value);
	void push_back(const T &value);

	void pop_back();
	std::size_t size() const {return Size;}


	class Iterator {
	   protected:
		Vector<T>  *v;
		std::size_t index;
		Iterator(Vector<T> *v, std::size_t index) : v(v), index(index) {}

	   public:
		inline Iterator &operator++();
		inline Iterator	 operator++(int);
		inline Iterator &operator--();
		inline Iterator	 operator--(int);
		inline T		&operator*() { return (*v)[index]; }
		inline bool		 operator!=(Iterator other) const { return index != other.index || v != other.v; }
		inline bool		 operator==(Iterator other) const { return index == other.index && v == other.v; }
		friend class Vector<T>;
	};

	class ConstIterator {
	   protected:
		const Vector<T> *v;
		std::size_t		 index;
		ConstIterator(const Vector<T> *v, std::size_t index) : v(v), index(index) {}

	   public:
		inline ConstIterator &operator++();
		inline ConstIterator  operator++(int);
		inline ConstIterator &operator--();
		inline ConstIterator  operator--(int);
		inline const T		 &operator*() { return (*v)[index]; }
		inline bool			  operator!=(ConstIterator other) const { return index != other.index || v != other.v; }
		inline bool			  operator==(ConstIterator other) const { return index == other.index && v == other.v; }
		friend class Vector<T>;
	};

	Iterator	  begin() { return Iterator(this, 0); }
	Iterator	  end() { return Iterator(this, Size); };
	ConstIterator begin() const { return ConstIterator(this, 0); }
	ConstIterator end() const { return ConstIterator(this, Size); };

   private:
	void resize_if_needed();
};

template <class T>
Vector<T>::Vector() : Capacity(0), Size(0), Arr(nullptr) {}

template <class T>
Vector<T>::~Vector() {
	if (this->Arr) delete[] this->Arr;
}

template <class T>
Vector<T>::Vector(const Vector &other) : Capacity(other.Capacity), Size(other.Size), Arr(new T[other.Capacity]) {
	// ne!!! memcopy(Arr, other.Arr, this->Size * Sizeof(T));
	for (std::size_t i = 0; i < this->Size; ++i) {
		Arr[i] = other.Arr[i];
	}
	std::cout << "copy constructor" << std::endl;
}
template <class T>
Vector<T>::Vector(Vector &&other) : Capacity(other.Capacity), Size(other.Size), Arr(other.Arr) {
	other.Capacity = 0;
	other.Size	   = 0;
	other.Arr	   = nullptr;
	std::cout << "move constructor" << std::endl;
}

template <class T>
Vector<T>::Vector(std::initializer_list<T> other)
	: Capacity(other.size()), Size(0), Arr(new T[other.size()]) {
	for (auto t : other) {
		push_back(t);
	}
	std::cout << "{} constructor" << std::endl;
}

template <class T>
Vector<T> &Vector<T>::operator=(const Vector &other) {
	if (this == &other) return *this;

	clear();

	this->Capacity = other.Capacity;
	this->Size	   = other.Size;
	this->Arr	   = new T[this->Capacity];
	for (std::size_t i = 0; i < this->Size; ++i) {
		Arr[i] = other.Arr[i];
	}
}

template <class T>
Vector<T> &Vector<T>::operator=(Vector &&other) {
	this->Capacity = other.Capacity;
	this->Size	   = other.Size;
	this->Arr	   = other.Arr;

	other.Capacity = 0;
	other.Size	   = 0;
	other.Arr	   = nullptr;
}

template <class T>
void Vector<T>::clear() {
	if (Arr) {
		delete[] Arr;
		this->Arr	   = nullptr;
		this->Capacity = 0;
		this->Size	   = 0;
	}
}

template <class T>
void Vector<T>::resize(std::size_t new_cap) {
	assert(this->Size <= new_cap);
	if (this->Capacity == new_cap) return;

	T *new_arr = new T[new_cap];
	for (std::size_t i = 0; i < this->Size; ++i) {
		new_arr[i] = std::move(this->Arr[i]);
	}
	if (Arr) delete[] this->Arr;
	this->Arr	   = new_arr;
	this->Capacity = new_cap;
}

template <class T>
void Vector<T>::push_back(T &&value) {
	resize_if_needed();
	this->Arr[this->Size++] = std::move(value);
}

template <class T>
void Vector<T>::push_back(const T &value) {
	resize_if_needed();
	this->Arr[this->Size++] = value;
}

template <class T>
void Vector<T>::resize_if_needed() {
	if (this->Size >= this->Capacity) {
		if (!this->Capacity) Capacity = 2;
		resize(this->Capacity << 1);
	}
}

template <class T>
void Vector<T>::pop_back() {
	assert(Size > 0);
	--Size;
}

template <class T>
typename Vector<T>::Iterator &Vector<T>::Iterator::operator++() {
	++this->index;
	return *this;
}
template <class T>
typename Vector<T>::Iterator Vector<T>::Iterator::operator++(int) {
	Iterator res = *this;
	this->operator++();
	return res;
}

template <class T>
typename Vector<T>::Iterator &Vector<T>::Iterator::operator--() {
	--this->index;
	return *this;
}
template <class T>
typename Vector<T>::Iterator Vector<T>::Iterator::operator--(int) {
	Iterator res = *this;
	this->operator--();
	return res;
}

template <class T>
typename Vector<T>::ConstIterator &Vector<T>::ConstIterator::operator++() {
	++this->index;
	return *this;
}
template <class T>
typename Vector<T>::ConstIterator Vector<T>::ConstIterator::operator++(int) {
	ConstIterator res = *this;
	this->operator++();
	return res;
}

template <class T>
typename Vector<T>::ConstIterator &Vector<T>::ConstIterator::operator--() {
	--this->index;
	return *this;
}
template <class T>
typename Vector<T>::ConstIterator Vector<T>::ConstIterator::operator--(int) {
	ConstIterator res = *this;
	this->operator--();
	return res;
}
