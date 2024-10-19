#pragma once
#include <cstdint>
#include <vector>

class BoolVector {
   public:
	BoolVector() : Size(0), Arr(0) {}
	BoolVector(int size) : Size(size), Arr((size + 7) >> 3) {}

	class BoolVectorProxy {
		uint8_t *source;
		uint8_t	 position;	   // 0...7

	   public:
		BoolVectorProxy(uint8_t *source, std::size_t position) : source(source), position(position) {}

		BoolVectorProxy &operator=(bool b) {
			*source &= ~(1 << position);
			*source |= b << position;
			return *this;
		}

		operator bool() const { return (*source & (1 << position)) >> position; }
	};

	void push_back(bool b) {
		if (Size >= 8 * Arr.size()) { Arr.push_back(0); }

		(*this)[Size++] = b;
	}
	void pop_back() { --Size; }

	BoolVectorProxy		  operator[](int i) { return BoolVectorProxy(Arr.data() + (i >> 3), i & 7); }
	const BoolVectorProxy operator[](int i) const { return BoolVectorProxy((uint8_t *)Arr.data() + (i >> 3), i & 7); }
	std::size_t			  size() const { return Size; }

	BoolVector &operator+=(const BoolVector &other) {
		for (std::size_t i = 0; i < other.size(); ++i)
			push_back(other[i]);
		return *this;
	}

	BoolVector operator+(const BoolVector &other) const {
		BoolVector result(*this);
		result += other;
		return result;
	}

   private:
	std::size_t			 Size;
	std::vector<uint8_t> Arr;
};
