#pragma once

#include <iostream>

class Serializable {
public:
	virtual void serialize(std::ostream &) = 0;
	virtual void deserialize(std::istream &) = 0;
	virtual ~Serializable() {};
};
