

#include <exception>
#include <queue>
#include <stdexcept>
#include <vector>
template <class T>
class ParticleSystem {
   private:
   public:
	using Id = int;

	Id add(T &el) {
		if (!empty.empty()) {
			Id free = empty.front();
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

   private:
	struct ElementData {
		T	 value;
		bool valid;
	};

	std::vector<ElementData> elements;
	std::queue<Id>			 empty;
};

int main() { ParticleSystem<int> ps; }
