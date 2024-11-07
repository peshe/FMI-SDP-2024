

#include <queue>
#include <stdexcept>
#include <vector>
#include "serializable.hpp"

template <class T>
class ParticleSystem : public Serializable {
   private:
   public:
	using Id = unsigned int;

	Id add(const T &el) {
		if (!empty.empty()) {
			Id free				 = empty.front();
			elements[free].value = el;
			elements[free].valid = true;
			empty.pop();
			return free;
		}
		elements.push_back(ElementData{el, true});
		return elements.size() - 1;
	}

	void remove(Id id) {
		empty.push(id);
		elements[id].valid = false;
	}

	T &operator[](Id id) {
		if (!elements[id].valid) { throw std::invalid_argument("invalid id"); }
		return elements[id].value;
	}

	template <class C = ParticleSystem<T>, class U = T>
	class Iterator {
		C &container;
		Id id;

	   public:
		Iterator(C &container, Id id) : container(container), id(id) {}

		Iterator &operator++() {
			if(id >= container.elements.size()) return *this;
			do {
				++this->id;
			} while (id < container.elements.size() && !container.elements[id].valid);
			return *this;
		}
		Iterator operator++(int) {
			Iterator res = *this;
			this->operator++();
			return res;
		}
		inline U   &operator*() { return container[id]; }
		inline bool operator!=(Iterator other) const { return id != other.id || &container != &other.container; }
		inline bool operator==(Iterator other) const { return id == other.id && &container == &other.container; }
		inline bool isValid() const { return id < container.elements.size() && container.elements[id].valid; }
		friend class ParticleSystem<T>;
	};
	using ConstIterator = Iterator<const ParticleSystem<T>, const T>;

	Iterator<> begin() {
		Iterator<> it{*this, static_cast<Id>(0)};
		if (!it.isValid()) ++it;
		return it;
	}

	Iterator<> end() { return Iterator<>{*this, static_cast<Id>(elements.size())}; }

	ConstIterator begin() const {
		ConstIterator it{*this, static_cast<Id>(0)};
		if (!it.isValid()) ++it;
		return it;
	}

	ConstIterator end() const { return ConstIterator{*this, static_cast<Id>(elements.size())}; }

	void serialize(std::ostream &out) {
		std::size_t size = elements.size();
		out.write((char*)&size, sizeof(size));
		for (auto &[value, valid] : elements) {
			value.serialize(out);
			out.write((char*)&valid, sizeof(valid));
		}
	}

	void deserialize(std::istream &in) {
		elements.clear();
		{
			std::queue<Id> cleared;
			empty.swap(cleared);
		}
		std::size_t size;
		in.read((char*) &size, sizeof(size));
		for(std::size_t i = 0; i < size; ++i) {
			elements.push_back({T(), false});
			auto &[value, valid] = elements.back();
			value.deserialize(in);
			in.read((char*)&valid, sizeof(valid));
		}
	}

   private:
	struct ElementData {
		T	 value;
		bool valid;
	};

	std::vector<ElementData> elements;
	std::queue<Id>			 empty;
};

/*
int main() {
	ParticleSystem<int> ps;

	auto id1 = ps.add(1);
	auto id2 = ps.add(2);
	auto id3 = ps.add(3);
	auto id4 = ps.add(4);

	for (int p : ps)
		std::cout << p << " ";
	std::cout << std::endl;

	ps.remove(id1);
	ps.remove(id3);

	for (int p : ps)
		std::cout << p << " ";
	std::cout << std::endl;
}
*/
