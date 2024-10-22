#pragma once

#include <cstdint>
#include <vector>
#include "../../../../Лекции/примери/линейни СД/DynamicArray/DynArray.hpp"

namespace fmi {
namespace sdp {

/*
* Проблем: не използва алокатора
* Трябва да се подмени std::vector с DynArray
* Вероятно би изисквало някои промени по DynArray
* и алокаторът тъй като DynArray не позволява да се 
* използва алокатор с тип uint16_t при T=bool
*/

template <class Allocator>
class DynArray<bool, Allocator> {
   public:
	DynArray() : Size(0), Arr() {}
	DynArray(std::size_t Size) : Size(Size), Arr((Size + 15) >> 4) {}

	class DynArrayProxy {
		uint16_t *ptr;
		uint8_t	  position;

	   public:
		DynArrayProxy(uint16_t *ptr, uint8_t position) : ptr(ptr), position(position) {}

		DynArrayProxy &operator=(bool b) {
			*ptr &= ~(1 << position);
			*ptr |= b << position;
			return *this;
		}

		operator bool() const { return (*ptr & (1 << position)) >> position; }
	};

	template <class Type = uint16_t, class ProxyType = DynArrayProxy>
	class Iterator {
		Type   *ptr;
		uint8_t position;

	   public:
		Iterator(Type *ptr, uint8_t position) : ptr(ptr), position(position) {}

		Iterator &operator++() {
			++position;
			ptr += position >> 4;
			position &= 0b1111;
			return *this;
		}
		Iterator operator++(int) {
			Iterator res(*this);
			++(*this);
			return res;
		}

		ProxyType operator*() { return DynArrayProxy(const_cast<uint16_t *>(ptr), position); }

		bool operator==(const Iterator &other) const { return ptr == other.ptr && position == other.position; }
		bool operator!=(const Iterator &other) const { return ptr != other.ptr || position != other.position; }
	};

	using ConstIterator = Iterator<const uint16_t, const DynArrayProxy>;

	Iterator<> begin() { return Iterator(&Arr[0], 0); }
	Iterator<> end() { return Iterator(&Arr[Size >> 4], Size & 0b1111); }

	ConstIterator begin() const { return ConstIterator(&Arr[0], 0); }
	ConstIterator end() const { return ConstIterator(&Arr[Size >> 4], Size & 0b1111); }

	void push_back(bool b) {
		if (Size >= 16 * Arr.size()) Arr.push_back(b);
		else (*this)[Size] = b;
		++Size;
	}

	void		pop_back() { --Size; }
	std::size_t size() const { return Size; }

	DynArrayProxy		operator[](int i) { return DynArrayProxy(&Arr[i >> 4], i & 0b1111); }
	const DynArrayProxy operator[](int i) const {
		return DynArrayProxy(const_cast<uint16_t *>(&Arr[i >> 4]), i & 0b1111);
	}

   private:
	std::size_t			  Size;
	std::vector<uint16_t> Arr;
};

}	  // namespace sdp
}	  // namespace fmi
