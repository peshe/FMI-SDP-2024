#include "DynArray.hpp"
#include <iostream>

using namespace fmi::sdp;

void testSpecialization()
{
    DynArrayBool boolArray(5);
    assert(boolArray.getSize() == 0);
    assert(boolArray.getCapacity() == 5);

    assert(!boolArray.contains(true));
    boolArray.append(true);
    assert(boolArray.contains(true));

    assert(!boolArray.contains(false));
    boolArray += false;
    assert(boolArray.contains(false));

    DynArray<int> intArray;
    intArray.append(2);
    intArray.append(0);
    boolArray = intArray;
    // assert(boolArray[0] == true);
    assert(boolArray.get(1) == false);
    assert(boolArray.getSize() == 2);
    assert(boolArray.getCapacity() >= 2);

    const DynArrayBool constBoolArray = intArray;
    assert(constBoolArray[0] == true);
    assert(constBoolArray.get(1) == false);
    assert(constBoolArray.getSize() == 2);
    assert(constBoolArray.getCapacity() >= 2);

    boolArray += intArray;
    for (size_t i = 0; i < boolArray.getSize(); ++i) {
    	std::cout << boolArray.get(i) << ' ';
    	assert(boolArray.get(i) == bool(intArray[i % intArray.getSize()]));
    }

    boolArray.remove(3);
    boolArray.remove(1);
    assert(!boolArray.contains(false));
}

int main()
{
	try {
    	testSpecialization();
    }
    catch (const char* e) {
    	std::cout << e << std::endl;
    	return 1;
    }
    return 0;
}
