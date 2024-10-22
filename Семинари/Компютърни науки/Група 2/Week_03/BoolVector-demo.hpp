
#include <cstddef>
#include <cstdint>
#include <vector>

class BoolVector {

	class BoolProxy {
		uint8_t *ptr;
		uint8_t position : 3;
		BoolProxy(uint8_t *ptr, uint8_t position) : ptr(ptr), position(position){}
	public: 
		
		operator bool () { 
			return (*ptr & (1 << position)) >> position;
		}

		BoolProxy &operator = (bool b) {
			*ptr = (*ptr & ~(1 << position)) | b << position;
			return *this;
		}

		void flip() {
			*ptr = *ptr ^ (1<<position);
		}

		friend class BoolVector;
	};

public:
	BoolVector(int size) : Size(size), V((size+8-1)/8) {}

	std::size_t size() {return Size;}

	BoolProxy operator[](int i) {
		return BoolProxy(V.data() + (i>>3), (i & 7));
	}

	void push_back(bool b) {
		if(Size >= 8*V.size()) V.push_back(b);
		else
			(*this)[Size] = b;
		++Size;
	}

	void pop_back() {--Size;}

private: 
	std::size_t Size;
	std::vector<uint8_t> V;

};

