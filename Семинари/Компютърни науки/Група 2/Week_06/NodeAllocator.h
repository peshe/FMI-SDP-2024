#pragma once

#include <stdexcept>
#include "../Week_05/particle_system.hpp"

template <class T>
class Allocator : private ParticleSystem<T> {
   public:
	Allocator(std::size_t size) : ParticleSystem<T>(size) { std::cout << "CREATING AN ALLOCATOR" << std::endl; }

	T *allocate() {
		if (this->capacity() == this->size()) { throw std::invalid_argument("no more space"); }

		typename ParticleSystem<T>::Id id	 = this->add(T());
		std::cout << "ADDING: " << id << std::endl;

		T	*res = &(*this)[id];
		std::cout << "ALLOCATING: " << res << std::endl;
		return res;
	}

	void free(T *ptr) {
		std::cout << "FREEING: " << ptr << std::endl;
		if (ptr == nullptr) return;

		const T *begin = &(this->elements.data()->value);
		std::size_t id = ((char *)ptr - (char *)begin) / sizeof(typename ParticleSystem<T>::ElementData);
		std::cout << "REMOVING: " << id << std::endl;
		try {
			this->remove(id);
		} catch (...) { throw std::invalid_argument("invalid pointer to free"); }
	}

	bool checkForLeaks() { 
		if(this->size() != 0) {
			std::cout << "LEAKS DETECTED: " << this->size() << std::endl;
			for(auto &el : *this) {
				std::cout << "LEAK: " << el.to_string() << std::endl;
			}

			return true;
		}

		return this->size() == 0; }

   private:
};
