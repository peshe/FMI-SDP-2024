#include <iostream>
#include <ostream>
#include <sstream>

#include "serializable.hpp"
#include "particle_system.hpp"

struct Point : Serializable {
	int x, y, z;

   public:
	Point() : Point(0,0,0) {}
	Point(int x, int y, int z) : x(x), y(y), z(z) {}
	void serialize(std::ostream &out) override {
		out.write((char *)&x, sizeof(x));
		out.write((char *)&y, sizeof(y));
		out.write((char *)&z, sizeof(z));
	}

	void deserialize(std::istream &in) override {
		in.read((char *)&x, sizeof(x));
		in.read((char *)&y, sizeof(y));
		in.read((char *)&z, sizeof(z));
	}
};

int main() {
	std::stringstream s;

	{
		ParticleSystem<Point> ps;
		ps.add(Point{1, 2, 3});
		ps.add(Point{4, 5, 6});
		ps.add(Point{1, 2, 3});
		ps.add(Point{4, 5, 6});

		for (auto [x, y, z] : ps)
			std::cout << x << " " << y << " " << z << std::endl;
		std::cout << std::endl;
		ps.serialize(s);
		std::cout << "serialization done " << std::endl;
	}


	{
		ParticleSystem<Point> ps;
		ps.add(Point{10,20,30});
		ps.deserialize(s);
		std::cout << "deserialization done" << std::endl;
		for (auto [x, y, z] : ps)
			std::cout << x << " " << y << " " << z << std::endl;
		std::cout << std::endl;
	}
}
