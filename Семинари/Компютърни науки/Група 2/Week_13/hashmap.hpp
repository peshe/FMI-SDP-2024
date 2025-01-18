#pragma once

#include <stdexcept>
#include <vector>
#include <iostream>

template <class T>
class uptr {
	T *ptr;

   public:
	uptr(T *ptr) : ptr(ptr) {};
	uptr(const uptr &) = delete;
	uptr(uptr &&rhs) noexcept : ptr(rhs.ptr) { rhs.ptr = nullptr; }

	~uptr() { delete ptr; }

	uptr &operator=(const uptr &) = delete;
	uptr &operator=(uptr &&rhs) { std::swap(ptr, rhs.ptr); }

	T		*operator->() { return ptr; }
	const T *operator->() const { return ptr; }
	T		&operator*() { return *ptr; }
	const T &operator*() const { return *ptr; }
};

template <typename K, typename V>
class hashmap {
   public:
	hashmap(std::size_t size) : data(size) {}

	void insert(const K &key, const V &value) {
		std::size_t index = hash(key, data.size());
		for (uptr<node> &n : data[index]) {
			if (n->key == key) {
				n->value = value;
				return;
			}
		}
		data[index].push_back(new node{key, value});

		if (data[index].size() >= 3) { rehash(); }
	}

	V& get(const K &key) {
		std::size_t index = hash(key, data.size());
		for (uptr<node> &n : data[index]) {
			if (n->key == key) {
				return n->value;
			}
		}
		throw std::runtime_error("NO");
	}

	void printAll() {
		for (std::vector<uptr<node>> &el : data) {
			std::cout << "{" << std::endl;
			for (uptr<node> &node : el) {
				std::cout << node->key << " " << node->value << std::endl;
			}
			std::cout << "}" << std::endl;
		}
	}

   private:
	struct node {
		K key;
		V value;
	};

	std::vector<std::vector<uptr<node>>> data;

	std::size_t hash(const K &key, std::size_t size) { return std::hash<K>()(key) % size; }

	void rehash() {
		std::vector<std::vector<uptr<node>>> newData(2 * data.size());

		for (std::vector<uptr<node>> &el : data) {
			for (uptr<node> &n : el) {
				//n->key, n->value;
				std::size_t newPos = hash(n->key, newData.size());
				newData[newPos].push_back(std::move(n));
			}
		}

		data = std::move(newData);
	}
};
